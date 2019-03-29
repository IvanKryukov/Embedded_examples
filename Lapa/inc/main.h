#ifndef MAIN_H
#define MAIN_H

#include "mcu_config.h"
#include "crc16ccitt.h"

void delay(uint32_t count);
void delay_ms(uint32_t count);
void delay_us(uint32_t count);
void USART1_Send(uint8_t SendData);
void USART_Send_SeparatedData(uint16_t SendData);
void USART_Send_CompressedData(uint16_t SendData);
void USART1_SendAll(uint8_t send_status);
void USART_BT_Send(uint8_t *ArrData, uint8_t CountData);
void ADC1_2_IRQHandler(void);
uint16_t create_crc16(uint8_t create_status);
int main(void);

#endif

