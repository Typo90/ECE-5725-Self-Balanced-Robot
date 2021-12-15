#include "common.h"

void do_sth_before_exit()
{
    i2c_deinit();
    bcm2835_close();
}
