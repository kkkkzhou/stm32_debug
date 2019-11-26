#include "stm32f10x.h"
#include "arm_init.h"
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
    
    if(ms >= 1000)
    {
        wait_for_sec(ms/1000);
    }

    ms %= 1000;
    delay_cycle_count = ms*(SystemCoreClock/1000);
    current_cnt = get_cpu_cycle_count();

    do
    {
        volatile u32 wait_cycle = 10;
        while (wait_cycle)
        {
            wait_cycle--;
        }
        
        internal_cnt = get_cpu_cycle_count() - current_cnt;
    } while(internal_cnt < delay_cycle_count);
}

void wait_for_us(u32 us)
{
    u32 current_cnt = 0;
    u32 internal_cnt = 0;
    u32 delay_cycle_count = 0;
    
    if(us >= 1000)
    {
        wait_for_ms(us/1000);
    }

    us %= 1000;
    delay_cycle_count = us*(SystemCoreClock/1000000);
    current_cnt = get_cpu_cycle_count();

    do
    {
        u32 wait_cycle = 10;
        while (wait_cycle)
        {
            wait_cycle--;
        }
        
        internal_cnt = get_cpu_cycle_count() - current_cnt;
    } while(internal_cnt < delay_cycle_count);
}

/**
 * \function 	mem_cpy
 * \brief		this function copy memory from src to dst, size of len byte. note this is copy byte by byte.
 *
 * \param[in]  	dst - the destination of buffer
 * \param[in] 	src - the source of buffer
 * \param[in] 	len - the length of buffer in bytes
 *
 * \return	   	return the last position of destination
 *
 */
OPTI_S void *mem_cpy (void *dst, const void *src, size_t len)
{
    byte_t *dstp = (byte_t *)dst;
    byte_t *srcp = (byte_t *)src;

    while (len > 0)
    {
        *dstp++ = *srcp++;
        len -= 1;
    }

    return dstp;
}


/**
 * \function 	mem_cpy32
 * \brief		this function copy memory from src to dst, size of len words. note this is copy words by words.
 * 				words is 32 bits words.
 *
 * \param[in]  	dst - the destination of buffer, must be aligned by 4.
 * \param[in] 	src - the source of buffer, must be aligned by 4.
 * \param[in] 	len_of_words - the length of buffer in 32bits words
 *
 * \return	   	return the last position of destination
 *
 */
OPTI_S void *mem_cpy32 (void *dst, const void *src, size_t len_of_words)
{
    unsigned long *dstp = (unsigned long*)dst;
    unsigned long *srcp = (unsigned long*)src;

    ASSERT(((long)dstp)%4==0);
    ASSERT(((long)srcp)%4==0);

    while (len_of_words > 0)
    {
        *dstp++ = *srcp++;
        len_of_words -= 1;
    }

    return dstp;
}


/**
 * \function 	mem_set
 * \brief		this function set a range of memory to some fixed value: value
 *
 * \param[in]  	dst - the destination of buffer
 * \param[in] 	value - value that will set to this range of buffer
 * \param[in] 	len - the length of buffer in bytes
 *
 * \return	   	return the last position of destination
 *
 */
OPTI_S void *mem_set (void *dst, unsigned char value, size_t len)
{
    byte_t *dstp = (byte_t *)dst;

    while (len > 0)
    {
        *dstp++ = value;
        len -= 1;
    }

    return dstp;
}

/**
 * \function 	mem_set32
 * \brief		this function set a range of memory to some fixed value: value
 * 				words is 32 bits words.
 *
 * \param[in]  	dst - the destination of buffer, must be aligned by 4.
 * \param[in] 	value - value that will set to this range of buffer
 * \param[in] 	len_of_words - the length of buffer in 32bits words
 *
 * \return	   	return the last position of destination
 */
OPTI_S void *mem_set32 (void *dst, long value, size_t len_of_words)
{
    unsigned long *dstp = (unsigned long*)dst;

    ASSERT(((long)dst)%4==0);

    while (len_of_words > 0)
    {
        *dstp++ = value;
        len_of_words -= 1;
    }

    return dstp;
}

/*
 memcmp implementation
*/
int mem_cmp(const void *b1, const void *b2, u32 nbytes)
{
	u8 *p1, *p2;
	int status = 0;

	p1 = (u8 *) b1;
	p2 = (u8 *) b2;
	while (nbytes--)
	{
		if (*p1 != *p2)
		{
			status = (int) (*p1 - *p2);
			break;
		}
		p1++;
		p2++;
	}
	return status;
}



