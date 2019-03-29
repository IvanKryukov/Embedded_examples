/* Includes ------------------------------------------------------------------*/
#include "stm_config.h"

/* Exported types ----------------------------------------------------------- */
uint16_t DataOut[2500];
uint8_t DataIn[10];
uint32_t adc_ctrl = 0;

/* Description functions ------------------------------------------------------- */

/*******************************************************************************
 SYSCLK Configuration(28MHz)
 *******************************************************************************/
 void SYSCLK_Configuration(void)
{
	RCC->CFGR=0;
	RCC->CFGR &= ~(RCC_CFGR_SW);
	while ((RCC->CFGR & RCC_CFGR_SWS) != (uint32_t)0x00){} 

	RCC->CR &=~(RCC_CR_PLLON);
	while((RCC->CR & RCC_CR_PLLRDY) == 1) {}

	RCC->CFGR &=~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
	RCC->CFGR |= RCC_CFGR_PLLMULL7;

	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {}
		
	RCC->CFGR &= ~(RCC_CFGR_SW);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != (uint32_t)0x08){} 
}

/*******************************************************************************
 GPIO Configuration
 *******************************************************************************/
void GPIO_Configuration(void)
{
	RCC->APB2ENR|= (RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPDEN|RCC_APB2ENR_AFIOEN);

	//USART1_TX(PA9)
	GPIOA->CRH |= (GPIO_CRH_CNF9_1|GPIO_CRH_MODE9);

	//USART1_RX(PA10)
	GPIOA->CRH |=GPIO_CRH_CNF10_0;
	GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
	GPIOA->CRH &= ~GPIO_CRH_MODE10;

	/*USART3_TX(PB10)
	GPIOB->CRH |= (GPIO_CRH_CNF10_1|GPIO_CRH_MODE10);


	//USART3_RX(PB11)
	GPIOB->CRH |= GPIO_CRH_CNF11_0;
	GPIOB->CRH &= ~GPIO_CRH_CNF11_1;
	GPIOB->CRH &= ~GPIO_CRH_MODE11;
	*/

	/*SPI1_MOSI(PA7)
	GPIOA->CRL |= GPIO_CRL_MODE7;    
	GPIOA->CRL &= ~GPIO_CRL_CNF7;     
	GPIOA->CRL |= GPIO_CRL_CNF7_1;  
	
	//SPI1_SCK(PA5)
	GPIOA->CRL |= GPIO_CRL_MODE5;    
	GPIOA->CRL &= ~GPIO_CRL_CNF5;    
	GPIOA->CRL |= GPIO_CRL_CNF5_1;

	//SPI1_NSS(PA4)
	GPIOA->CRL |= GPIO_CRL_MODE4;    
	GPIOA->CRL &= ~GPIO_CRL_CNF4;     
	GPIOA->BSRR = GPIO_BSRR_BS4;
	*/
	
	//ADC1(PC1)
	GPIOC->CRL &= ~GPIO_CRL_CNF1;
	GPIOC->CRL &= ~GPIO_CRL_MODE1;
	
	//ADC1(PC3)
	GPIOC->CRL &= ~GPIO_CRL_CNF3;
	GPIOC->CRL &= ~GPIO_CRL_MODE3;
	
	//GPIOA(0,1,2,3)
	GPIOA->CRL |= (GPIO_CRL_MODE0|GPIO_CRL_MODE1|GPIO_CRL_MODE2|GPIO_CRL_MODE3);
	GPIOA->CRL &= ~(GPIO_CRL_CNF0|GPIO_CRL_CNF1|GPIO_CRL_CNF2|GPIO_CRL_CNF3);
	
	//GPIOB(0,1,6,7,8,9,13,14)
	GPIOB->CRH |= (GPIO_CRH_MODE8|GPIO_CRH_MODE9|GPIO_CRH_MODE13|GPIO_CRH_MODE14);
	GPIOB->CRH &= ~(GPIO_CRH_CNF8|GPIO_CRH_CNF9|GPIO_CRH_CNF13|GPIO_CRH_CNF14);
	GPIOB->CRL |= (GPIO_CRL_MODE0|GPIO_CRL_MODE1|GPIO_CRL_MODE6|GPIO_CRL_MODE7);
	GPIOB->CRL &= ~(GPIO_CRL_CNF0|GPIO_CRL_CNF1|GPIO_CRL_CNF6|GPIO_CRL_CNF7);
	
	//GPIOC(0,4,5,6,13,14,15)
	GPIOC->CRL |= (GPIO_CRL_MODE0|GPIO_CRL_MODE4|GPIO_CRL_MODE5|GPIO_CRL_MODE6);
	GPIOC->CRL &= ~(GPIO_CRL_CNF0|GPIO_CRL_CNF4|GPIO_CRL_CNF5|GPIO_CRL_CNF6);
	GPIOC->CRH |= (GPIO_CRH_MODE13|GPIO_CRH_MODE14|GPIO_CRH_MODE15);
	GPIOC->CRH &= ~(GPIO_CRH_CNF13|GPIO_CRH_CNF14|GPIO_CRH_CNF15);
	
	//GPIOD(0,1)
	GPIOD->CRL |= (GPIO_CRL_MODE0|GPIO_CRL_MODE1);
	GPIOD->CRL &= ~(GPIO_CRL_CNF0|GPIO_CRL_CNF1);
}

