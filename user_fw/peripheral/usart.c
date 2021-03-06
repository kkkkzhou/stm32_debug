#include "usart.h"
#include "arm_init.h"
#include "lib.h"

typedef char *va_list;
typedef int native_int;

/* Storage alignment properties */
#define _AUPBND (sizeof(native_int) - 1)
#define _ADNBND (sizeof(native_int) - 1)

/* Variable argument list macro definitions */
#define _bnd(X, bnd)    (((sizeof(X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)   (*(T *)(((ap) += (_bnd(T, _AUPBND))) - (_bnd(T, _ADNBND))))
#define va_end(ap)      (void)0
#define va_start(ap, A) (void)((ap) = (((char *)&(A)) + (_bnd(A, _AUPBND))))

//
// The Uart command interface promote
u8 promote[] = "USART>";

//
// The Uart receive buffer, can receive UART_BUFFER_SIZE character at max
char uart_buffer[UART_BUFFER_SIZE];

//
// How many character received now
u32 uart_received_counter = 0;

//
// Whether echo characters
u8 not_echo = 0;
char echo_str[10];

static void usart_struct_init(USART_TypeDef *usart_x,
                              u32 baud, u16 wordlen,
                              u16 stopbits, u16 parity,
                              u16 mode, u16 flowcontrol)
{
    USART_InitTypeDef usart_init_struct;
    mem_set(&usart_init_struct, 0, sizeof(USART_InitTypeDef));

    usart_init_struct.USART_BaudRate = baud;
    usart_init_struct.USART_WordLength = wordlen;
    usart_init_struct.USART_StopBits = stopbits;
    usart_init_struct.USART_Parity = parity;
    usart_init_struct.USART_Mode = mode;
    usart_init_struct.USART_HardwareFlowControl = flowcontrol;

    USART_Init(usart_x, &usart_init_struct);
}

static void usart_interrupt_config(USART_TypeDef *usart_x, u16 usart_it, FunctionalState state)
{
    USART_ITConfig(usart_x, usart_it, state);
}

static void usart_enable(USART_TypeDef *usart_x)
{
    USART_Cmd(usart_x, ENABLE);
}

#if 0
static void usart_disable(USART_TypeDef *usart_x)
{
    USART_Cmd(usart_x, DISABLE);
}
#endif