int mem_cmp32(const void *b1, const void *b2, u32 nbytes)
{
    unsigned long *p1, *p2;
	int status = 0;

	p1 = (unsigned long*) b1;
	p2 = (unsigned long*) b2;
	while (nbytes--)
	{
		if (*p1 != *p2)
		{
			status = (int) (*p1 - *p2);
			break;
		}
		p1++;
		p2++;
	}
	return status;
}

/**
 * \function 	str_cpy
 * \brief		this function copy NULL terminated string src to dst
 *
 * \param[in]  	dst - the destination of string
 * \param[in] 	src - the source of string
 *
 * \return	   	return the last position of destination
 *
 */
OPTI_S char *str_cpy(char *dst, const char *src)
{
    unsigned char c;
    char *s = (char *)src;
    const pdiff_t off = dst - src - 1;

    do
    {
        c = *s++;
        s[off] = c;
    } while (c != '\0');

    return dst;
}

/**
 * \function 	strn_cpy
 * \brief		this function copy NULL terminated string src to dst
 * 				if s2 is longer than n bytes, then just copy n bytes,
 * 				if s2 is shorter than n bytes, then just whole s2 to s1, then fill with 0s.
 *
 * \param[in]  	s1 - the destination of string
 * \param[in] 	s2 - the source of string
 * \param[in] 	n  - the maximun length that to copy
 *
 * \return	   	return the last position of destination
 *
 */
OPTI_S char *strn_cpy(char *s1, const char *s2, size_t n)
{
    unsigned char c;
    char *s = s1;

    --s1;

    if (n >= 4)
    {
        size_t n4 = n >> 2;
        for (;;)
        {
            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                break;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                break;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                break;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                break;

            if (--n4 == 0)
                goto last_chars;
        }

        n = n - (s1 - s) - 1;
        if (n == 0)
            return s;
        goto zero_fill;
    }

last_chars:
    n &= 3;
    if (n == 0)
        return s;

    do
    {
        c = *s2++;
        *++s1 = c;
        if (--n == 0)
            return s;
    } while (c != '\0');

zero_fill:
    do
    {
        *++s1 = '\0';
    } while (--n > 0);

    return s;
}


/**
 * \function 	str_cat
 * \brief		this function Append SRC on the end of DEST
 *
 * \param[in]  	dest- the destination of string
 * \param[in] 	src - the source of string
 *
 * \return	   	return the last position of destination
 *
 */
char * str_cat(char *dest, const char *src)
{
    char *s1 = dest;
    const char *s2 = src;
    unsigned char c;

    /* Find the end of the string.  */
    do
    {
        c = *s1++;
    } while (c != '\0');

    /* Make S1 point before the next character, so we can increment
       it while memory is read (wins on pipelined cpus).  */
    s1 -= 2;

    do
    {
        c = *s2++;
        *++s1 = c;
    } while (c != '\0');

    return dest;
}

/**
 * \function 	strn_cat
 * \brief		this function Append SRC on the end of DEST, append maximum n characters
 *
 * \param[in]  	s1 - the destination of string
 * \param[in] 	s2 - the source of string
 * \param[in] 	n  - the length that append maximum
 *
 * \return	   	return the last position of destination
 */
char *strn_cat(char *s1, const char *s2, size_t n)
{
    unsigned char c;
    char *s = s1;

    /* Find the end of S1.  */
    do
    {
        c = *s1++;
    } while (c != '\0');

    /* Make S1 point before next character, so we can increment
       it while memory is read (wins on pipelined cpus).  */
    s1 -= 2;

    if (n >= 4)
    {
        size_t n4 = n >> 2;
        do
        {
            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                return s;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                return s;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                return s;

            c = *s2++;
            *++s1 = c;
            if (c == '\0')
                return s;

        } while(--n4 > 0);

        n &= 3;
    }

    while (n > 0)
    {
        c = *s2++;
        *++s1 = c;

        if (c == '\0')
            return s;
        n--;
    }

    if(c != '\0')
        *++s1 = '\0';

    return s;
}

