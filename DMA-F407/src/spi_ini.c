#include "spi_ini.h"

/**********************
 * SPI INITIALIZATION *
 **********************/
 
 void SPI_INIT(SPI_TypeDef* SPIx, uint8_t SPI_MasterSlave_Mode, uint8_t DMA_Mode)
{
	if (SPIx == SPI1) RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	if (SPIx == SPI2) RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	if (SPIx == SPI3) RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

	if (SPI_MasterSlave_Mode != SPI_Slave)
	{	
		SPIx->CR1 &= ~SPI_CR1_BR;			// Set baudrate = f/2 (just clear BR-bits)
		SPIx->CR1 |= SPI_CR1_BR_2;		// Set baudrate = f/32
		SPIx->CR1 |= SPI_CR1_MSTR;		// Master configuration
	}
	else
	{
		SPIx->CR1 &= ~SPI_CR1_MSTR;		// Slave configuration
		SPIx->CR1 |= SPI_CR1_SSM;			// Software slave management
		SPIx->CR1 |= SPI_CR1_SSI;			// Internal slave select
	}

	SPIx->CR1 &= ~SPI_CR1_CPHA;			// Clock Phase: The first clock transition is the first data capture edge
	SPIx->CR1 &= ~SPI_CR1_CPOL;			// Clock Polarity: CK to 0 when idle
	SPIx->CR1 &= ~SPI_CR1_DFF;			// 8-bit data frame format
	SPIx->CR1 &= ~SPI_CR1_LSBFIRST;	// Most Significant Bit first frame format
	
	if (DMA_Mode != DMA_OFF)
	{
		SPIx->CR2 |= SPI_CR2_RXDMAEN;	// Rx buffer DMA enabled
		SPIx->CR2 |= SPI_CR2_TXDMAEN;	// Tx buffer DMA enabled
	}
	else
	{
		SPIx->CR2 &= ~SPI_CR2_RXDMAEN;	// Rx buffer DMA disabled
		SPIx->CR2 &= ~SPI_CR2_TXDMAEN;	// Tx buffer DMA disabled
	}
	
	SPIx->CR1 |= SPI_CR1_SPE;				// SPI Enable
}

void SPI_Send(SPI_TypeDef* SPIx, uint8_t SPI_Data)
{
	SPIx->DR = SPI_Data;
}

