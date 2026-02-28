#ifndef INC_INTERFACE_H_
#define INC_INTERFACE_H_

#include <stdint.h>
#include <stddef.h>

/************************************************************
*                       TIMEBASE                            *
*************************************************************/

typedef struct {
    uint64_t (*get)(void);
    void (*deinit)(void);
}timebase_interface_t;

timebase_interface_t *timebase_get(void);

/************************************************************
*                       COMM                                *
*************************************************************/

typedef struct
{
    void    (*init)(void);
    void    (*send)(uint8_t *buffer, uint32_t len);
    uint8_t (*receive)(uint8_t *buffer, uint32_t len);
    uint8_t (*data_available)(void);
    void    (*deinit)(void);
}Comm_Interface_t;

Comm_Interface_t *Comm_ProtocolGet(uint8_t type);

/************************************************************
*                       IO                                  *
*************************************************************/

typedef enum {
    IO_OK              =  0,   /**< Operation completed successfully     */
    IO_ERR_NULL        = -1,   /**< Null pointer received                */
    IO_ERR_INVALID_PIN = -2,   /**< pin_id out of configured range       */
    IO_ERR_NOT_INIT    = -3,   /**< Pin not initialized                  */
    IO_ERR_HW_FAULT    = -4,   /**< Fault reported by the GPIO driver    */
    IO_ERR_TIMEOUT     = -5,   /**< Timeout in an I/O operation          */
}io_status_t;

typedef struct
{
    void    (*init)(void);
    void    (*write)(uint8_t value);
    uint8_t (*read)(void);
    void    (*toggle)(void);
    void    (*deinit)(void);
}IO_Interface_t;  

/** Canonical values for pin read/write */
#define IO_PIN_HIGH     ((uint8_t)1u)
#define IO_PIN_LOW      ((uint8_t)0u)

/** Direction modes for IO_set_mode() */
#define IO_MODE_OUTPUT  ((uint8_t)0u)
#define IO_MODE_INPUT   ((uint8_t)1u)

io_status_t IO_init(uint8_t pin_id);
io_status_t IO_write(uint8_t pin_id, uint8_t value);
io_status_t IO_read(uint8_t pin_id, uint8_t *out_value);
io_status_t IO_toggle(uint8_t pin_id);
io_status_t IO_set_mode(uint8_t pin_id, uint8_t mode);
io_status_t IO_deinit(uint8_t pin_id);

#endif /* INC_INTERFACE_H_ */