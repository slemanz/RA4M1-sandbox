/**
 * @file interface_io.c
 * @brief Implementation of global IO functions
 *
 * The IO_Interface_t (pointer struct) exists ONLY here, as a
 * private implementation detail. No external file knows about it.
 *
 * Call flow (e.g., led.c calls IO_write(pin_id, value)):
 *
 * IO_write(pin_id, value)
 * └─ dispatch(pin_id)         → validates pin_id, returns internal struct
 * └─ instance->write(value) → calls the real GPIO driver
 *
 * To add a new pin:
 * 1. DEFINE_IO_PIN(IDX, MASK, PORT, PIN)
 * 2. Add &s_ioN to s_io_table[]
 * No public header changes.
 */
#include "interface/interface.h"
#include "driver_gpio.h"

/* ------------------------------------------------------------------ */
/* Initialization control (bitmask per pin)                          */
/* ------------------------------------------------------------------ */

#define IO0_MASK  (1U << 0)
#define IO1_MASK  (1U << 1)
#define IO2_MASK  (1U << 2)
#define IO3_MASK  (1U << 3)
#define IO4_MASK  (1U << 4)

static uint32_t s_init_flags = 0u;

static bool s_pin_is_init(uint32_t mask)
{
    return (s_init_flags & mask) != 0u;
}

/* ------------------------------------------------------------------ */
/* Internal struct — private to this file                             */
/* ------------------------------------------------------------------ */

typedef struct
{
    io_status_t (*init)    (void);
    io_status_t (*write)   (uint8_t value);
    io_status_t (*read)    (uint8_t *out_value);
    io_status_t (*toggle)  (void);
    io_status_t (*set_mode)(uint8_t mode);
    io_status_t (*deinit)  (void);
} io_instance_t;

/* ------------------------------------------------------------------ */
/* Generation macro — one complete instance per pin                  */
/* ------------------------------------------------------------------ */

#define DEFINE_IO_PIN(IDX, MASK, PORT, PIN)                                 \
                                                                            \
    static io_status_t priv_io##IDX##_init(void)                            \
    {                                                                       \
        GPIO_PinConfig_t cfg;                                               \
        cfg.pPORT               = (PORT);                                   \
        cfg.GPIO_PinNumber      = (PIN);                                    \
        cfg.GPIO_PinMode        = GPIO_MODE_OUT;                            \
        cfg.GPIO_PinDrive       = GPIO_PIN_DRIVE_LOW;                       \
        cfg.GPIO_PinOPType      = GPIO_PIN_OP_TYPE_CMOS;                    \
        cfg.GPIO_PinPuControl = GPIO_PIN_PU_DISABLE;                        \
        cfg.GPIO_PeriphSel      = GPIO_PIN_PSEL_DEFAULT;                    \
        if (GPIO_Init(&cfg) != GPIO_OK) return IO_ERR_HW_FAULT;             \
        s_init_flags |= (MASK);                                             \
        return IO_OK;                                                       \
    }                                                                       \
    static io_status_t priv_io##IDX##_write(uint8_t value)                  \
    {                                                                       \
        if (!s_pin_is_init(MASK)) {                                         \
            io_status_t s = priv_io##IDX##_init();                          \
            if (s != IO_OK) return s;                                       \
        }                                                                   \
        GPIO_WriteToOutputPin((PORT), (PIN), value);                        \
        return IO_OK;                                                       \
    }                                                                       \
                                                                            \
    static io_status_t priv_io##IDX##_read(uint8_t *out_value)              \
    {                                                                       \
        if (out_value == NULL) return IO_ERR_NULL;                          \
        if (!s_pin_is_init(MASK)) {                                         \
            io_status_t s = priv_io##IDX##_init();                          \
            if (s != IO_OK) return s;                                       \
        }                                                                   \
        *out_value = GPIO_ReadFromInputPin((PORT), (PIN));                  \
        return IO_OK;                                                       \
    }                                                                       \
                                                                            \
    static io_status_t priv_io##IDX##_toggle(void)                          \
    {                                                                       \
        if (!s_pin_is_init(MASK)) {                                         \
            io_status_t s = priv_io##IDX##_init();                          \
            if (s != IO_OK) return s;                                       \
        }                                                                   \
        GPIO_ToggleOutputPin((PORT), (PIN));                                \
        return IO_OK;                                                       \
    }                                                                       \
                                                                            \
    static io_status_t priv_io##IDX##_set_mode(uint8_t mode)                \
    {                                                                       \
        if (!s_pin_is_init(MASK)) {                                         \
            io_status_t s = priv_io##IDX##_init();                          \
            if (s != IO_OK) return s;                                       \
        }                                                                   \
        GPIO_SetPinMode((PORT), (PIN), mode);                               \
        return IO_OK;                                                       \
    }                                                                       \
                                                                            \
    static io_status_t priv_io##IDX##_deinit(void)                          \
    {                                                                       \
        s_init_flags &= ~(MASK);                                            \
        return IO_OK;                                                       \
    }                                                                       \
                                                                            \
    static const io_instance_t s_io##IDX = {                                \
        .init     = priv_io##IDX##_init,                                    \
        .write    = priv_io##IDX##_write,                                   \
        .read     = priv_io##IDX##_read,                                    \
        .toggle   = priv_io##IDX##_toggle,                                  \
        .set_mode = priv_io##IDX##_set_mode,                                \
        .deinit   = priv_io##IDX##_deinit,                                  \
    }

