#ifndef MAIN_INI
#define MAIN_INI

#include "stm32f4xx.h"
#include "dma_ini.h"
#include "gpio_ini.h"
#include "rcc_ini.h"
#include "spi_ini.h"
#include "tim_ini.h"
#include "usart_ini.h"
#include <stdio.h>

void delay_1KCycles(uint32_t del);
void PWM_LED_Indication(void);
void set_channel(uint8_t num, uint16_t comp);
int main(void);

#endif

