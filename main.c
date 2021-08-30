
#include <main.h>
#include <lcd.c>
#include <spi.c>
#include <gyro.c>







int main(void)
{
	HAL_Init();
	SystemClock_Config();
	GPIO_CLK_Init();
	SPI5_Init();
	LCD_Init();
	HAL_Delay(5);
	GYRO_Init();
	HAL_Delay(10);
	LCD_Setup_Screen();
	time1 = HAL_GetTick();
		while (1) {
			if (GYRO_Collect() == HAL_OK) {
				GYRO_Calculate();
				gyroSamples++;
				if (gyroSamples > 5) {
					
					LCD_Clear_Result((x_Final == x_Final_Last), (y_Final == y_Final_Last), (z_Final == z_Final_Last));
				
					LCD_Get_Chars(x_Final, y_Final, z_Final);
					
					LCD_Print_Coords((x_Final == x_Final_Last), (y_Final == y_Final_Last), (z_Final == z_Final_Last));
					
					gyroSamples = 0;
					x_Final_Last = x_Final;		
					y_Final_Last = y_Final;	
					z_Final_Last = z_Final;
							
				}	
			}
	}
	
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	*/
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	                            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}



static void GPIO_CLK_Init(void)
{

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
	SPI5_GPIO_Init();
}

void SysTick_Handler(void) {
	HAL_IncTick();
}

void Error_Handler(void) {
	__disable_irq();
	while (1)
	{
		__ASM("bkpt 255");
	}
}

