#ifndef __USART_H__
#define __USART_H__
#include "stm32f10x.h"

#define  USART1_TX_GPIO_PORT       GPIOA
#define  USART1_TX_GPIO_PIN        GPIO_Pin_9
#define  USART1_RX_GPIO_PORT       GPIOA
#define  USART1_RX_GPIO_PIN        GPIO_Pin_10

void usart1_init(void);
void print(const char *fmt, ...);

#endif /* __USART_H__ */
