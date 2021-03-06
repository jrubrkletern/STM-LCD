#ifndef __LCD_H
#define __LCD_H
#include <main.h>

static void LCD_Send_Cmd(uint8_t);
static void LCD_Send_Data(uint8_t*, uint8_t);
static void LCD_Init(void);
static void LCD_Display_Pixel(uint16_t, uint16_t, uint16_t);
static void LCD_Display_Char(uint8_t, uint16_t, uint16_t);
static void LCD_Clear_Char(uint8_t, uint16_t, uint16_t);
static void LCD_Setup_Screen(void);
static void LCD_Clear_Result(uint8_t, uint8_t, uint8_t);
static void LCD_Set_Window(uint16_t, uint16_t, uint16_t, uint16_t);
static void LCD_Print_Coords(uint8_t, uint8_t, uint8_t);
static void LCD_Get_Chars(int16_t, int16_t, int16_t);

static uint8_t num[12];
static uint8_t num_Last[9] = {255, 255, 255, 255, 255, 255, 255, 255, 255};
static uint8_t pixel_Data[2] = { 0xFF , 0xFF};


static uint8_t bg_Data[2] = { 0x00, 0x00 };
#endif