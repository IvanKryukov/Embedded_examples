#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>

void init_gpio() {
	GPIO_InitTypeDef init;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	init.GPIO_Mode = GPIO_Mode_AF;
	init.GPIO_OType = GPIO_OType_PP;
	init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	init.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&init);

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
}

void tim_init(){
	TIM_TimeBaseInitTypeDef base_timer;
	TIM_OCInitTypeDef oc_init;
	TIM_TimeBaseStructInit(&base_timer);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	base_timer.TIM_Prescaler = 31;//8400 - 1;   // ???????? ???????
	base_timer.TIM_Period = 10000;  // ??????
	base_timer.TIM_CounterMode = TIM_CounterMode_Up; // ???? ?????
	TIM_TimeBaseInit(TIM4, &base_timer);
	
	TIM_OCStructInit(&oc_init);
	oc_init.TIM_OCMode = TIM_OCMode_PWM1;   // ???????? ? ?????? ??? ( PWM )
	oc_init.TIM_OutputState = TIM_OutputState_Enable;
	oc_init.TIM_Pulse = 50;   // ??????? ???
	oc_init.TIM_OCPolarity = TIM_OCPolarity_High;  // ????????????? ??????????

	TIM_OC1Init(TIM4,&oc_init);   /// ??????? ?????? ? ?????? ????? - ???? D12
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	//2
	oc_init.TIM_Pulse = 500; /// ???????? ??????? ???
	TIM_OC2Init(TIM4,&oc_init);  // ??????????? ?????? ????? D13
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	//3 ????? - D14
	oc_init.TIM_Pulse = 50;
	TIM_OC3Init(TIM4,&oc_init);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	//4  - D15
	oc_init.TIM_Pulse = 500;
	TIM_OC4Init(TIM4,&oc_init);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);   // ????????? ????
}

void init_it() {
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0); // ????????? ??????? ?????????? ?? ????? ?

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
	{
		TIM_OCInitTypeDef oc_init;
		TIM_OCStructInit(&oc_init);
		
		oc_init.TIM_OCMode = TIM_OCMode_PWM1;
		oc_init.TIM_OutputState = TIM_OutputState_Enable;
		oc_init.TIM_Pulse = 5000;
		oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC1Init(TIM4,&oc_init);
		TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		//2
		oc_init.TIM_Pulse = 500;
		TIM_OC2Init(TIM4,&oc_init);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

		//3
		oc_init.TIM_Pulse = 5000;
		TIM_OC3Init(TIM4,&oc_init);
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

		//4
		oc_init.TIM_Pulse = 500;
		TIM_OC4Init(TIM4,&oc_init);
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
		EXTI_ClearITPendingBit(EXTI_Line0);    
	}
}

int main()
{
	init_gpio();
	init_it();
	tim_init();
	while(1)
	{
		
	}
}

