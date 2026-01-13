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

typedef struct
{
    void    (*init)(void);
    void    (*write)(uint8_t value);
    uint8_t (*read)(void);
    void    (*toggle)(void);
    void    (*deinit)(void);
}IO_Interface_t;  

#define IO_SET              1
#define IO_RESET            0

IO_Interface_t *IO_Interface_get(uint8_t pin);

#endif /* INC_INTERFACE_H_ */