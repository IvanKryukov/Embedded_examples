#include "main.h"

#define 	SEND_SIGNAL 0
#define 	SEND_CHARGE	1
#define 	MODE_ON(mode) 		(mode = TRUE)
#define 	MODE_OFF(mode) 		(mode = FALSE)
#define 	MODE_IS_ON(mode)	((mode & TRUE) != 0)
#define 	MODE_IS_OFF(mode)	((mode & TRUE) == 0)

uint16_t 	data_adc = 0;
uint32_t 	k = 0;
uint16_t 	amplitude_adc = 0;
uint16_t 	sys_time;
uint8_t 	charge_lvl = 200;
uint16_t 	crc16pack;
/** Self-calibration variables **/
bool 			SELFCALIBRATION_MODE;
uint16_t 	k_clbr = 0;
uint16_t 	min_lvl = 0xFFF, max_lvl = 0x0;
uint16_t 	mid_calib = 0;
uint16_t 	delta_cal = 0;
/********************************/
uint8_t 	BT_COMM_TEST[] = "AT";
uint8_t 	BT_COMM_NAME[] = "AT+NAMELapa";
uint8_t 	BT_COMM_BAUD[] = "AT+BAUD6"; // 38400 baudrate

void delay(uint32_t count)	// Delay cycles
{
	while(count--);
}

void delay_us(uint32_t count) // Delay microseconds
{
	/*********************************************************************************
	!!! SET THE REGISTER TIM3->ARR TO 0xFFFF FOR CORRECT WORK OF THIS PROCEDURE !!!
	*********************************************************************************/
	TIM3->CNT = 0x0;
	TIM3->CR1 |= TIM_CR1_CEN;			// Timer3	enable
	while (TIM3->CNT < count);
	TIM3->CR1 &= ~TIM_CR1_CEN;		// Timer3	disable
}

void delay_ms(uint32_t count) 	// Delay milliseconds
{
	/************************************************************************************
	!!! SET THE REGISTER TIM3->ARR TO 0x3EB (1000) FOR CORRECT WORK OF THIS PROCEDURE !!!
	************************************************************************************/
	uint32_t counter = 0;
	TIM4->CNT = 0x0;
	TIM4->CR1 |= TIM_CR1_CEN;			// Timer3	enable
	while (counter < count)
	{
		while (TIM4->CNT < count)
		{
			if ((TIM4->SR & TIM_SR_UIF) == TRUE)
			{
				TIM_ClearITPendingBit(TIM4,TIM_SR_UIF);
				counter++;
			}
		}
	}
	TIM4->CR1 &= ~TIM_CR1_CEN;		// Timer3	disable
}

/**********************************************************************
****** USART1 Functions
***********************************************************************/
/* Transmit USART1 Data and waiting for the end of transfer */
void USART1_Send(uint8_t SendData)
{
	GPIOA->BSRR |= GPIO_BSRR_BR9;
	USART_SendData(USART1, SendData);
	while((USART1->SR & USART_SR_TC) == 0 ) {} // Waiting for completed transfer
	GPIOA->BSRR |= GPIO_BSRR_BS9;
}

/* Separate data and send it */
void USART_Send_SeparatedData(uint16_t SendData) 
{
	uint8_t part_data = 255;	// Variable for saving data
	
	part_data &= SendData;		// Save first 8 bit of data
	USART1_Send(part_data);		// Transmit first 8 bit of data

	part_data = 255;					// Variable for saving data
	SendData >>= 8;						// Shift data by 8 bits
	part_data &= SendData;		// Save last 4 bit of data
	USART1_Send(part_data);		// Transmit last 4 bit of data
}

/* Compress data to 8 bits and send it */
void USART_Send_CompressedData(uint16_t SendData)
{
	uint8_t compr_data;						// Variable for saving data
	
	compr_data = SendData >> 4;		// Save 8 high bits
	USART1_Send(compr_data);			// Send data
}

void USART1_SendAll(uint8_t send_status)
{
	switch (send_status)
	{
		case SEND_SIGNAL:
			USART1_Send('A');													// Transmit first byte
			USART_Send_SeparatedData(crc16pack);			// Transmit CRC16
			USART_Send_SeparatedData(amplitude_adc);	// Transmit amplitude data
			USART_Send_SeparatedData(sys_time);				// Transmit time data
		break;
	
		case SEND_CHARGE:
			USART1_Send('B');													// Transmit first byte
			USART_Send_SeparatedData(crc16pack);			// Transmit CRC16
			USART1_Send(charge_lvl);									// Transmit charge data
		break;
	}
}

/**********************************************************************
****** BT Functions
***********************************************************************/
void USART_BT_Send(uint8_t *ArrData, uint8_t CountData)
{
	while(CountData--) USART1_Send(*ArrData++);		
}

