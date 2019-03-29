#ifndef MCU_CONFIG_H
#define MCU_CONFIG_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "main.h"

void GPIO_init(void);
void Timer_init(void);
void Counter_init(void);
void Counter2_init(void);
void ADC_init_WD(void);
void ADC_init_noWD(void);
void USART1_init(void);

#endif
