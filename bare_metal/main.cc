#include <atomic>

#include "stm32f7xx_hal.h"

#define GREEN_LED_Pin GPIO_PIN_1
#define GREEN_LED_GPIO_Port GPIOI

static void MpuConfig(void);
static void SystemClockConfig(void);
static void GpioInit(void);
static void ErrorHandler(void);

static std::atomic<bool> g_flag = false;

class StaticConstructorTest {
 public:
  StaticConstructorTest() {
    g_flag = true;
  }
};

static StaticConstructorTest g_static_object;

int main(void) {
  SCB_EnableDCache();

  HAL_Init();

  MpuConfig();
  SystemClockConfig();
  GpioInit();

  while (true) {
    HAL_Delay(500);
    if (g_flag) {
      HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
    }
  }

  return 0;
}

static void MpuConfig(void) {
  HAL_MPU_Disable();

  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  // This regions protects the normal memory mapped to external memories from speculative reads (and
  // the hangs which would occur if they were made) by specifying the regions as non-cacheable.
  // See https://www.youtube.com/watch?v=6IUfxSAFhlw.
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

static void SystemClockConfig(void) {
  // Voltage scale 1 and overdrive required for operation at 216MHz. (DS Table 17.)
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // HSE = 25MHz.  PLL setup to acheive SYSCLK = 216MHZ.
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    ErrorHandler();
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    ErrorHandler();
  }

  // HCLK = 216MHz, PCLK1 = 54MHz, PCLK2 = 108MHz
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_ClkInitStruct.ClockType =
      RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  // 7 Wait states required for 216MHz operation. (RM0385 Table 5.)
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
    ErrorHandler();
  }
}

static void GpioInit(void) {
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GREEN_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GREEN_LED_GPIO_Port, &GPIO_InitStruct);
}

static void ErrorHandler(void) {
  __disable_irq();
  while (1) {
  }
}
