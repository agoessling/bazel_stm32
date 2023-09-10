#include <stdbool.h>
#include <stdint.h>

#include "stm32f7xx.h"

// Exported from linker script.
// Reminder: the addresses of these are equal to the linker script labels.
extern uint32_t _estack;  // End of stack memory region. (initial stack pointer)
extern uint32_t _sidata;  // Start of initialization for .data section.
extern uint32_t _sdata;  // Start of .data section.
extern uint32_t _edata;  // End of .data section.
extern uint32_t _sbss;  // Start of .bss section.
extern uint32_t _ebss;  // End of .bss section.
void (* __preinit_array_start)(void); // Start of preinit function array.
void (* __preinit_array_end)(void); // End of preinit function array.
void (* __init_array_start)(void); // Start of preinit function array.
void (* __init_array_end)(void); // End of preinit function array.

int main(void); // Application main

void Reset_Handler(void) {
  uint32_t *src;
  uint32_t *dst;

  // Copy .data section by words.  This relies on .data being word aligned via linker script.
  src = &_sidata;
  dst = &_sdata;
  while (dst < &_edata) {
    *dst++ = *src++;
  }

  // Zero .bss seciton by words.  This relies on .bss being word aligned via linker script.
  dst = &_sbss;
  while (dst < &_ebss) {
    *dst++ = 0;
  }

  // Turn on FPU.
  SCB->CPACR |= (0x0F << 20); // Enable full access to CP10 and CP11 coprocessors.
  __DSB();
  __ISB();

  // Static initialization functions aggregated by compiler into .preinit_array and .init_array.
  void (**func)(void);

  func = &__preinit_array_start;
  while (func < &__preinit_array_end) {
    (*func++)();
  }

  func = &__init_array_start;
  while (func < &__init_array_end) {
    (*func++)();
  }

  (void)main();

  // NOTE: Static deinitialization functions are not handled as they don't make sense in an embedded
  // context.

  // Catch if main() returns.
  while (true) {
  }
}

// Create weak alias to trap for all interrupts.
__attribute__((weak)) void NMI_Handler(void) { while(true) {} }
__attribute__((weak)) void HardFault_Handler(void) { while(true) {} }
__attribute__((weak)) void MemManage_Handler(void) { while(true) {} }
__attribute__((weak)) void BusFault_Handler(void) { while(true) {} }
__attribute__((weak)) void UsageFault_Handler(void) { while(true) {} }
__attribute__((weak)) void SVC_Handler(void) { while(true) {} }
__attribute__((weak)) void DebugMon_Handler(void) { while(true) {} }
__attribute__((weak)) void PendSV_Handler(void) { while(true) {} }
__attribute__((weak)) void SysTick_Handler(void) { while(true) {} }
__attribute__((weak)) void WWDG_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void PVD_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TAMP_STAMP_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void RTC_WKUP_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void FLASH_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void RCC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI0_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream0_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream6_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void ADC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN1_TX_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN1_RX0_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN1_RX1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN1_SCE_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI9_5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM1_BRK_TIM9_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM1_UP_TIM10_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM1_TRG_COM_TIM11_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM1_CC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C1_EV_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C1_ER_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C2_EV_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C2_ER_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void USART1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void USART2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void USART3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void EXTI15_10_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void RTC_Alarm_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_FS_WKUP_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM8_BRK_TIM12_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM8_UP_TIM13_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM8_TRG_COM_TIM14_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM8_CC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA1_Stream7_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void FMC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SDMMC1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void UART4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void UART5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM6_DAC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void TIM7_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream0_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream3_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void ETH_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void ETH_WKUP_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN2_TX_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN2_RX0_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN2_RX1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CAN2_SCE_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_FS_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream6_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2_Stream7_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void USART6_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C3_EV_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C3_ER_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_HS_EP1_OUT_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_HS_EP1_IN_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_HS_WKUP_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void OTG_HS_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DCMI_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void RNG_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void FPU_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void UART7_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void UART8_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI4_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI5_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPI6_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SAI1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void LTDC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void LTDC_ER_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void DMA2D_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SAI2_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void QUADSPI_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void LPTIM1_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void CEC_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C4_EV_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void I2C4_ER_IRQHandler(void) { while(true) {} }
__attribute__((weak)) void SPDIF_RX_IRQHandler(void) { while(true) {} }