void usart1_init(void)
{
    // enable GPIO and usart clock
    enable_apb2_clock(RCC_APB2Periph_GPIOA);
    enable_apb2_clock(RCC_APB2Periph_USART1);

    // GPIO config
    gpio_config(USART1_TX_GPIO_PORT, USART1_TX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    gpio_config(USART1_RX_GPIO_PORT, USART1_RX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
    usart_struct_init(USART1, 115200, USART_WordLength_8b,
                      USART_StopBits_1, USART_Parity_No,
                      USART_Mode_Rx | USART_Mode_Tx,
                      USART_HardwareFlowControl_None);

    // config nvic for usart1
    nvic_irq_config(NVIC_PriorityGroup_2, USART1_IRQn, 1, 1, ENABLE);
    usart_interrupt_config(USART1, USART_IT_RXNE, ENABLE);
    usart_enable(USART1);
}

void usart2_init(void)
{
    // enable GPIO and usart clock
    enable_apb2_clock(RCC_APB2Periph_GPIOA);
    enable_apb1_clock(RCC_APB1Periph_USART2);

    // GPIO config
    gpio_config(USART2_TX_GPIO_PORT, USART2_TX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    gpio_config(USART2_RX_GPIO_PORT, USART2_RX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
    usart_struct_init(USART2, 115200, USART_WordLength_8b,
                      USART_StopBits_1, USART_Parity_No,
                      USART_Mode_Rx | USART_Mode_Tx,
                      USART_HardwareFlowControl_None);

    // config nvic for usart2
    nvic_irq_config(NVIC_PriorityGroup_2, USART2_IRQn, 1, 1, ENABLE);
    usart_interrupt_config(USART2, USART_IT_RXNE, ENABLE);
    usart_enable(USART2);
}

void usart3_init(void)
{
    // enable GPIO and usart clock
    enable_apb2_clock(RCC_APB2Periph_GPIOB);
    enable_apb1_clock(RCC_APB1Periph_USART3);

    // GPIO config
    gpio_config(USART3_TX_GPIO_PORT, USART3_TX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
    gpio_config(USART3_RX_GPIO_PORT, USART3_RX_GPIO_PIN, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
    usart_struct_init(USART3, 115200, USART_WordLength_8b,
                      USART_StopBits_1, USART_Parity_No,
                      USART_Mode_Rx | USART_Mode_Tx,
                      USART_HardwareFlowControl_None);

    // config nvic for usart3
    nvic_irq_config(NVIC_PriorityGroup_2, USART3_IRQn, 1, 1, ENABLE);
    usart_interrupt_config(USART3, USART_IT_RXNE, ENABLE);
    usart_enable(USART3);
}

void uart_send_char_port(USART_TypeDef *uart_port, u8 ch)
{
    USART_SendData(uart_port, ch);
    while (USART_GetFlagStatus(uart_port, USART_FLAG_TXE) == RESET)
        ;
}

void uart_send_char(u8 c)
{
    uart_send_char_port(USART1, c);
}

/**
 * \function    put_char
 * \brief               this function send a character outof uart port
 *
 * \param[in]   c - the character to send out
 *
 * \return
 *
 */
OPTI_S void put_char(char c)
{
    uart_send_char(c);
}

/**
 * \function    put_str
 * \brief       this function send a string outof uart port
 *
 * \param[in]   str - the string to send out
 *
 * \return
 *
 */
OPTI_S void put_str(const char *str)
{
    while (*str)
        put_char(*str++);
}

/**
 * \function    vprintfmt
 * \brief       print a format string to vargs
 *
 * \param[in]   fmt - the format string
 * \param[in]   arp - the arg list
 *
 * \return
 *
 */
OPTI_S void vprintfmt(const char *fmt, va_list arp)
{
    unsigned int r, i, j, w, f;
    unsigned long v;
    char s[16], c, d, *p;

    for (;;) {
        c = *fmt++; /* Get a char */
        if (!c)
            break;      /* End of format? */
        if (c != '%') { /* Pass through it if not a % sequense */
            put_char(c);
            continue;
        }

        f = 0;
        c = *fmt++;     /* Get first char of the sequense */
        if (c == '0') { /* Flag: '0' padded */
            f = 1;
            c = *fmt++;
        } else {
            if (c == '-') { /* Flag: left justified */
                f = 2;
                c = *fmt++;
            }
        }

        for (w = 0; c >= '0' && c <= '9'; c = *fmt++) /* Minimum width */
        {
            w = w * 10 + c - '0';
        }

        if (c == 'l' || c == 'L') { /* Prefix: Size is long int */
            f |= 4;
            c = *fmt++;
        }

        if (!c)
            break; /* End of format? */

        d = c;

        if (d >= 'a')
            d -= ASCII_SPACE;

        switch (d) { /* Type is... */
        case 'S':    /* String */
            p = va_arg(arp, char *);
            for (j = 0; p[j]; j++)
                ;

            while (!(f & 2) && j++ < w)
                put_char(' ');

            put_str(p);

            while (j++ < w)
                put_char(' ');

            continue;
        case 'C': /* Character */
            put_char((char)va_arg(arp, int));
            continue;
        case 'B': /* Binary */
            r = 2;
            break;
        case 'O': /* Octal */
            r = 8;
            break;
        case 'D': /* Signed decimal */
        case 'U': /* Unsigned decimal */
            r = 10;
            break;
        case 'X': /* Hexdecimal */
            r = 16;
            break;
        default: /* Unknown type (passthrough) */
            put_char(c);
            continue;
        }

        /* Get an argument and put it in numeral */
        v = (f & 4) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, unsigned int));

        if (d == 'D' && (v & PRINT_PLURAL_MASK)) {
            v = 0 - v;
            f |= 8;
        }

        i = 0;

        do {
            d = (char)(v % r);
            v /= r;
            if (d > 9)
                d += (c == 'x') ? ASCII_APOSTROPHE : ASCII_BELL;

            s[i++] = d + '0';
        } while (v && i < sizeof(s));

        if (f & 8)
            s[i++] = '-';

        j = i;
        d = (f & 1) ? '0' : ' ';

        while (!(f & 2) && j++ < w)
            put_char(d);

        do {
            put_char(s[--i]);
        } while (i);

        while (j++ < w)
            put_char(' ');
    }
}

/**
 * \function    print
 * \brief               print a format string to uart port
 *
 * \param[in]   fmt - the format string
 *
 * \return
 *
 */
void print(const char *fmt, ...)
{
    va_list arp;
    va_start(arp, fmt);
    vprintfmt(fmt, arp);
    va_end(arp);
}

void usart_isr(USART_TypeDef *usart_x)
{
    u8 c = USART_ReceiveData(usart_x);

    // If the character not \r, then we need echo it
    if (c != '\r' && c != '\n') {
        // Delete one Character
        if (c == BACKSPACE || c == BACKSPACE2) {
            if (uart_received_counter > 0) {
                // Delete one char
                uart_received_counter--;
                uart_buffer[uart_received_counter] = '\0';

                // If configred that echo user inputs, then output this character to terminal
                if (!not_echo) {
                    echo_str[0] = BACKSPACE;
                    echo_str[1] = ' '; // output blank to erase character user input
                    echo_str[2] = BACKSPACE;
                    echo_str[3] = EOS;
                    print(echo_str);
                }
            }
        }
        // Normal character, save it
        else {
            // Echo received char
            if (uart_received_counter < (UART_BUFFER_SIZE - 1)) {
                if (!not_echo) {
                    // Echo it
                    echo_str[0] = c;
                    echo_str[1] = EOS;
                    print(echo_str);
                }

                // Save character
                uart_buffer[uart_received_counter++] = c;
            }
        }
    } else {
        uart_buffer[uart_received_counter] = EOS;
        uart_received_counter = 0;
        if (!not_echo) {
            print("\n");
        }
        //print((char *)&promote[0]);
    }
}

/*********************************************END OF FILE**********************/
