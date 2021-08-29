
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include <stm32f4xx_hal.h>


void Error_Handler(void);
void SystemClock_Config(void);
static void GPIO_CLK_Init(void);


	static int16_t gyroResult;
	static uint16_t gyroSamples;
	
#define SPI5_GYRO_CE_Pin GPIO_PIN_1
#define SPI5_GYRO_CE_GPIO_Port GPIOC
	
#define SPI5_LCD_CE_Pin GPIO_PIN_2
#define SPI5_LCD_CE_GPIO_Port GPIOC
	
#define SPI5_LCD_DSX_Pin GPIO_PIN_13
#define SPI5_LCD_DSX_GPIO_Port GPIOD
	
#define SPI5_LCD_RSX_Pin GPIO_PIN_12
#define SPI5_LCD_RSX_GPIO_Port GPIOD

#ifdef __cplusplus
}
#endif

#endif


