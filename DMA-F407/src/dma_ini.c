#include "dma_ini.h"

/**********************
 * DMA INITIALIZATION *
 **********************/

void DMA_INIT(DMA_TypeDef* DMAy, DMA_Stream_TypeDef* DMAy_StreamX, uint8_t DMA_Buff)
{	
	if (DMAy == DMA1) RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	if (DMAy == DMA2) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	
	/***** Set channel *****/
	DMAy_StreamX->CR |= DMA_SxCR_CHSEL_2; // Stream3 Channel4 (100)
	
	/***** Set peripheral and memory address registers, set the direction	*****/
	DMAy_StreamX->PAR = (uint32_t)&(USART3->DR);	// Peripheral address register (pointer to USART3 data register)
	DMAy_StreamX->M0AR = (uint32_t)&DMA_Buff;			// Memory0 address register (variable DMA_Buff)
	DMAy_StreamX->CR &= ~DMA_SxCR_DIR;						
	DMAy_StreamX->CR |= DMA_SxCR_DIR_0;							// Data transfer direction - Memory-to-Peripheral
	DMAy_StreamX->NDTR = sizeof(DMA_Buff);				// Number of data register
	
	/***** Set data size, increnemt modes and circular mode *****/
	DMAy_StreamX->CR &= ~DMA_SxCR_MSIZE;	// Memory data size - 1 byte (8 bit)
	DMAy_StreamX->CR &= ~DMA_SxCR_PSIZE;	// Peripheral Data Size - 1 byte (8 bit)
	DMAy_StreamX->CR &= ~DMA_SxCR_MINC;		// Memory increment mode is OFF (address pointer is incremented)
	DMAy_StreamX->CR &= ~DMA_SxCR_PINC;		// Peripheral increment mode is OFF (address pointer is fixed)
	DMAy_StreamX->CR &= ~DMA_SxCR_CIRC;
	DMAy_StreamX->CR &= ~DMA_SxCR_CIRC;		// Circular mode is disable (Single mode)
	//DMAy_StreamX->CR |= DMA_SxCR_PFCTRL;	// Peripheral flow controller: The DMA is the flow controller
	
	/***** Set priority level *****/
	DMAy_StreamX->CR &= ~DMA_SxCR_PL;			
	DMAy_StreamX->CR |= DMA_SxCR_PL_0;		// Priority level:  Medium
	
	/***** Set FIFO features *****/
	DMAy_StreamX->FCR &= ~DMA_SxFCR_FEIE;	// FIFO error interrupt disable
	DMAy_StreamX->FCR &= ~DMA_SxFCR_FTH;	// FIFO threshold selection: 1/4 FIFO
	DMAy_StreamX->FCR |= DMA_SxFCR_FTH_0;	// FIFO threshold selection: half/full FIFO
	
	/***** Set peripheral and memory burst transfer configuration *****/
	DMAy_StreamX->CR &= ~DMA_SxCR_MBURST;	// Memory burst transfer configuration: Single transfer
	DMAy_StreamX->CR &= ~DMA_SxCR_PBURST;	// Peripheral burst transfer configuration: Single transfer
	
	//DMAy_StreamX->FCR &= ~DMA_SxCR_CT;
	
	DMAy_StreamX->CR |= DMA_SxCR_TCIE;		// Transfer complete interrupt enable	
	//DMAy_StreamX->CR |= DMA_SxCR_EN;			// DMA1 Stream1 Enable
	
	/***** Enable interrupt on DMA1_StreamX *****/
	if (DMAy_StreamX == DMA1_Stream0) NVIC_EnableIRQ(DMA1_Stream0_IRQn);		
	if (DMAy_StreamX == DMA1_Stream1) NVIC_EnableIRQ(DMA1_Stream1_IRQn);
	if (DMAy_StreamX == DMA1_Stream2) NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	if (DMAy_StreamX == DMA1_Stream3) NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	if (DMAy_StreamX == DMA1_Stream4) NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	if (DMAy_StreamX == DMA1_Stream5) NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	if (DMAy_StreamX == DMA1_Stream6) NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	if (DMAy_StreamX == DMA1_Stream7) NVIC_EnableIRQ(DMA1_Stream7_IRQn);
	
	if (DMAy_StreamX == DMA2_Stream0) NVIC_EnableIRQ(DMA2_Stream0_IRQn);		
	if (DMAy_StreamX == DMA2_Stream1) NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	if (DMAy_StreamX == DMA2_Stream2) NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	if (DMAy_StreamX == DMA2_Stream3) NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	if (DMAy_StreamX == DMA2_Stream4) NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	if (DMAy_StreamX == DMA2_Stream5) NVIC_EnableIRQ(DMA2_Stream5_IRQn);
	if (DMAy_StreamX == DMA2_Stream6) NVIC_EnableIRQ(DMA2_Stream6_IRQn);
	if (DMAy_StreamX == DMA2_Stream7) NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}

void DMA1_SET(DMA_Stream_TypeDef* DMAy_StreamX)
{
	DMAy_StreamX->CR |= DMA_SxCR_EN;			// DMA1 StreamX Enable
}
  