/*******************************************************************************
 USART Configuration(128000 bps)
 *******************************************************************************/
void USART_Configuration(void)
{
	RCC->APB2ENR|= RCC_APB2ENR_USART1EN;// USART For PC
	RCC->APB1ENR|= RCC_APB1ENR_USART3EN;// USART For Pic

	USART1->CR1 |= USART_CR1_UE;
	USART1->CR1 &= ~USART_CR1_M;
	USART1->CR2 &= ~USART_CR2_STOP;
	USART1->BRR = 0xDB;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR3 |=  USART_CR3_DMAR;  
	/*
	USART3->CR1 |= USART_CR1_UE;
	USART3->CR1 &= ~USART_CR1_M;
	USART3->CR2 &= ~USART_CR2_STOP;
	USART3->BRR = 0x2D9;
	USART3->CR1 |= USART_CR1_RE;
	USART3->CR1 |= USART_CR1_TE;
	*/
}

/*******************************************************************************
 SPI Configuration(For DDS)
 *******************************************************************************
void SPI_Configuration(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	SPI1->CR1 = 0x0000;           
	SPI1->CR2 = 0x0000;  
	SPI1->CR1 |= SPI_CR1_CPOL;	
	SPI1->CR1 |= SPI_CR1_MSTR; 
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST; 	
	SPI1->CR1 |= (SPI_CR1_BR_0|SPI_CR1_BR_1);         
	SPI1->CR1 |= SPI_CR1_SSI;        
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR1 |= SPI_CR1_SPE;       
}*/

/*******************************************************************************
 Timer Configuration (for ADC start)
 *******************************************************************************/
void TIM3_Configuration(uint32_t tim)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM3->PSC = tim;
	TIM3->ARR = 1;
	TIM3->CR2 |= TIM_CR2_MMS_1;          
	TIM3->DIER |= TIM_DIER_UDE;
	TIM3->CR1 |= TIM_CR1_CEN; 
}

/*******************************************************************************
 ADC Configuration (Channel 1)
 *******************************************************************************/
void ADC_Channel1_Configuration(void) 
{
	RCC->CFGR&= ~RCC_CFGR_ADCPRE;
	RCC->CFGR|=RCC_CFGR_ADCPRE_DIV2;
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;

	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){ }
	
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	if (adc_ctrl == 0)
	{
		ADC1->CR2 &= ~ADC_CR2_EXTSEL;
		ADC1->CR2 &= ~ADC_CR2_CONT;
		ADC1->CR2 |= ADC_CR2_EXTSEL_2;
	}
	else
	{
		ADC1->CR2 &= ~ADC_CR2_EXTSEL;
		ADC1->CR2 |= ADC_CR2_EXTSEL;
		ADC1->CR2 |= ADC_CR2_CONT;
	}
	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_DMA;		
	ADC1->CR1 &= ~ADC_CR1_SCAN;
	ADC1->SMPR1 &= ~ADC_SMPR1_SMP11;
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_3);
	
	ADC1->CR2 |= ADC_CR2_ADON;
				
}
/*******************************************************************************
 ADC Configuration (Channel 2)
 *******************************************************************************/
