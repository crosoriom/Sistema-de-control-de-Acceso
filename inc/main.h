#include <stdint.h>
#include "systick.h"
#include "gpio.h"
#include "exti.h"
#include "uart.h"

typedef enum {
    LOCKED = 0,
    TEMPORAL_UNLOCK,
    PERMANENT_UNLOCK
}state_t;
