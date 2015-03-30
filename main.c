#include "stm32f4xx_hal.h"

extern void EXTI15_10_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if(GPIO_Pin == GPIO_PIN_13) {
    GPIO_PinState ledState;

    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
      ledState = GPIO_PIN_RESET;
    } else {
      ledState = GPIO_PIN_SET;
    }

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ledState);
  }
}

int main() {
  HAL_Init();

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef led = {
    .Pin = GPIO_PIN_5,
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Speed = GPIO_SPEED_FAST,
    .Pull = GPIO_NOPULL
  };
  HAL_GPIO_Init(GPIOA, &led);

  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef button = {
    .Pin = GPIO_PIN_13,
    .Mode = GPIO_MODE_IT_RISING_FALLING,
    .Pull = GPIO_NOPULL
  };
  HAL_GPIO_Init(GPIOC, &button);
  HAL_NVIC_SetPriority((IRQn_Type) EXTI15_10_IRQn, 0x0F, 0x00);
  HAL_NVIC_EnableIRQ((IRQn_Type) EXTI15_10_IRQn);

  while (1) {
  }
}
