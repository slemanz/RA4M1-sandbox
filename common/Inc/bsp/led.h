#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>
#include "interface/interface.h"

void led_setup(IO_Interface_t *io_pin);
void led_toggle(void);

#endif /* INC_LED_H_ */