#include "stm32f10x.h"
#include "lib.h"

// 1ms 1 sys tick interrupt
__IO u32 gt_time_elapsed = 0;

inline u32 get_sys_tick(void)
{
    return gt_time_elapsed;
}

void wait_for_sec(u32 sec)
{
    u32 cur_time = get_sys_tick();

    u32 expire = cur_time + sec*1000;

    // Here is what Linux kernal does...
    while((s32)expire - (s32)get_sys_tick() > 0);
}

void wait_for_ms(u32 ms)
{
    u32 current_cnt = 0;
    u32 internal_cnt = 0;
    u32 delay_cycle_count = 0;
    
    if(ms > 1000)
    {
        wait_for_sec(ms/1000);
    }
    else
    {
        delay_cycle_count = ms*(SystemCoreClock/1000);

        while (internal_cnt < delay_cycle_count)
        {
            u32 wait_cycle = 10;
            do
            {
                if (!wait_cycle)
                {
                    current_cnt = get_cpu_cycle_count();
                }
            } while (wait_cycle-- != 0);
            internal_cnt = current_cnt;
        }
    }
}

void wait_for_us(u32 us)
{
    u32 cur_time = 0;
    u32 next_time = 0;
    u32 delay_cycle_count = 0;
    
    cur_time            = get_cpu_cycle_count();
    delay_cycle_count   = us*(SystemCoreClock/1000000);

    while(delay_cycle_count > 0)
    {
        next_time   = get_cpu_cycle_count();
        if(next_time >= cur_time)
        {
            delay_cycle_count -= (next_time - cur_time);
        }
        else
        {
            delay_cycle_count -= (next_time + 0xFFFFFFFF - cur_time);
        }
        cur_time = next_time;
    }
}



