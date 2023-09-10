#include "stm32f7xx_hal.h"

// These interrupt handles override the weak symbols defined in startup.c

// Handler pointers are stored in interrupt vector in startup.c, hence the C linkage.
extern "C" {
void SysTick_Handler(void);
}

void SysTick_Handler(void) {
  HAL_IncTick();
}