/**
 * \function 	str_cmp
 * \brief		this function Compare S1 and S2, returning less than, equal to or
 *  			greater than zero if S1 is lexicographically less than,
 *  			equal to or greater than S2.
 *
 * \param[in]  	p1 - the string p1 to compare with
 * \param[in] 	p2 - the string p2 to compare with
 *
 * \return	   	0 if equal, >0 if p1>p2, or <0 if p1<p2
 */
int str_cmp (const char *p1, const char *p2)
{
    register const unsigned char *s1 = (const unsigned char *) p1;
    register const unsigned char *s2 = (const unsigned char *) p2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0')
            return c1 - c2;

    } while (c1 == c2);

    return c1 - c2;
}

/**
 * \function 	strn_cmp
 * \brief		this function Compare no more than N characters of S1 and S2,
 *  			returning less than, equal to or greater than zero
 * 				if S1 is lexicographically less than, equal to or greater than S2.
 *
 * \param[in]  	p1 - the string p1 to compare with
 * \param[in] 	p2 - the string p2 to compare with
 * \param[in] 	n  - the length that maximum to compare
 *
 * \return	   	0 if equal, >0 if p1>p2, or <0 if p1<p2
 */
int strn_cmp(const char *s1, const char *s2, size_t n)
{
    unsigned char c1 = '\0';
    unsigned char c2 = '\0';

    if (n >= 4)
    {
        size_t n4 = n >> 2;
        do
        {
            c1 = (unsigned char) *s1++;
            c2 = (unsigned char) *s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (unsigned char) *s1++;
            c2 = (unsigned char) *s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (unsigned char) *s1++;
            c2 = (unsigned char) *s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;

            c1 = (unsigned char) *s1++;
            c2 = (unsigned char) *s2++;
            if (c1 == '\0' || c1 != c2)
                return c1 - c2;
        } while (--n4 > 0);

        n &= 3;
    }

    while (n > 0)
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
        if (c1 == '\0' || c1 != c2)
            return c1 - c2;
        n--;
    }

    return c1 - c2;
}


/**
 * \function 	str_len
 * \brief		this function Return the length of the null-terminated string STR.  Scan for
 * 				the null terminator quickly by testing four bytes at a time. *
 *
 * \param[in]  	str - the string to calculate length
 *
 * \return	   	the length of str
 */
size_t str_len (const char *str)
{
    const char *char_ptr;
    const unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;

    /* Handle the first few characters by reading one character at a time.
    Do this until CHAR_PTR is aligned on a longword boundary.  */
    for (char_ptr = str; ((unsigned long int) char_ptr
                          & (sizeof (longword) - 1)) != 0;
            ++char_ptr)
        if (*char_ptr == '\0')
            return char_ptr - str;

    /* All these elucidatory comments refer to 4-byte longwords,
    but the theory applies equally well to 8-byte longwords.  */

    longword_ptr = (unsigned long int *) char_ptr;

    /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
    the "holes."  Note that there is a hole just to the left of
    each byte, with an extra at the end:

    bits:  01111110 11111110 11111110 11111111
    bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

    The 1-bits make sure that carries propagate to the next 0-bit.
    The 0-bits provide holes for carries to fall into.  */
    himagic = HIGH_MAGIC;
    lomagic = LOW_MAGIC;
    if (sizeof (longword) > 4)
    {
        /* 64-bit version of the magic.  */
        /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }

    if (sizeof (longword) > 8)
        ASSERT(0);

    /* Instead of the traditional loop which tests each character,
    we will test a longword at a time.  The tricky part is testing
    if *any of the four* bytes in the longword in question are zero.  */
    for (;;)
    {
        longword = *longword_ptr++;

        if (((longword - lomagic) & ~longword & himagic) != 0)
        {
            /* Which of the bytes was the zero?  If none of them were, it was
            a misfire; continue the search.  */

            const char *cp = (const char *) (longword_ptr - 1);

            if (cp[0] == 0)
                return cp - str;
            if (cp[1] == 0)
                return cp - str + 1;
            if (cp[2] == 0)
                return cp - str + 2;
            if (cp[3] == 0)
                return cp - str + 3;

            if (sizeof (longword) > 4)
            {
                if (cp[4] == 0)
                    return cp - str + 4;
                if (cp[5] == 0)
                    return cp - str + 5;
                if (cp[6] == 0)
                    return cp - str + 6;
                if (cp[7] == 0)
                    return cp - str + 7;
            }
        }
    }
}

