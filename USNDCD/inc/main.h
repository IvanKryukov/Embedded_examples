#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define CS_ON            GPIOA->BRR |= GPIO_ODR_4               // stm32f030 CS - 0 (for Master)
#define CS_OFF         GPIOA->BSRR |= GPIO_ODR_4               // stm32f030 CS - 1 (for Master)

#define LED_1            GPIOA->BSRR |= GPIO_ODR_0               // stm32f030 ?????????? LED
#define LED_0            GPIOA->BRR |= GPIO_ODR_0               // stm32f030

#define PC13_0            GPIOC->BSRR |= GPIO_ODR_ODR13            // PC13 OUT LED OFF      (stm32f103) ?????????? LED1
#define PC13_1            GPIOC->BRR |= GPIO_ODR_ODR13            // PC13 OUT LED ON      (stm32f103)
#define PC13_N            GPIOC->ODR ^= GPIO_ODR_ODR13             // PC13 OUT LED INVERT   (stm32f103)

//#define SPI1_DR_8bit      (*(__IO uint8_t *)((uint32_t)&(SPI1->DR)))   // stm32f030
#define SPI_I2S_FLAG_BSY   ((uint16_t)0x0080)                     // stm32f103

void GPIO_INI(void);
void SPI1_INI(void);
void USART1_INI(void);
void INTERRUPT_INI(void);
void SPI_Send(uint32_t data);
void EXTI0_IRQHandler(void);
int main(void);
	
#endif

