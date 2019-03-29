#ifndef GPIO_INI
#define GPIO_INI

#include "stm32f4xx.h"
#include "main.h"

/******************** AF1 ********************/
#define GPIO_AF_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping */
#define GPIO_AF_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define GPIO_AF_LPTIM         ((uint8_t)0x01)  /* LPTIM Alternate Function mapping */
#endif /* STM32F410xx || STM32F413_423xx */

/******************** AF2 ********************/
#define GPIO_AF_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping */
#define GPIO_AF_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping */
#define GPIO_AF_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping */

/******************** AF3 ********************/
#define GPIO_AF_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping */
#define GPIO_AF_TIM9          ((uint8_t)0x03)  /* TIM9 Alternate Function mapping */
#define GPIO_AF_TIM10         ((uint8_t)0x03)  /* TIM10 Alternate Function mapping */
#define GPIO_AF_TIM11         ((uint8_t)0x03)  /* TIM11 Alternate Function mapping */
#if defined(STM32F446xx)
#define GPIO_AF3_CEC          ((uint8_t)0x03)  /* CEC Alternate Function mapping */
#endif /* STM32F446xx */
#if defined(STM32F413_423xx)
#define GPIO_AF3_DFSDM2       ((uint8_t)0x03)  /* DFSDM2 Alternate Function mapping */
#endif /* STM32F413_423xx */

/******************** AF4 ********************/
#define GPIO_AF_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping */
#define GPIO_AF_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping */
#define GPIO_AF_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping */
#if defined(STM32F446xx)
#define GPIO_AF4_CEC          ((uint8_t)0x04)  /* CEC Alternate Function mapping */
#endif /* STM32F446xx */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
#define GPIO_AF_FMPI2C        ((uint8_t)0x04)  /* FMPI2C Alternate Function mapping */
#endif /* STM32F410xx || STM32F446xx */

/******************** AF5 ********************/
#define GPIO_AF_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 Alternate Function mapping */
#define GPIO_AF_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 Alternate Function mapping */
#define GPIO_AF5_SPI3         ((uint8_t)0x05)  /* SPI3/I2S3 Alternate Function mapping (Only for STM32F411xE and STM32F413_423xx Devices) */
#define GPIO_AF_SPI4          ((uint8_t)0x05)  /* SPI4/I2S4 Alternate Function mapping */
#define GPIO_AF_SPI5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping      */
#define GPIO_AF_SPI6          ((uint8_t)0x05)  /* SPI6 Alternate Function mapping      */

/******************** AF6 ********************/
#define GPIO_AF_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 Alternate Function mapping */
#define GPIO_AF6_SPI1         ((uint8_t)0x06)  /* SPI1 Alternate Function mapping (Only for STM32F410xx Devices) */
#define GPIO_AF6_SPI2         ((uint8_t)0x06)  /* SPI2 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF6_SPI4         ((uint8_t)0x06)  /* SPI4 Alternate Function mapping (Only for STM32F411xE Devices) */
#define GPIO_AF6_SPI5         ((uint8_t)0x06)  /* SPI5 Alternate Function mapping (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF_SAI1          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping      */
#define GPIO_AF_I2S2ext       ((uint8_t)0x06)  /* I2S2ext_SD Alternate Function mapping (only for STM32F412xG and STM32F413_423xx Devices) */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF6_DFSDM1       ((uint8_t)0x06)  /* DFSDM1 Alternate Function mapping */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define GPIO_AF6_DFSDM2       ((uint8_t)0x06)  /* DFSDM2 Alternate Function mapping */
#endif /* STM32F413_423xx */

/******************** AF7 ********************/
#define GPIO_AF_USART1         ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF_USART2         ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF_USART3         ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /* SPI3/I2S3ext Alternate Function mapping */
#if defined(STM32F413_423xx)
#define GPIO_AF7_DFSDM2        ((uint8_t)0x07)  /* DFSDM2 Alternate Function mapping     */
#define GPIO_AF7_SAI1          ((uint8_t)0x07)  /* SAI1 Alternate Function mapping       */
#endif /* STM32F413_423xx */

#define GPIO_AF_I2S3ext   GPIO_AF7_SPI3

/******************** AF8 ********************/
#define GPIO_AF_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping  */
#define GPIO_AF_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping  */
#define GPIO_AF_USART6        ((uint8_t)0x08)  /* USART6 Alternate Function mapping */
#define GPIO_AF_UART7         ((uint8_t)0x08)  /* UART7 Alternate Function mapping  */
#define GPIO_AF_UART8         ((uint8_t)0x08)  /* UART8 Alternate Function mapping  */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF8_USART3        ((uint8_t)0x08)  /* USART3 Alternate Function mapping */
#define GPIO_AF8_DFSDM1        ((uint8_t)0x08)  /* DFSDM Alternate Function mapping  */
#define GPIO_AF8_CAN1          ((uint8_t)0x08)  /* CAN1 Alternate Function mapping   */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F446xx)
#define GPIO_AF8_SAI2          ((uint8_t)0x08)  /* SAI2 Alternate Function mapping */
#define GPIO_AF_SPDIF         ((uint8_t)0x08)   /* SPDIF Alternate Function mapping */
#endif /* STM32F446xx */

