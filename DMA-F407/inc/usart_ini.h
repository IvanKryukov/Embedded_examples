#ifndef USART_INI
#define USART_INI

#include "stm32f4xx.h"
#include "main.h"

void USART_INIT(USART_TypeDef* USARTx);
void USART_Send(USART_TypeDef* USARTx, uint8_t SendData);
void USART_Send_SeparatedData(USART_TypeDef* USARTx, uint16_t SendData);
uint32_t USARTx_BRRegister(uint32_t BaudRate, uint32_t APBxCLK);

#endif

