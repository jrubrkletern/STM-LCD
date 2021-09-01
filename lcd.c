#include <spi.h>
#include <lcd.h>
#include <font.h>


//todo: change these register accesses from ODR to BSRR for atomic modification, do the same in gyro.c too
void LCD_Send_Cmd(uint8_t data) { //CS Low DS Low
	SPI5_LCD_CE_GPIO_Port->ODR &= ~SPI5_LCD_CE_Pin;
	SPI5_LCD_DSX_GPIO_Port->ODR &= ~SPI5_LCD_DSX_Pin;
	HAL_SPI_Transmit(&hspi5, &data, 1, 1);
	SPI5_LCD_CE_GPIO_Port->ODR |= SPI5_LCD_CE_Pin;
	SPI5_LCD_DSX_GPIO_Port->ODR |= SPI5_LCD_DSX_Pin;
}

void LCD_Send_Data(uint8_t *pBuffer, uint8_t size) { //CS Low DS High
	SPI5_LCD_CE_GPIO_Port->ODR &= ~SPI5_LCD_CE_Pin;
	SPI5_LCD_DSX_GPIO_Port->ODR |= SPI5_LCD_DSX_Pin;
	HAL_SPI_Transmit(&hspi5, pBuffer, size, 1);
	SPI5_LCD_CE_GPIO_Port->ODR |= SPI5_LCD_CE_Pin;
}

void LCD_Set_Window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	LCD_Send_Cmd(0x2A);      //x	
	uint8_t coord_Buffer[4] = { (x1 >> 8) & 0xFF, x1  & 0xFF, (x2 >> 8)  & 0xFF, x2  & 0xFF};
	LCD_Send_Data(coord_Buffer, 4);
	
	LCD_Send_Cmd(0x2B);      //y
	coord_Buffer[0] = (y1 >> 8)  & 0xFF;
	coord_Buffer[1] = y1  & 0xFF;
	coord_Buffer[2] = (y2 >> 8)  & 0xFF;
	coord_Buffer[3] = y2  & 0xFF;
	LCD_Send_Data(coord_Buffer, 4);
	
	LCD_Send_Cmd(0x2C); 
	
}

void LCD_Display_Pixel(uint16_t x, uint16_t y, uint16_t color) {		
	LCD_Set_Window(x, y, (x), (y));
	uint8_t pixel_Buffer[2] = { color >> 8, color};
	LCD_Send_Data(pixel_Buffer, 2);
	
}

void LCD_Display_Char(uint8_t character, uint16_t x, uint16_t y) {	
	LCD_Set_Window(x, y, x + CHAR_WIDTH-1, y + CHAR_HEIGHT-1);
	for (uint8_t i = 0; i < CHAR_HEIGHT; i++) {
		for (uint8_t j = 0; j < CHAR_WIDTH; j++) {
			if ((font[character][0 + j]) & (1 << i)) {		
				LCD_Send_Data(pixel_Data, 2);
			} else { 
				LCD_Send_Data(bg_Data, 2);
			}
		}
	}	
}

void LCD_Setup_Screen(void) {
	uint8_t pixel_Data[2] = { 0x0000 >> 8, 0x0000 };
	LCD_Set_Window(0, 0, 360, 240);
	for (int i = 0; i < 360; i++) {
		for (int j = 0; j < 240 ; j++) {	
			LCD_Send_Data(pixel_Data, 2);	
		}		
	}
	HAL_Delay(10);
	//initial x
	LCD_Display_Char(10, 40, 200);
	LCD_Display_Char(0, 40, 165);
	LCD_Display_Char(0, 40, 150);
	LCD_Display_Char(0, 40, 135);
	
	//initial y
	LCD_Display_Char(11, 120, 200);
	LCD_Display_Char(0, 120, 165);
	LCD_Display_Char(0, 120, 150);
	LCD_Display_Char(0, 120, 135);
	
	//initial z
	LCD_Display_Char(12, 200, 200);
	LCD_Display_Char(0, 200, 165);
	LCD_Display_Char(0, 200, 150);
	LCD_Display_Char(0, 200, 135);
}

