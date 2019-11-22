#include "stm32f10x.h"
#include "led.h"

extern void sys_tick_init(void);

int main(void)
{   
    sys_tick_init();
    led_gpio_config();
    
    while(1)
    {
        LED_test();
    }
}
/*********************************************END OF FILE**********************/