/* ------------------------------------------------------------------ */
/* Instances — logical → physical mapping                            */
/* ------------------------------------------------------------------ */

DEFINE_IO_PIN(0, IO0_MASK, PORT1, GPIO_PIN_NO_11);
DEFINE_IO_PIN(1, IO1_MASK, PORT3, GPIO_PIN_NO_4);

/* ------------------------------------------------------------------ */
/* Dispatch table — only internal "public" data structure            */
/* ------------------------------------------------------------------ */

static const io_instance_t * const s_io_table[] = {
    &s_io0,   /* pin_id 0 -> PORT1 - PIN 11 */
    &s_io1,   /* pin_id 1 -> PORT3 - PIN 4  */
};

#define IO_PIN_COUNT  ((uint8_t)(sizeof(s_io_table) / sizeof(s_io_table[0])))

static const io_instance_t *io_dispatch(uint8_t pin_id)
{
    if(pin_id >= IO_PIN_COUNT) return NULL;
    return s_io_table[pin_id];
}

/* ================================================================== */
/* Implementation of public functions declared in interface.h        */
/* ================================================================== */

io_status_t IO_init(uint8_t pin_id)
{
    const io_instance_t *io = io_dispatch(pin_id);
    if(io == NULL) return IO_ERR_INVALID_PIN;
    return io->init();
}

io_status_t IO_write(uint8_t pin_id, uint8_t value)
{
    const io_instance_t *io = io_dispatch(pin_id);
    if (io == NULL) return IO_ERR_INVALID_PIN;
    return io->write(value);
}

io_status_t IO_read(uint8_t pin_id, uint8_t *out_value)
{
    if (out_value == NULL) return IO_ERR_NULL;
    const io_instance_t *io = io_dispatch(pin_id);
    if (io == NULL) return IO_ERR_INVALID_PIN;
    return io->read(out_value);
}

io_status_t IO_toggle(uint8_t pin_id)
{
    const io_instance_t *io = io_dispatch(pin_id);
    if (io == NULL) return IO_ERR_INVALID_PIN;
    return io->toggle();
}

io_status_t IO_set_mode(uint8_t pin_id, uint8_t mode)
{
    const io_instance_t *io = io_dispatch(pin_id);
    if (io == NULL) return IO_ERR_INVALID_PIN;
    return io->set_mode(mode);
}

io_status_t IO_deinit(uint8_t pin_id)
{
    const io_instance_t *io = io_dispatch(pin_id);
    if (io == NULL) return IO_ERR_INVALID_PIN;
    return io->deinit();
}