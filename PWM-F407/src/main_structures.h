#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>


void delay_ms(uint32_t ms)
{
	volatile uint32_t nCount; 				//Variable for counting
	RCC_ClocksTypeDef RCC_Clocks; 		//Variable for reading frequency
	RCC_GetClocksFreq (&RCC_Clocks); 	//Read CPU frequency
	 
	nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms; 	//milliseconds to cycles
	while (nCount--) {};													//empty cycles
}

int main (void)
{
	int x = 1023;
	
	GPIO_InitTypeDef PORT_SETUP;
	GPIO_InitTypeDef SinglePin;
	TIM_TimeBaseInitTypeDef TIM_SETUP; 	//Setup Timer Structure
	TIM_OCInitTypeDef PWM_SETUP;  			//Setup PWM Structure
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 
		
 	PORT_SETUP.GPIO_Mode = 	GPIO_Mode_AF;
	PORT_SETUP.GPIO_OType = GPIO_OType_PP; 
	PORT_SETUP.GPIO_Pin = 	GPIO_Pin_12; 
	PORT_SETUP.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &PORT_SETUP);
	
	SinglePin.GPIO_Mode = 	GPIO_Mode_OUT;
	SinglePin.GPIO_OType = GPIO_OType_PP; 
	SinglePin.GPIO_Pin = 	GPIO_Pin_13; 
	SinglePin.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &SinglePin);
 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
 	
	TIM_SETUP.TIM_CounterMode = TIM_CounterMode_Up;  	//Count Up  
	TIM_SETUP.TIM_Period = 			1023;     						//Timer period = 1023
	TIM_SETUP.TIM_Prescaler = 	16;    								//Disable prescaler
 	TIM_TimeBaseInit(TIM4, &TIM_SETUP);
 
	PWM_SETUP.TIM_Pulse = 			254; 										//Begin filling
	PWM_SETUP.TIM_OCMode = 			TIM_OCMode_PWM1; 				//Center align Mode1
	PWM_SETUP.TIM_OutputState = TIM_OutputState_Enable; //Set as output
	PWM_SETUP.TIM_OCPolarity = 	TIM_OCPolarity_High; 		//High Polarity
	TIM_OC1Init(TIM4, &PWM_SETUP);
	TIM_Cmd(TIM4, ENABLE);
	
	while(1)
	{
		while(x > 0) //LED low
		{
			TIM4->CCR1=x;
			x--;
			delay_ms(1);
		}
		
		while(x < 1023) //LED high
		{
			TIM4->CCR1=x;
			x++;
			delay_ms(1);
		}
	}
}


