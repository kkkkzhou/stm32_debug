#ifndef __ARM_INIT_H__
#define __ARM_INIT_H__
#include "stm32f10x.h"

void sys_tick_init(void);
u32 get_cpu_cycle_count(void);
void enable_cpu_cycle_count(void);

inline u32 get_cpu_cycle_count(void)
{
    volatile u32 *reg = (volatile u32 *)0xE0001004;
    return *reg;
}

inline void enable_cpu_cycle_count(void)
{
    *(volatile u32 *)0xE000EDFC |= (1 << 24);
    *(volatile u32 *)0xE0001000 |= 1;
}

void nvic_irq_config(u32 pri_group, u32 irq_n, u32 preemp_prority, u32 sub_prority, FunctionalState state);
void gpio_config(GPIO_TypeDef *gpio_x, u16 pin, GPIOSpeed_TypeDef speed, GPIOMode_TypeDef mode);
void enable_apb1_clock(u32 apb1_periph);
void disable_apb1_clock(u32 apb1_periph);
void enable_apb2_clock(u32 apb2_periph);
void disable_apb2_clock(u32 apb2_periph);
void enable_ahb_clock(u32 ahb_periph);
void disable_ahb_clock(u32 ahb_periph);

#endif /* __ARM_INIT_H__ */
