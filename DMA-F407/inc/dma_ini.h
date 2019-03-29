#ifndef DMA_INI
#define DMA_INI

#include "stm32f4xx.h"
#include "main.h"

#define DMA_OFF			0
#define DMA_ON			1

void DMA_INIT(DMA_TypeDef* DMAy,DMA_Stream_TypeDef* DMAy_StreamX, uint8_t DMA_Buff);
void DMA1_SET(DMA_Stream_TypeDef* DMAy_StreamX);

#endif