/**
 * \function 	strn_len
 * \brief		Find the length of S, but scan at most MAXLEN characters.  If no
 *			    '\0' terminator is found in that many characters, return MAXLEN.
 *
 * \param[in]  	str - the string to calculate length
 * \param[in]  	maxlen - the max len
 *
 * \return	   	the length of str
 */
size_t strn_len (const char *str, size_t maxlen)
{
    const char *char_ptr, *end_ptr = str + maxlen;
    const unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;

    if (maxlen == 0)
        return 0;

    if (end_ptr < str)
        end_ptr = (const char *) ~0UL;

    /* Handle the first few characters by reading one character at a time.
    Do this until CHAR_PTR is aligned on a longword boundary.  */
    for (char_ptr = str; ((unsigned long int) char_ptr
                          & (sizeof (longword) - 1)) != 0;
            ++char_ptr)
    {
        if (*char_ptr == '\0')
        {
            if (char_ptr > end_ptr)
                char_ptr = end_ptr;
            return char_ptr - str;
        }
    }

    /* All these elucidatory comments refer to 4-byte longwords,
    but the theory applies equally well to 8-byte longwords.  */

    longword_ptr = (unsigned long int *) char_ptr;

    /* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
    the "holes."  Note that there is a hole just to the left of
    each byte, with an extra at the end:

    bits:  01111110 11111110 11111110 11111111
    bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

    The 1-bits make sure that carries propagate to the next 0-bit.
    The 0-bits provide holes for carries to fall into.  */
    himagic = HIGH_MAGIC;
    lomagic = LOW_MAGIC;
    if (sizeof (longword) > 4)
    {
        /* 64-bit version of the magic.  */
        /* Do the shift in two steps to avoid a warning if long has 32 bits.  */
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }

    if (sizeof (longword) > 8)
        ASSERT(0);

    /* Instead of the traditional loop which tests each character,
    we will test a longword at a time.  The tricky part is testing
    if *any of the four* bytes in the longword in question are zero.  */
    while (longword_ptr < (unsigned long int *) end_ptr)
    {
        /* We tentatively exit the loop if adding MAGIC_BITS to
        LONGWORD fails to change any of the hole bits of LONGWORD.

        1) Is this safe?  Will it catch all the zero bytes?
        Suppose there is a byte with all zeros.  Any carry bits
        propagating from its left will fall into the hole at its
        least significant bit and stop.  Since there will be no
        carry from its most significant bit, the LSB of the
        byte to the left will be unchanged, and the zero will be
        detected.

        2) Is this worthwhile?  Will it ignore everything except
        zero bytes?  Suppose every byte of LONGWORD has a bit set
        somewhere.  There will be a carry into bit 8.  If bit 8
        is set, this will carry into bit 16.  If bit 8 is clear,
        one of bits 9-15 must be set, so there will be a carry
        into bit 16.  Similarly, there will be a carry into bit
        24.  If one of bits 24-30 is set, there will be a carry
        into bit 31, so all of the hole bits will be changed.

        The one misfire occurs when bits 24-30 are clear and bit
        31 is set; in this case, the hole at bit 31 is not
        changed.  If we had access to the processor carry flag,
        we could close this loophole by putting the fourth hole
        at bit 32!

        So it ignores everything except 128's, when they're aligned
        properly.  */

        longword = *longword_ptr++;

        if ((longword - lomagic) & himagic)
        {
            /* Which of the bytes was the zero?  If none of them were, it was
            a misfire; continue the search.  */

            const char *cp = (const char *) (longword_ptr - 1);

            char_ptr = cp;
            if (cp[0] == 0)
                break;
            char_ptr = cp + 1;
            if (cp[1] == 0)
                break;
            char_ptr = cp + 2;
            if (cp[2] == 0)
                break;
            char_ptr = cp + 3;
            if (cp[3] == 0)
                break;
            if (sizeof (longword) > 4)
            {
                char_ptr = cp + 4;
                if (cp[4] == 0)
                    break;
                char_ptr = cp + 5;
                if (cp[5] == 0)
                    break;
                char_ptr = cp + 6;
                if (cp[6] == 0)
                    break;
                char_ptr = cp + 7;
                if (cp[7] == 0)
                    break;
            }
        }
        char_ptr = end_ptr;
    }

    if (char_ptr > end_ptr)
        char_ptr = end_ptr;

    return char_ptr - str;
}