void ADC_Channel2_Configuration(void) 
{
	RCC->CFGR&= ~RCC_CFGR_ADCPRE;
	RCC->CFGR|=RCC_CFGR_ADCPRE_DIV2;
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;

	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){ }
	
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	if (adc_ctrl == 0)
	{
		ADC1->CR2 &= ~ADC_CR2_EXTSEL;
		ADC1->CR2 &= ~ADC_CR2_CONT;
		ADC1->CR2 |= ADC_CR2_EXTSEL_2;
	}
	else
	{
		ADC1->CR2 &= ~ADC_CR2_EXTSEL;
		ADC1->CR2 |= ADC_CR2_EXTSEL;
		ADC1->CR2 |= ADC_CR2_CONT;
	}
	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_DMA;		
	ADC1->CR1 &= ~ADC_CR1_SCAN;
	ADC1->SMPR1 &= ~ADC_SMPR1_SMP13;
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_2|ADC_SQR3_SQ1_3);
	
	ADC1->CR2 |= ADC_CR2_ADON;
				
}
/*******************************************************************************
 ADC Configuration (Channel 1&2)
 *******************************************************************************/
void ADC_Channel_1_2_Configuration(void) 
{
	RCC->CFGR&= ~RCC_CFGR_ADCPRE;
	RCC->CFGR|=RCC_CFGR_ADCPRE_DIV2;
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;

	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){ }
	
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	ADC1->CR2 &= ~ADC_CR2_EXTSEL;
	ADC1->CR2 &= ~ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_EXTSEL_2;

	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_DMA;
	
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->SMPR1 &= ~ADC_SMPR1_SMP11;
	ADC1->SMPR1 &= ~ADC_SMPR1_SMP13;
	ADC1->SQR1 |= ADC_SQR1_L_0;
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_3);
	ADC1->SQR3 |= (ADC_SQR3_SQ2_0|ADC_SQR3_SQ2_2|ADC_SQR3_SQ2_3);
	
	ADC1->CR2 |= ADC_CR2_ADON;
				
}
/*******************************************************************************
 DMA Configuration (Channel1 & Channel 5)
 *******************************************************************************
void DMA_Configuration(void)
{
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;


	DMA1_Channel1->CPAR |= (uint32_t) &ADC1->DR; 
	DMA1_Channel1->CMAR |= (uint32_t) &DataOut[0]; 
	DMA1_Channel1->CNDTR = 2500;
	DMA1_Channel1->CCR =  0;
	DMA1_Channel1->CCR &= ~DMA_CCR1_DIR; 
	DMA1_Channel1->CCR &= ~DMA_CCR1_PINC; 
	DMA1_Channel1->CCR |= DMA_CCR1_MINC; 	
	DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;		
	DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_TCIE; 
	DMA1_Channel1->CCR |= DMA_CCR1_EN; 
	

	DMA1_Channel5->CPAR |= (uint32_t) &USART1->DR; 
	DMA1_Channel5->CMAR |= (uint32_t) &DataIn[0]; 
	DMA1_Channel5->CNDTR = 11;
	DMA1_Channel5->CCR =  0;
	DMA1_Channel5->CCR |= DMA_CCR5_CIRC; 
	DMA1_Channel5->CCR &= ~DMA_CCR5_DIR; 
	DMA1_Channel5->CCR &= ~DMA_CCR5_PINC; 
	DMA1_Channel5->CCR |= DMA_CCR5_MINC; 	
	DMA1_Channel5->CCR |= DMA_CCR5_PL;
	DMA1_Channel5->CCR |= DMA_CCR5_TCIE; 
	DMA1_Channel5->CCR |= DMA_CCR5_EN; 
}*/
/* --------------------------------------------------------------------------- */

