#ifndef _GYRO_H
#define _GYRO_H

#include <main.h>

static HAL_StatusTypeDef GYRO_Collect(void);
static void GYRO_Calculate(void);
static void GYRO_Write(uint8_t, uint8_t);
static void GYRO_Read(uint8_t);
static void GYRO_Init(void);


static uint16_t time1;
static uint16_t time2;
static int16_t x_Rate;
static int16_t x_Rate_Last;
static int16_t x_Final;
static int16_t x_Final_Last;
static int16_t y_Rate;
static int16_t y_Rate_Last;
static int16_t y_Final;
static int16_t y_Final_Last;
static int16_t z_Rate;
static int16_t z_Rate_Last;
static int16_t z_Final;
static int16_t z_Final_Last;


static uint8_t buffer_tx[2];
static uint8_t buffer_rx[2];

#endif