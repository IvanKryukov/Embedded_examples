#include "rcc_ini.h"

void RCC_INIT(void)
{
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR &= ~RCC_CFGR_HPRE;		// Reset AHB1 Prescaler
	RCC->CFGR |= RCC_CFGR_HPRE_3;		// Set AHB1 Prescaler (div 2)
	
	RCC->CFGR &= ~RCC_CFGR_SW;			// Clear SW bits in CFGR register
	//RCC->CFGR |= RCC_CFGR_SW_HSE;		// Set HSE clock as system clock
	RCC->CFGR |= RCC_CFGR_SW_PLL;		// Set PLL clock as system clock
	
	RCC->CFGR &= ~RCC_CFGR_PPRE1;		// Reset APB1 Prescaler
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV16;
	
	RCC->CFGR &= ~RCC_CFGR_PPRE2;		// Reset APB2 Prescaler
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	
	RCC->CR |= RCC_CR_PLLON;
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; 		// Reset PLL Source
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;	// Set the HSE as source of PLL
	/*  */
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;			// PLL multiplication factor
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6;			// PLL multiplication factor
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;			// Reset the PLL M-factor of division
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_1;			// Set the PLL M-factor of division
}

