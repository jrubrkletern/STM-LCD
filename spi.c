
#include <main.h>
#include <spi.h>


static void SPI5_Init(void) {
	
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi5.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi5) != HAL_OK)
	{
		Error_Handler();
	}
	
}

static void SPI5_GPIO_Init(void) {
	__HAL_RCC_SPI5_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_SPIInit;
	GPIO_SPIInit.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_SPIInit.Mode = GPIO_MODE_AF_PP;
	GPIO_SPIInit.Alternate = GPIO_AF5_SPI5;
	GPIO_SPIInit.Pull = GPIO_NOPULL;
	GPIO_SPIInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOF, &GPIO_SPIInit);
	
	/*Configure LCD/GYRO CE and DSX Pins Output Level */
	HAL_GPIO_WritePin(SPI5_GYRO_CE_GPIO_Port, SPI5_GYRO_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI5_LCD_CE_GPIO_Port, SPI5_LCD_CE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI5_LCD_DSX_GPIO_Port, SPI5_LCD_DSX_Pin, GPIO_PIN_SET);
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/*Configure GPIO pin : SPI5_GYRO_CE_Pin / SPI5_LCD_CE_Pin */
	GPIO_InitStruct.Pin = SPI5_GYRO_CE_Pin | SPI5_LCD_CE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(SPI5_GYRO_CE_GPIO_Port, &GPIO_InitStruct);   //both pins are on port c
	
	/*Configure GPIO Pin : SPI5_LCD_DSX_Pin */
	
	GPIO_InitStruct.Pin = SPI5_LCD_DSX_Pin | SPI5_LCD_RSX_Pin;
	HAL_GPIO_Init(SPI5_LCD_DSX_GPIO_Port, &GPIO_InitStruct);    //both pins are on port d
}

