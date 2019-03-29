#include "tim_ini.h"


uint16_t setwidth = 4000;
void TIMER_INIT(TIM_TypeDef* TIMx)
{
	// Set clock for TIMx
	if (TIMx == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (TIMx == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (TIMx == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (TIMx == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	if (TIMx == TIM5) RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	if (TIMx == TIM6) RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	if (TIMx == TIM7) RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	if (TIMx == TIM8) RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	 
	//At first - initialize base timer (TIMx)
	TIMx->PSC = 0;			// Prescaler
	TIMx->ARR = 4095; 	// Period
	TIMx->CR1 |= TIM_CR1_DIR; // UpCounter Mode
	TIMx->CR1 &= ~TIM_CR1_CKD;
	
	// Clear TIMx_CCMR1 register
	TIMx->CCMR1 &= ~(TIM_CCMR1_OC1M);
			
	/***** Set PWM for 1 Channel *****/
	TIMx->CCMR1 |= (TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1); // PWM Mode 1 Ch1
	TIMx->CCR1 |= setwidth;							// Set Pulse Width Channel 1
	TIMx->CCER |= TIM_CCER_CC1E; 	// Output Enable Channel 1
	TIMx->CCER |= TIM_CCER_CC1P; 	// High Polarity Channel 1
	
	/***** Set PWM for 2 Channel *****/
	TIMx->CCMR1 |= (TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1); // PWM Mode 1 Ch2
	TIMx->CCR2 |= setwidth;							// Set Pulse Width Channel 2
	TIMx->CCER |= TIM_CCER_CC2E; 	// Output Enable Channel 2
	TIMx->CCER |= TIM_CCER_CC2P; 	// High Polarity Channel 2
	
	/***** Set PWM for 3 Channel *****/
	TIMx->CCMR2 |= (TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3M_1); // PWM Mode 1 Ch3
	TIMx->CCR3 |= setwidth;							// Set Pulse Width Channel 3
	TIMx->CCER |= TIM_CCER_CC3E; 	// Output Enable Channel 3
	TIMx->CCER |= TIM_CCER_CC3P; 	// High Polarity Channel 3
	
	/***** Set PWM for 4 Channel *****/
	TIMx->CCMR2 |= (TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4M_1); // PWM Mode 1 Ch3
	TIMx->CCR4 |= setwidth;							// Set Pulse Width Channel 4
	TIMx->CCER |= TIM_CCER_CC4E; 	// Output Enable Channel 4
	TIMx->CCER |= TIM_CCER_CC4P; 	// High Polarity Channel 4
	
	/***** Activate Timer *****/
	TIMx->CR1 |= TIM_CR1_ARPE;	// Set Auto-Reload Preload Register
	TIMx->CR1 |= TIM_CR1_CEN; 	// Set the Timer
}

