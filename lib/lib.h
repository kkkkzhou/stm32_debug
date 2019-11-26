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


void wait_for_sec(u32 sec);
void wait_for_ms(u32 ms);
void wait_for_us(u32 us);

#define OPTI_S               // _Pragma("optimize=speed high")
#define OPTI_Z               // _Pragma("optimize=size high")s


#define ASSERT(x) 				do {} while(0);

#define HIGH_MAGIC	0x80808080L
#define LOW_MAGIC	0x01010101L

#define ASCII_SPACE			0x20
#define ASCII_BELL 			0x07
#define ASCII_APOSTROPHE	0x27
#define PRINT_PLURAL_MASK	0x80000000		




void*   mem_cpy     (void *dst, const void *src, size_t len);
void*   mem_cpy32   (void *dst, const void *src, size_t len_of_words);

void*   mem_set     (void *dst, unsigned char value, size_t len);
void*   mem_set32   (void *dst, long value, size_t len_of_words);

void    mem_zero    (void *s, size_t len);
int     mem_cmp     (const void *b1, const void *b2, u32 nbytes);
int 	mem_cmp32(const void *b1, const void *b2, u32 nbytes);

char*   str_cpy     (char *dest, const char *src);
char*   strn_cpy    (char *dest, const char *src, size_t n);

char* 	str_cat     (char *dest, const char *src);
char* 	strn_cat    (char *dest, const char *src, size_t n);

int  	str_cmp     (const char *s1, const char *s2);
int  	strn_cmp    (const char *s1, const char *s2, size_t n);

#endif // __LIB_H__


