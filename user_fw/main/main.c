
#include "stm32f10x.h"
#include "led.h"


int main(void)
{   
    LED_GPIO_Config();
    
    while(1)
    {
        LED_test();
    }
}
/*********************************************END OF FILE**********************/
