#include <main.h>
#include <spi.h>
#include <gyro.h>



static void GYRO_Write(uint8_t addr, uint8_t data) {
	buffer_tx[0] = addr;
	buffer_tx[1] = data;
	SPI5_GYRO_CE_GPIO_Port->ODR &= ~SPI5_GYRO_CE_Pin;
	HAL_SPI_Transmit(&hspi5, buffer_tx, 2, 10);
	SPI5_GYRO_CE_GPIO_Port->ODR |= SPI5_GYRO_CE_Pin;
	HAL_Delay(10);	
}
	

static void GYRO_Read(uint8_t addr) {
	buffer_tx[0] = addr | 0x80;
	SPI5_GYRO_CE_GPIO_Port->ODR &= ~SPI5_GYRO_CE_Pin;
	HAL_SPI_TransmitReceive(&hspi5, buffer_tx, buffer_rx, 2, 10);
	SPI5_GYRO_CE_GPIO_Port->ODR |= SPI5_GYRO_CE_Pin;
	HAL_Delay(10);	
	
}
static HAL_StatusTypeDef GYRO_Collect(void) {
		
	GYRO_Read(0x27);
	//check bit 3 in status register to see if new data is available.
if((buffer_rx[1] & (1 << 3)) == 8) {
		
		//save previous rate and time data
		x_Rate_Last = x_Rate;
		y_Rate_Last = y_Rate;
		z_Rate_Last = z_Rate;
		time1 = time2;
			
		//Read X
		
		GYRO_Read(0x28);
			
		x_Rate = buffer_rx[1];
		
		GYRO_Read(0x29);
			
		x_Rate |= (buffer_rx[1] << 8);
		x_Rate = (~x_Rate) + 1;
			
		//Read Y
		
		GYRO_Read(0x2A);
			
		y_Rate = buffer_rx[1];
		
		GYRO_Read(0x2b);
			
		y_Rate |= (buffer_rx[1] << 8);
		y_Rate = (~y_Rate) + 1;
		
		//Read Z	
		GYRO_Read(0x2C);
		
		z_Rate = buffer_rx[1];
		
		GYRO_Read(0x2D);
			
		z_Rate |= (buffer_rx[1] << 8);	
		z_Rate = (~z_Rate) + 1;	
			
		time2 = HAL_GetTick();		
		return HAL_OK;
	}
	return HAL_BUSY;
}

static void GYRO_Calculate(void) {
	int16_t x_Inc;
	int16_t y_Inc;
	int16_t z_Inc;
	
	x_Inc = (x_Rate + x_Rate_Last) / (time2 - time1);
	y_Inc = (y_Rate + y_Rate_Last) / (time2 - time1);
	z_Inc = (z_Rate + z_Rate_Last) / (time2 - time1);
	
	if (x_Inc > 6 || x_Inc < -6) {
		x_Final += x_Inc;
	}
	if (y_Inc > 6 || y_Inc < -6) {
		y_Final += y_Inc;
	}
	if (z_Inc > 6 || z_Inc < -6) {
		z_Final += z_Inc;
	}
	
	if (x_Final <= -999 || x_Final >= 999) {
		x_Final = 0;
	}
	if (y_Final <= -999 || y_Final >= 999) {
		y_Final = 0;
	}
	if (z_Final <= -999 || z_Final >= 999) {
		z_Final = 0;
	}
	
	
}

static void GYRO_Init(void) {
	//configure main control register, enabling x y and z axis.
	GYRO_Write(0x20, 0xff);
	
	//TODO: Possibly change high pass filter settings IN CTRL REG 2
	
	GYRO_Write(0x21, 0x04);
	//CTRL 3 Already = 0, all interrupt features disabled by default.
	
	//CTRL 4, DPI. The Endianness is already fine as is (LSB at lower address)
	
	GYRO_Write(0x23, 0x30);
	
}