/* Transmit initialization messages to BT */
void BT_init(void)
{
	USART_BT_Send(BT_COMM_TEST,2);	// Transmit test message
	delay(1000);
	USART_BT_Send(BT_COMM_NAME,1);	// Transmit new name to BT
	delay(1000);
	USART_BT_Send(BT_COMM_BAUD,8);	// Transmit baudrate message
	delay(1000);
}

/**********************************************************************
****** ADC WatchDog Interrupt (or End of Conversion)
***********************************************************************/
/* Interrupt */
void ADC1_2_IRQHandler(void)
{
	uint8_t mult = 4; // multiplier for calculating HTR and LTR
	
	/***** If self-calibration mode is off *****/
	if (MODE_IS_OFF(SELFCALIBRATION_MODE))
	{
		if(ADC_GetITStatus(ADC1, ADC_IT_AWD) == SET)// If flag is set
		{
			ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);	// Clear flag
		}	
		k++;
		TIM2->CR1 |= TIM_CR1_CEN;										// Timer2	enable
		data_adc = ADC1->DR;												// Remember ADC value
		if (data_adc > amplitude_adc) amplitude_adc = data_adc; // Search amplitude
	}
	/***** If self-calibration mode is on *****/
	if (MODE_IS_ON(SELFCALIBRATION_MODE))
	{
		k_clbr++;	
		if(ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET)
		{
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		}
		
		if (k_clbr < 10000)
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
			ADC1->CR2 |= ADC_CR2_EXTSEL;						// Set ADC
			if (ADC1->DR <= min_lvl) min_lvl = ADC1->DR;	// Search the maximum
			if (ADC1->DR >= max_lvl) max_lvl = ADC1->DR;	// Search the minimum
		}
		else
		{			
			mid_calib = max_lvl/2 + min_lvl/2;	// Calculate the middle level of signal
			delta_cal = max_lvl - min_lvl;			// Calculate occuracy
			
			ADC1->HTR = mid_calib + mult*delta_cal;	//	Set the high threshold
			ADC1->LTR = mid_calib - mult*delta_cal;	//	Set the low threshold
			
			MODE_OFF(SELFCALIBRATION_MODE);
		}
	}
}

uint16_t create_crc16(uint8_t create_status)
{
	uint16_t result;
	uint8_t part_data;		// Variable for saving data
	uint8_t arrPack[5];
	
	switch (create_status)
	{
		case SEND_SIGNAL:
			/* Separate amplitude_adc and safe to pack*/
			result = amplitude_adc;
			part_data = 0xFF;
			part_data &= result;	// Safe first amplitude_adc byte
			arrPack[0] = part_data;
			
			result >>= 8;
			part_data = 0xFF;
			part_data &= result;	// Safe high amplitude_adc byte
			arrPack[1] = part_data;
			
			/* Separate sys_time and add to pack*/
			result = sys_time;
			part_data = 0xFF;
			part_data &= result;	// Safe first sys_time byte
			arrPack[2] = part_data;
			
			result >>= 8;
			part_data = 0xFF;
			part_data &= result;	// Safe high sys_time byte
			arrPack[3] = part_data;
			
			result = get_crc16_ccitt_arr(arrPack,5); // Get CRC16 from the pack
		break;
		
		case SEND_CHARGE:
			arrPack[0] = charge_lvl;
			result = get_crc16_ccitt_arr(arrPack,1); // Get CRC16 from the pack
		break;
	}
	return result;
}

int main(void)
{
	/********* Initialization Block *********/
	GPIO_init();
	USART1_init();
	Timer_init();
	Counter_init();
	Counter2_init();
	/******** Self-calibration Block ********/
	MODE_ON(SELFCALIBRATION_MODE);
	ADC_init_noWD();		// Initialization ADC without WatchDog
	while(MODE_IS_ON(SELFCALIBRATION_MODE))
	{
		ADC1->CR2 |= ADC_CR2_EXTSEL;	// Set ADC1
	}
	/****************************************/
	ADC_init_WD();			// Initialization ADC with WatchDog
	BT_init();
	
	while(1)
	{
		//ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		ADC1->CR2 |= ADC_CR2_EXTSEL;								// Set ADC1
		if ((k != 0) && (ADC1->DR < ADC1->HTR))
		{
			TIM2->CR1 &= ~TIM_CR1_CEN;		// Stop Timer2
			sys_time = TIM2->CNT;					// Remember impulse time
			crc16pack = create_crc16(SEND_SIGNAL);		// Create CRC16
			USART1_SendAll(SEND_SIGNAL);	// Send all data we need
			/* Reset variables */
			amplitude_adc = 0;					
			k = 0;
			TIM2->CNT = 0x00000000;			
			
			//delay_ms(4);
			delay_us(4000);
		}
	}
}