void LCD_Clear_Char(uint8_t character, uint16_t x, uint16_t y) {	
	LCD_Set_Window(x, y, x + CHAR_WIDTH - 1, y + CHAR_HEIGHT - 1);
	for (uint8_t i = 0; i < CHAR_HEIGHT; i++) {
		for (uint8_t j = 0; j < CHAR_WIDTH; j++) {
				LCD_Send_Data(bg_Data, 2);		
		}
	}
}
void LCD_Clear_Result(uint8_t x_Same, uint8_t y_Same, uint8_t z_Same) {
	if (!x_Same) {
		if (num[0] != num_Last[0]) {
			LCD_Clear_Char(num[0], 40, 165);
		}
		if (num[1] != num_Last[1]) {
			LCD_Clear_Char(num[1], 40, 150);
		}
		if (num[2] != num_Last[2]) {
			LCD_Clear_Char(num[2], 40, 135);
		}
		
		if (num[9] == '-') 
			LCD_Clear_Char(13, 40, 180);
	}
	if(!y_Same) {
		if (num[3] != num_Last[3]) {
			LCD_Clear_Char(num[3], 120, 165);
		}
		if (num[4] != num_Last[4]) {
			LCD_Clear_Char(num[4], 120, 150);
		}
		if (num[5] != num_Last[5]) {
			LCD_Clear_Char(num[5], 120, 135);
		}
		if (num[10] == '-') 
			LCD_Clear_Char(13, 120, 180);
	}
	if(!z_Same) {
		if (num[6] != num_Last[6]) {
			LCD_Clear_Char(num[6], 200, 165);
		}
		if (num[7] != num_Last[7]) {
			LCD_Clear_Char(num[7], 200, 150);
		}
		if (num[8] != num_Last[8]) {
			LCD_Clear_Char(num[8], 200, 135);
		}
		if (num[11] == '-') 
			LCD_Clear_Char(13, 200, 180);
	}	
}

void LCD_Print_Coords(uint8_t x_Same, uint8_t y_Same, uint8_t z_Same) {
	if (!x_Same) {
		if (num[0] != num_Last[0]) {
			LCD_Display_Char(num[0], 40, 165);
		}
		if (num[1] != num_Last[1]) {
			LCD_Display_Char(num[1], 40, 150);
		}
		if (num[2] != num_Last[2]) {
			LCD_Display_Char(num[2], 40, 135);
		}
		
		if (num[9] == '-') 
			LCD_Display_Char(13, 40, 180);
	}
	if (!y_Same) {
		if (num[3] != num_Last[3]) {
			LCD_Display_Char(num[3], 120, 165);
		}
		if (num[4] != num_Last[4]) {
			LCD_Display_Char(num[4], 120, 150);
		}
		if (num[5] != num_Last[5]) {
			LCD_Display_Char(num[5], 120, 135);
		}
		if (num[10] == '-') 
			LCD_Display_Char(13, 120, 180);
	}
	if (!z_Same) {
		if (num[6] != num_Last[6]) {
			LCD_Display_Char(num[6], 200, 165);
		}
		if (num[7] != num_Last[7]) {
			LCD_Display_Char(num[7], 200, 150);
		}
		if (num[8] != num_Last[8]) {
			LCD_Display_Char(num[8], 200, 135);
		}
		if (num[11] == '-') 
			LCD_Display_Char(13, 200, 180);
	}	

	for (int i = 8; i >= 0; i--) {
		num_Last[i] = num[i];
	}
		
}
	
void LCD_Init(void)
{	
	SPI5_LCD_RSX_GPIO_Port->ODR |= SPI5_LCD_RSX_Pin;
	SPI5_LCD_RSX_GPIO_Port->ODR &= ~SPI5_LCD_RSX_Pin;
	HAL_Delay(25);
	SPI5_LCD_CE_GPIO_Port->ODR &= ~SPI5_LCD_CE_Pin;
	HAL_Delay(25);
	SPI5_LCD_RSX_GPIO_Port->ODR |= SPI5_LCD_RSX_Pin;
	
	uint8_t *data;
	uint8_t test;
	data = &test;
	
	*data = 0x20 | 0x08;
	LCD_Send_Cmd(0x36);
	LCD_Send_Data(data, 1);    //addressing order, and rgb vs bgr order (right to left, bgr order)
	
	*data = 0x23;
	LCD_Send_Cmd(0xC0);
	LCD_Send_Data(data, 1);
	
	*data = 0x55;
	LCD_Send_Cmd(0x3A);
	LCD_Send_Data(data, 1);    //changes from default of 18 bits to 16 bits
	
	
	LCD_Send_Cmd(0x11);
	HAL_Delay(150);

	LCD_Send_Cmd(0x29);

}





void LCD_Get_Chars(int16_t x_Final, int16_t y_Final, int16_t z_Final) {
	gyroResult = x_Final;
	if (gyroResult < 0) {
		gyroResult = -gyroResult;
		LCD_Display_Char(13, 40, 180);
		num[9] = '-';
	}
	else {
		num[9] = 0; 
	}
	num[0] = gyroResult / 100;
	num[1] = (gyroResult % 100) / 10;
	num[2] = gyroResult % 10;
				
	gyroResult = y_Final;
	if (gyroResult < 0) {
		gyroResult = -gyroResult;
						
		LCD_Display_Char(13, 120, 180);
		num[10] = '-';
	}
	else {
		num[10] = 0; 
	}
	num[3] = gyroResult / 100;
	num[4] = (gyroResult % 100) / 10;
	num[5] = gyroResult % 10;
		
				
	gyroResult = z_Final;
	if (gyroResult < 0) {
		gyroResult = -gyroResult;
		LCD_Display_Char(13, 200, 180);
		num[11] = '-';
	}
	else {
		num[11] = 0; 
	}
	num[6] = gyroResult / 100;
	num[7] = (gyroResult % 100) / 10;
	num[8] = gyroResult % 10;
}


