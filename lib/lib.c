#include "lib.h"

inline void delay_cpu_count(u32 cpu_count)
{
    while (cpu_count--);
}

