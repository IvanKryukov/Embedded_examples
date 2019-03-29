#include "adc_ini.h"

/**********************
 * ADC INITIALIZATION *
 **********************/
 
 void ADC_INIT(void)
{
	ADC1->CR2 &= ~ADC_CR2_ADON;		// DISABLE ADC (ADC OFF)
	
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	ADC1->CR2 &= ~ADC_CR2_ALIGN;	// Right Alignment
	ADC1->CR2 &= ~ADC_CR2_EXTEN;	// External triiger disable
	ADC1->CR2 &= ~ADC_CR2_CONT;		// Single conversion mode (not continious)
		
	ADC1->CR2 |= ADC_CR2_DMA;			// DMA mode enabled
	ADC1->CR1 &= ~ADC_CR1_SCAN;		// Scan mode disabled
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP1;
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR3 = 0;
	//ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_3);
	//ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_2); // 5 channel
	ADC1->SQR3 |= (ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1|ADC_SQR3_SQ1_2); // 7 channel
		
	ADC1->CR1 |= ADC_CR1_EOCIE;

	NVIC_EnableIRQ(ADC_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	ADC1->CR2 |= ADC_CR2_ADON;
}
 