/******************** AF9 ********************/
#define GPIO_AF_CAN1          ((uint8_t)0x09)  /* CAN1 Alternate Function mapping  */
#define GPIO_AF_CAN2          ((uint8_t)0x09)  /* CAN2 Alternate Function mapping  */
#define GPIO_AF_TIM12         ((uint8_t)0x09)  /* TIM12 Alternate Function mapping */
#define GPIO_AF_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping */
#define GPIO_AF_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping */
#define GPIO_AF9_I2C2         ((uint8_t)0x09)  /* I2C2 Alternate Function mapping (Only for STM32F401xx/STM32F410xx/STM32F411xE/STM32F412xG/STM32F413_423xx Devices) */
#define GPIO_AF9_I2C3         ((uint8_t)0x09)  /* I2C3 Alternate Function mapping (Only for STM32F401xx/STM32F411xE/STM32F412xG and STM32F413_423xx Devices) */
#if defined(STM32F446xx)
#define GPIO_AF9_SAI2         ((uint8_t)0x09)  /* SAI2 Alternate Function mapping */
#endif /* STM32F446xx */
#define GPIO_AF9_LTDC         ((uint8_t)0x09)  /* LTDC Alternate Function mapping */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF9_QUADSPI      ((uint8_t)0x09)  /* QuadSPI Alternate Function mapping */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF9_FMPI2C       ((uint8_t)0x09)  /* FMPI2C Alternate Function mapping (Only for STM32F410xx Devices) */
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx */

/******************** AF10 ********************/
#define GPIO_AF_OTG_FS         ((uint8_t)0xA)  /* OTG_FS Alternate Function mapping */
#define GPIO_AF_OTG_HS         ((uint8_t)0xA)  /* OTG_HS Alternate Function mapping */
#if defined(STM32F446xx)
#define GPIO_AF10_SAI2         ((uint8_t)0x0A)  /* SAI2 Alternate Function mapping */
#endif /* STM32F446xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF10_QUADSPI      ((uint8_t)0x0A)  /* QuadSPI Alternate Function mapping */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF10_FMC           ((uint8_t)0xA)  /* FMC Alternate Function mapping    */
#define GPIO_AF10_DFSDM1         ((uint8_t)0xA) /* DFSDM Alternate Function mapping  */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define GPIO_AF10_DFSDM2        ((uint8_t)0x0A)  /* DFSDM2 Alternate Function mapping */
#define GPIO_AF10_SAI1          ((uint8_t)0x0A)  /* SAI1 Alternate Function mapping   */
#endif /* STM32F413_423xx */

/******************** AF11 ********************/
#define GPIO_AF_ETH             ((uint8_t)0x0B)  /* ETHERNET Alternate Function mapping */
#if defined(STM32F413_423xx)
#define GPIO_AF11_UART4         ((uint8_t)0x0B)  /* UART4 Alternate Function mapping  */
#define GPIO_AF11_UART5         ((uint8_t)0x0B)  /* UART5 Alternate Function mapping  */
#define GPIO_AF11_UART9         ((uint8_t)0x0B)  /* UART9 Alternate Function mapping  */
#define GPIO_AF11_UART10        ((uint8_t)0x0B)  /* UART10 Alternate Function mapping */
#define GPIO_AF11_CAN3          ((uint8_t)0x0B)  /* CAN3 Alternate Function mapping   */
#endif /* STM32F413_423xx */

/******************** AF12 ********************/
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF_FSMC             ((uint8_t)0xC)  /* FSMC Alternate Function mapping                     */
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */
#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF_FMC              ((uint8_t)0xC)  /* FMC Alternate Function mapping                      */
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F446xx || STM32F469_479xx */
#define GPIO_AF_OTG_HS_FS        ((uint8_t)0xC)  /* OTG HS configured in FS, Alternate Function mapping */
#define GPIO_AF_SDIO             ((uint8_t)0xC)  /* SDIO Alternate Function mapping                     */

/******************** AF13 ********************/
#define GPIO_AF_DCMI          ((uint8_t)0x0D)  /* DCMI Alternate Function mapping */
#if defined(STM32F469_479xx)
#define GPIO_AF_DSI           ((uint8_t)0x0D)  /* DSI Alternate Function mapping */
#endif /* STM32F469_479xx */

/******************** AF14 ********************/
#define GPIO_AF_LTDC          ((uint8_t)0x0E)  /* LCD-TFT Alternate Function mapping */
#if defined(STM32F413_423xx)
#define GPIO_AF14_RNG         ((uint8_t)0x0E)  /* RNG Alternate Function mapping  */
#endif /* STM32F413_423xx */

/******************** AF15 ********************/
#define GPIO_AF_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

/******************** PIN SOURCES ********************/
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

void Setting_GPIO_AF(GPIO_TypeDef* GPIOx, uint8_t GPIO_PinSource, uint8_t GPIO_AF);
void GPIO_INIT(void);

#endif

