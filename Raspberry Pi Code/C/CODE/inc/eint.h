#ifndef _EINT_H_
#define _EINT_H_

#include "common.h"

typedef void (*callback)();

void eint_init();
void register_eint_callback(callback cb);

#endif