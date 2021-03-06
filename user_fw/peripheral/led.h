#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

// Red
#define LED_R_GPIO_PORT GPIOB                // GPIOB
#define LED_R_GPIO_CLK  RCC_APB2Periph_GPIOB // GPIO clock
#define LED_R_GPIO_PIN  GPIO_Pin_5           // PIN5

// Green
#define LED_G_GPIO_PORT GPIOB                // GPIOB
#define LED_G_GPIO_CLK  RCC_APB2Periph_GPIOB // GPIO clock
#define LED_G_GPIO_PIN  GPIO_Pin_0           // PIN0

// Blue
#define LED_B_GPIO_PORT GPIOB                // GPIOB
#define LED_B_GPIO_CLK  RCC_APB2Periph_GPIOB // GPIO clock
#define LED_B_GPIO_PIN  GPIO_Pin_1           // PIN1

/** the macro definition to trigger the led on or off 
  * 1 - off
  * 0 - on
  */
#define ON  0
#define OFF 1

#define LED_R(a)                                       \
    if (a)                                             \
        GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN); \
    else                                               \
        GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN)

#define LED_G(a)                                       \
    if (a)                                             \
        GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN); \
    else                                               \
        GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN)

#define LED_B(a)                                       \
    if (a)                                             \
        GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
    else                                               \
        GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN)

void led_init(void);
void led_test(void);

#endif /* __LED_H__ */
