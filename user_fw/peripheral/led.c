#include "lib.h"
#include "led.h"

void led_gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // enable GPIO clock
    RCC_APB2PeriphClockCmd(LED_R_GPIO_CLK | LED_G_GPIO_CLK | LED_B_GPIO_CLK, ENABLE);

    // GPIO pin configuration
    GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;
    GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
    GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure);

    // turn off all LED
    GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
    GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
    GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}

void LED_test(void)
{
    LED_R(ON);
    wait_for_sec(1);
    LED_R(OFF);
    
    LED_G(ON);
    wait_for_sec(1);
    LED_G(OFF);

    LED_B(ON);
    wait_for_sec(1);
    LED_B(OFF);
}
/*********************************************END OF FILE**********************/
