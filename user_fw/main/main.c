#include "stm32f10x.h"
#include "led.h"
#include "arm_init.h"
#include "usart.h"




int main(void)
{
    enable_cpu_cycle_count();
    sys_tick_init();
    led_init();
    usart1_init();
    print("System init done.\n");

    
    while(1)
    {
        led_test();
    }
}
/*********************************************END OF FILE**********************/
