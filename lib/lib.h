#ifndef __LIB_H__
#define __LIB_H__


typedef signed long long                    s64;
typedef unsigned long long                  u64;

typedef int                                 s32;
typedef unsigned int                        u32;

typedef short int                           s16;
typedef unsigned short int                  u16;

typedef signed char                         s8;
typedef unsigned char                       u8;


typedef unsigned int                        error_t;

// do not define bool_t, please use bool_t!
typedef unsigned char                       bool_t;
typedef unsigned int                        size_t;
typedef unsigned int                        pdiff_t;
typedef unsigned char                       byte_t;





void delay_cpu_count(u32 cpu_count);

#endif // __LIB_H__


