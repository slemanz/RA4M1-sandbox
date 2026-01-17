#ifndef INC_UPRINT_H_
#define INC_UPRINT_H_

#include <stdarg.h>
#include "interface/interface.h"

void uprint_setup(Comm_Interface_t *comm);
void uprint(const char *fmt, ...);

#endif /* INC_UPRINT_H_ */