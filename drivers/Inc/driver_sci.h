#ifndef INC_DRIVER_SCI_H_
#define INC_DRIVER_SCI_H_

#include "ra4m1.h"

void sci2_init(void);
void sci2_write_byte(uint8_t ch);
void sci2_write(uint8_t* pBuffer, uint32_t Len);

#endif /* INC_DRIVER_SCI_H_ */