// clang-format off
__attribute__((section(".isr_vector"))) void (* const isr_vectors[])(void) = {
  (void (* const)(void))&_estack,
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  // External interrupts.
  WWDG_IRQHandler,                   // Window WatchDog
  PVD_IRQHandler,                    // PVD through EXTI Line detection
  TAMP_STAMP_IRQHandler,             // Tamper and TimeStamps through the EXTI line
  RTC_WKUP_IRQHandler,               // RTC Wakeup through the EXTI line
  FLASH_IRQHandler,                  // FLASH
  RCC_IRQHandler,                    // RCC
  EXTI0_IRQHandler,                  // EXTI Line0
  EXTI1_IRQHandler,                  // EXTI Line1
  EXTI2_IRQHandler,                  // EXTI Line2
  EXTI3_IRQHandler,                  // EXTI Line3
  EXTI4_IRQHandler,                  // EXTI Line4
  DMA1_Stream0_IRQHandler,           // DMA1 Stream 0
  DMA1_Stream1_IRQHandler,           // DMA1 Stream 1
  DMA1_Stream2_IRQHandler,           // DMA1 Stream 2
  DMA1_Stream3_IRQHandler,           // DMA1 Stream 3
  DMA1_Stream4_IRQHandler,           // DMA1 Stream 4
  DMA1_Stream5_IRQHandler,           // DMA1 Stream 5
  DMA1_Stream6_IRQHandler,           // DMA1 Stream 6
  ADC_IRQHandler,                    // ADC1, ADC2 and ADC3s
  CAN1_TX_IRQHandler,                // CAN1 TX
  CAN1_RX0_IRQHandler,               // CAN1 RX0
  CAN1_RX1_IRQHandler,               // CAN1 RX1
  CAN1_SCE_IRQHandler,               // CAN1 SCE
  EXTI9_5_IRQHandler,                // External Line[9:5]s
  TIM1_BRK_TIM9_IRQHandler,          // TIM1 Break and TIM9
  TIM1_UP_TIM10_IRQHandler,          // TIM1 Update and TIM10
  TIM1_TRG_COM_TIM11_IRQHandler,     // TIM1 Trigger and Commutation and TIM11
  TIM1_CC_IRQHandler,                // TIM1 Capture Compare
  TIM2_IRQHandler,                   // TIM2
  TIM3_IRQHandler,                   // TIM3
  TIM4_IRQHandler,                   // TIM4
  I2C1_EV_IRQHandler,                // I2C1 Event
  I2C1_ER_IRQHandler,                // I2C1 Error
  I2C2_EV_IRQHandler,                // I2C2 Event
  I2C2_ER_IRQHandler,                // I2C2 Error
  SPI1_IRQHandler,                   // SPI1
  SPI2_IRQHandler,                   // SPI2
  USART1_IRQHandler,                 // USART1
  USART2_IRQHandler,                 // USART2
  USART3_IRQHandler,                 // USART3
  EXTI15_10_IRQHandler,              // External Line[15:10]s
  RTC_Alarm_IRQHandler,              // RTC Alarm (A and B) through EXTI Line
  OTG_FS_WKUP_IRQHandler,            // USB OTG FS Wakeup through EXTI line
  TIM8_BRK_TIM12_IRQHandler,         // TIM8 Break and TIM12
  TIM8_UP_TIM13_IRQHandler,          // TIM8 Update and TIM13
  TIM8_TRG_COM_TIM14_IRQHandler,     // TIM8 Trigger and Commutation and TIM14
  TIM8_CC_IRQHandler,                // TIM8 Capture Compare
  DMA1_Stream7_IRQHandler,           // DMA1 Stream7
  FMC_IRQHandler,                    // FMC
  SDMMC1_IRQHandler,                 // SDMMC1
  TIM5_IRQHandler,                   // TIM5
  SPI3_IRQHandler,                   // SPI3
  UART4_IRQHandler,                  // UART4
  UART5_IRQHandler,                  // UART5
  TIM6_DAC_IRQHandler,               // TIM6 and DAC1&2 underrun errors
  TIM7_IRQHandler,                   // TIM7
  DMA2_Stream0_IRQHandler,           // DMA2 Stream 0
  DMA2_Stream1_IRQHandler,           // DMA2 Stream 1
  DMA2_Stream2_IRQHandler,           // DMA2 Stream 2
  DMA2_Stream3_IRQHandler,           // DMA2 Stream 3
  DMA2_Stream4_IRQHandler,           // DMA2 Stream 4
  ETH_IRQHandler,                    // Ethernet
  ETH_WKUP_IRQHandler,               // Ethernet Wakeup through EXTI line
  CAN2_TX_IRQHandler,                // CAN2 TX
  CAN2_RX0_IRQHandler,               // CAN2 RX0
  CAN2_RX1_IRQHandler,               // CAN2 RX1
  CAN2_SCE_IRQHandler,               // CAN2 SCE
  OTG_FS_IRQHandler,                 // USB OTG FS
  DMA2_Stream5_IRQHandler,           // DMA2 Stream 5
  DMA2_Stream6_IRQHandler,           // DMA2 Stream 6
  DMA2_Stream7_IRQHandler,           // DMA2 Stream 7
  USART6_IRQHandler,                 // USART6
  I2C3_EV_IRQHandler,                // I2C3 event
  I2C3_ER_IRQHandler,                // I2C3 error
  OTG_HS_EP1_OUT_IRQHandler,         // USB OTG HS End Point 1 Out
  OTG_HS_EP1_IN_IRQHandler,          // USB OTG HS End Point 1 In
  OTG_HS_WKUP_IRQHandler,            // USB OTG HS Wakeup through EXTI
  OTG_HS_IRQHandler,                 // USB OTG HS
  DCMI_IRQHandler,                   // DCMI
  0,                                 // Reserved
  RNG_IRQHandler,                    // Rng
  FPU_IRQHandler,                    // FPU
  UART7_IRQHandler,                  // UART7
  UART8_IRQHandler,                  // UART8
  SPI4_IRQHandler,                   // SPI4
  SPI5_IRQHandler,                   // SPI5
  SPI6_IRQHandler,                   // SPI6
  SAI1_IRQHandler,                   // SAI1
  LTDC_IRQHandler,                   // LTDC
  LTDC_ER_IRQHandler,                // LTDC error
  DMA2D_IRQHandler,                  // DMA2D
  SAI2_IRQHandler,                   // SAI2
  QUADSPI_IRQHandler,                // QUADSPI
  LPTIM1_IRQHandler,                 // LPTIM1
  CEC_IRQHandler,                    // HDMI_CEC
  I2C4_EV_IRQHandler,                // I2C4 Event
  I2C4_ER_IRQHandler,                // I2C4 Error
  SPDIF_RX_IRQHandler,               // SPDIF_RX
};
// clang-format on
