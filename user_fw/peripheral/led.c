#include "led.h"
#include "arm_init.h"
#include "lib.h"

static void led_red_init(void)
{
    enable_apb2_clock(LED_R_GPIO_CLK);
    gpio_config(LED_R_GPIO_PORT, LED_R_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
}

static void led_green_init(void)
{
    enable_apb2_clock(LED_G_GPIO_CLK);
    gpio_config(LED_G_GPIO_PORT, LED_G_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
}

static void led_blue_init(void)
{
    enable_apb2_clock(LED_B_GPIO_CLK);
    gpio_config(LED_B_GPIO_PORT, LED_B_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}

void led_init(void)
{
    led_red_init();
    led_green_init();
    led_blue_init();
}

void led_test(void)
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
