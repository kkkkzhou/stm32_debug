#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"

#define  USART1_TX_GPIO_PORT       GPIOA
#define  USART1_TX_GPIO_PIN        GPIO_Pin_9
#define  USART1_RX_GPIO_PORT       GPIOA
#define  USART1_RX_GPIO_PIN        GPIO_Pin_10

#define BACKSPACE                   '\b'
#define BACKSPACE2                  127
#define CR                          '\r'
#define LINE_FEED                   '\n'
#define ESC                         0x1B
#define EOS                         0
#define UART_BUFFER_SIZE            80

void usart1_init(void);
void print(const char *fmt, ...);
void usart_isr(USART_TypeDef* usart_x);

#endif /* __USART_H__ */
