#include "usart_ini.h"

/************************
 * USART INITIALIZATION *
 ************************/
 
void USART_INIT(USART_TypeDef* USARTx)
{
	/***** Set USART Clock *****/
	if (USARTx == USART1) RCC->APB2ENR|= RCC_APB2ENR_USART1EN;
	if (USARTx == USART2) RCC->APB1ENR|= RCC_APB1ENR_USART2EN;
	if (USARTx == USART3) RCC->APB1ENR|= RCC_APB1ENR_USART3EN;
	if (USARTx == USART6) RCC->APB2ENR|= RCC_APB2ENR_USART6EN;

	/***** Set USART *****/
	USARTx->CR1 &= ~USART_CR1_M;		// Start bit, 8 Data bits, n Stop bit
	USARTx->CR2 &= ~USART_CR2_STOP;	// 1 Stop bit
	USARTx->BRR = USARTx_BRRegister(9600, 1000000);
	//USARTx->BRR = 0x341; 					// for 16MHz 9600 baudrate
	//USARTx->BRR = 0x1940; 					// for 120MHz 9600 baudrate
	USARTx->CR1 |= USART_CR1_RE;		// Receiver enable
	USARTx->CR1 |= USART_CR1_TE;		// Transmitter enable
	//USARTx->CR1 |= USART_CR1_RXNEIE;	// RXNE interrupt enable 
	//USARTx->CR1 |= USART_CR1_TCIE;		// Transmit complete (TC) interrupt enable
	USARTx->CR3 |= USART_CR3_DMAT;	// DMA mode is enabled for reception
	
	USARTx->CR1 |= USART_CR1_UE;		// USARTx Enable
	
	if (USARTx == USART1) NVIC_EnableIRQ(USART1_IRQn);
	if (USARTx == USART2) NVIC_EnableIRQ(USART2_IRQn);
	if (USARTx == USART3) NVIC_EnableIRQ(USART3_IRQn);
	if (USARTx == USART6) NVIC_EnableIRQ(USART6_IRQn);

}

/********************
 * USART1 FUNCTIONS *
 ********************/

/* Transmit USART1 Data and waiting for the end of transfer */
void USART_Send(USART_TypeDef* USARTx, uint8_t SendData)
{
	uint8_t buff;
	buff = SendData;
	//GPIOD->BSRRL |= GPIO_BSRR_BR_9;
	USARTx->DR = buff;
	while((USARTx->SR & USART_SR_TC) == 0 ) {} // Waiting for completed transfer
	//GPIOD->BSRRL |= GPIO_BSRR_BS_9;
}

/* Separate data and send it */
void USART_Send_SeparatedData(USART_TypeDef* USARTx, uint16_t SendData) 
{
	uint8_t part_data = 0xFF;	// Variable for saving data
	
	part_data &= SendData;		// Save first 8 bit of data
	USART_Send(USARTx, part_data);		// Transmit first 8 bit of data

	part_data = 0xFF;					// Variable for saving data
	SendData >>= 0x8;						// Shift data by 8 bits
	part_data &= SendData;		// Save last 8 bit of data
	USART_Send(USARTx, part_data);		// Transmit last 8 bit of data
}

uint32_t USARTx_BRRegister(uint32_t BaudRate, uint32_t APBxCLK)
{
	double BR_All;
	uint32_t BR_Reg;
	
	BR_All = APBxCLK / BaudRate; /* / 16; */
	BR_Reg = (uint32_t)BR_All;
	
	return BR_Reg;
}
