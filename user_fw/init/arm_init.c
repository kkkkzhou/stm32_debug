#include "lib.h"
#include "arm_init.h"


inline void sys_tick_init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}

void nvic_irq_config(u32 pri_group, u32 irq_n, u32 preemp_prority, u32 sub_prority, FunctionalState state)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    mem_set(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    
    NVIC_PriorityGroupConfig(pri_group);
    NVIC_InitStructure.NVIC_IRQChannel = irq_n;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = preemp_prority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_prority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = state;
    NVIC_Init(&NVIC_InitStructure);
}

void gpio_config(GPIO_TypeDef *gpio_x, u16 pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    mem_set(&GPIO_InitStructure, 0, sizeof(NVIC_InitTypeDef));
    
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_Init(gpio_x, &GPIO_InitStructure);
}

inline void enable_apb1_clock(u32 apb1_periph)
{
    RCC_APB1PeriphClockCmd(apb1_periph, ENABLE);
}

inline void disable_apb1_clock(u32 apb1_periph)
{
    RCC_APB1PeriphClockCmd(apb1_periph, DISABLE);
}

inline void enable_apb2_clock(u32 apb2_periph)
{
    RCC_APB2PeriphClockCmd(apb2_periph, ENABLE);
}

inline void disable_apb2_clock(u32 apb2_periph)
{
    RCC_APB2PeriphClockCmd(apb2_periph, DISABLE);
}

inline void enable_ahb_clock(u32 ahb_periph)
{
    RCC_AHBPeriphClockCmd(ahb_periph, ENABLE);
}

inline void disable_ahb_clock(u32 ahb_periph)
{
    RCC_AHBPeriphClockCmd(ahb_periph, DISABLE);
}

/*********************************************END OF FILE**********************/
