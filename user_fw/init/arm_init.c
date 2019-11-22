#include "arm_init.h"


void sys_tick_init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}


/*********************************************END OF FILE**********************/
