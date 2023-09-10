#include "FreeRTOS.h"
#include "task.h"

#include "stm32f7xx_hal.h"

// These interrupt handles override the weak symbols defined in startup.c

// Handler pointers are stored in interrupt vector in startup.c, hence the C linkage.
extern "C" {
void SysTick_Handler(void);
void xPortSysTickHandler(void);  // FreeRTOS SysTick handler.
}

// Handle SysTick manually so that both HAL and FreeRTOS handlers can be called.
void SysTick_Handler(void) {
  HAL_IncTick();

  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
    xPortSysTickHandler();
  }
}
