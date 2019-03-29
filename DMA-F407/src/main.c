#include "main.h"

uint32_t DMA_Buff;

// Sorry for this delay))) That's better than nothing!
void delay_1KCycles(uint32_t del)
{
	del *= 1000;
	while(del--) {};
}

uint32_t x = 0;
uint32_t maxx = 10000;
uint16_t Pack = 'A';

void PWM_LED_Indication(void)
{
	TIM4->CCR1 = x;
	TIM4->CCR2 = maxx - x + 1;
	TIM4->CCR3 = x;
	TIM4->CCR4 = maxx - x + 1;
}

void set_channel(uint8_t num, uint16_t comp)
{
	switch (num)
	{
		case 1:	TIM2->CCR1 = comp;	// PA0
			break;
		case 2:	TIM2->CCR2 = comp;	// PA1
			break;
		case 3: TIM2->CCR3 = comp;	// PA2
			break;
		case 4: TIM2->CCR4 = comp;	// PA3
			break;
		case 5: TIM4->CCR3 = comp;	// PD13
			break;
		case 6: TIM4->CCR4 = comp;	// PD14
			break;
		case 7: TIM3->CCR3 = comp;	// PB0
			break;
		case 8: TIM3->CCR4 = comp;	// PB1
			break;
		case 9: TIM4->CCR1 = comp;	// PD12
			break;
		case 10: TIM4->CCR2 = comp;	// PD13
			break;
		default:
			break;
	}
}
/*
uint8_t rxbuff;
uint8_t n;
uint8_t num;
uint16_t comp, compL, compM;
void USART3_IRQHandler(void)
{
	if (USART3->SR & USART_SR_RXNE)
	{
		USART3->SR &= ~USART_SR_RXNE;
		USART3->SR &= ~USART_SR_TC;
		rxbuff = USART3->DR;
		
		n = rxbuff;
		n >>= 6;	// Remember number of pack
		switch (n)
		{
			case 0:	// Pack is number of power unit
				num = rxbuff;
				num <<= 3;
				num >>= 3;
				break;
			
			case 1:	// Pack is Most Significant 6 bits
				comp = rxbuff;
				comp <<= 10;
				comp >>= 4;
				compM = comp;
				break;
			
			case 2:	// Pack is Least Significant 6 bits
				rxbuff <<= 2;
				rxbuff >>= 2;
				comp |= rxbuff;
				//comp <<= 4;
				compL = rxbuff;
			
				set_channel(num, comp);	// Set the PWM channel
				break;
			
			default: // Nothing
				break;
		}
		//USART3->DR = 0x0;
	}
}
*/

void DMA1_Stream3_IRQHandler(void)
{
	if (DMA1->LISR & DMA_LISR_TCIF3)	
	{
		DMA1->LIFCR |= DMA_LIFCR_CTCIF3;	// Stream 3 clear transfer complete interrupt flag (TCIF)
	}
}

uint8_t Dbuff = 0xA8;
int main()
{
	RCC_INIT();
	GPIO_INIT();
	//TIMER_INIT(TIM2);
	//TIMER_INIT(TIM3);
	TIMER_INIT(TIM4);
	//SPI_INIT(SPI3, SPI_Master, DMA_ON);
	/***** GPIOA Port has some errors with USART (USART1 and USART2)*****/
	//USART_INIT(USART6);
	USART_INIT(USART3);
	DMA_INIT(DMA1, DMA1_Stream3, Dbuff);
	
	while(1)
	{
		delay_1KCycles(10000);
		DMA1_SET(DMA1_Stream3);
		//delay_1KCycles(10000);
		//USART_Send(USART3, Dbuff);
	}
}

