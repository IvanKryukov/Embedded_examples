#ifndef __STM_CONFIG_H
#define __STM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported functions ------------------------------------------------------- */

void SYSCLK_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void SPI_Configuration(void);
void TIM3_Configuration(uint32_t tim);
void ADC_Channel1_Configuration(void);
void ADC_Channel2_Configuration(void);
void ADC_Channel_1_2_Configuration(void);
void DMA_Configuration(void);




#endif


