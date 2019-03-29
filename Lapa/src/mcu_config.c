#include "mcu_config.h"

#define F_CPU 		28000000UL
#define TimerTick	F_CPU/1000-1

/************************************************************
GPIO Initialization
*************************************************************/
void GPIO_init(void)
{
	RCC->APB2ENR|= (RCC_APB2ENR_IOPAEN|RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPDEN|RCC_APB2ENR_AFIOEN);
	
	/*****************************************
	USART Ports initialization
	******************************************/
	//USART1_TX(PA9)
	GPIOA->CRH |= (GPIO_CRH_CNF9_1|GPIO_CRH_MODE9);
	//GPIOA->ODR |= GPIO_ODR_ODR9;
	//GPIOA->BSRR = GPIO_BSRR_BS9;
	
	//USART1_RX(PA10)
	GPIOA->CRH &= ~GPIO_CRH_MODE10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF10_0;
	
	//USART2_TX(PA2)
	//GPIOA->CRL |= (GPIO_CRL_CNF2_1|GPIO_CRL_MODE2);
	
	//USART2_RX(PA3)
	//GPIOA->CRL &= ~GPIO_CRL_MODE3;
	//GPIOA->CRL |= GPIO_CRL_CNF3_1;
	//GPIOA->CRL &= ~GPIO_CRL_CNF3_0;
	
	/*****************************************
	ADC Ports initialization
	******************************************/
	//ADC1(PC1)
	GPIOC->CRL &= ~GPIO_CRL_CNF1;
	GPIOC->CRL &= ~GPIO_CRL_MODE1;
	
	//ADC1(PC3)
	GPIOC->CRL &= ~GPIO_CRL_CNF3;
	GPIOC->CRL &= ~GPIO_CRL_MODE3;
}

/************************************************************
TIMER Initialization (Frequency is equal to 28MHz)
*************************************************************/
void Timer_init(void)
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
		
	//SysTick_Config(TimerTick);
}

void Counter_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->ARR &= ~TIM_ARR_ARR;
	TIM2->ARR |= (uint16_t)0x7FFF;
	
	TIM2->CR1 &= ~TIM_CR1_CKD;	
	TIM2->CR1 &= ~TIM_CR1_DIR;
	
	TIM2->PSC = (uint16_t)0x001B;
}

void Counter2_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM3->ARR &= ~TIM_ARR_ARR;
	TIM3->ARR |= (uint16_t)0x7FFF; // FOR DELAY_US
	//TIM3->ARR |= (uint16_t)0x3EB; // FOR DELAY_MS (1000us)
	
	TIM3->CR1 &= ~TIM_CR1_CKD;	
	TIM3->CR1 &= ~TIM_CR1_DIR;
	
	TIM3->PSC = (uint16_t)0x001B;
}

/************************************************************
ADC Initialization
*************************************************************/
void ADC_init_noWD(void)
{
	ADC1->CR2 &= ~ADC_CR2_ADON;
	
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){}

	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 &= ~ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_EXTSEL;
	ADC1->CR2 &= ~ADC_CR2_CONT;
		
	ADC1->CR2 &= ~ADC_CR2_DMA;
	ADC1->CR1 &= ~ADC_CR1_SCAN;
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP1;
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_3);
		
	ADC1->CR1 |= ADC_CR1_EOCIE;

	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	ADC1->CR2 |= ADC_CR2_ADON;
}

void ADC_init_WD(void)
{
	ADC1->CR2 &= ~ADC_CR2_ADON;
	
	RCC->CFGR &= ~RCC_CFGR_ADCPRE;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){}
	
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	ADC1->CR2 &= ~ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_EXTSEL;
	ADC1->CR2 &= ~ADC_CR2_CONT;
		
	ADC1->CR2 &= ~ADC_CR2_DMA;
	ADC1->CR1 &= ~ADC_CR1_SCAN;
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP1;
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_3);
	
	/****************ADC Interrupt Initialization****************/
	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	ADC1->CR1 |= ADC_CR1_AWDEN;			// Enable WatchDog
	ADC1->CR1 &= ~ADC_CR1_AWDCH;		// Analog watchdog channel select 
	ADC1->CR1 |= ADC_CR1_AWDCH_0;		// Select ADC analog Channel1	
	ADC1->CR1 |= ADC_CR1_AWDIE;			// Analog watchdog interrupt enable
	//ADC1->HTR = ((uint16_t)0x0000);
	//ADC1->LTR = ((uint16_t)0x0FFF);
	
	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
	/************************************************************/
	
	ADC1->CR2 |= ADC_CR2_ADON;
}

/************************************************************
USART Initialization
*************************************************************/
void USART1_init(void)
{	
	RCC->APB2ENR|= RCC_APB2ENR_USART1EN;// USART For PC

	USART1->CR1 |= USART_CR1_UE;
	USART1->CR1 &= ~USART_CR1_M;
	USART1->CR2 &= ~USART_CR2_STOP;
	//USART1->BRR = 0xB64; 	// for 28MHz 9600 baudrate
	USART1->BRR = 0x2D9; 	// for 28MHz 38400 baudrate
	//USART1->BRR = 0xF3; 	// for 28MHz 115200 baudrate
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TE;
}
