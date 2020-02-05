/*
 *#include "DISP_SPI_INIT.h"
 *
 *  Created on: 05-Nov-2019
 *      Author: vijaygokl.R
 */

#ifndef DISP_SPI_INIT_H_
#define DISP_SPI_INIT_H_
#define USR_SPI_CHANNAL 1
#include "MC60_GPIO.h"
#include "MY_ILI9341.h"
//////////////////////////////////////////////////////lcd////////////////////////
//////https://www.waveshare.com/wiki/4inch_TFT_Touch_Shield//////////////////////////

typedef enum {
TM_ILI9341_Landscape,
TM_ILI9341_Portrait
} TM_ILI9341_Orientation;

/*
* @brief  LCD options
* @note   Used private
*/
typedef struct {
u16 width;
u16 height;
TM_ILI9341_Orientation orientation; // 1 = portrait; 0 = landscape
} TM_ILI931_Options_t;

/* Pin functions */
u16 ILI9341_x;
u16 ILI9341_y;
TM_ILI931_Options_t ILI9341_Opts;
u8 ILI9341_INT_CalledFromPuts = 0;


	static u8 rotationNum=1;
	static bool _cp437    = FALSE;
//	static SPI_HandleTypeDef lcdSPIhandle;
//	//Chip Select pin
//	static GPIO_TypeDef  *tftCS_GPIO;
//	static u16 tftCS_PIN;
//	//Data Command pin
//	static GPIO_TypeDef  *tftDC_GPIO;
//	static u16 tftDC_PIN;
//	//Reset pin
//	static GPIO_TypeDef  *tftRESET_GPIO;
//	static u16 tftRESET_PIN;

	static //Text simple font array (You can your own font)
	const unsigned char font1[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x22, 0x54, 0x54, 0x78, 0x42,
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0x7D, 0x12, 0x11, 0x12, 0x7D,
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x3A, 0x44, 0x44, 0x44, 0x3A,
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x3D, 0x42, 0x42, 0x42, 0x3D,
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0x55, 0x00, 0x55, 0x00, 0x55,
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	0xFF, 0x55, 0xFF, 0x55, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0xFC, 0x4A, 0x4A, 0x4A, 0x34,
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00
	};


////////////////////////////////////////////////////////
void init_Spi();
void disp_gpio_init();
/////////////////////////////quctel development board///////////////////////////////
//s32 LCD_CS = D2;
//s32 LCD_DC = D3;
//s32 LCD_RST = D4;

////bts bord/////////////////////////////////////////////////////////////
s32 LCD_CS = D6;
s32 LCD_DC = D2;
s32 LCD_RST = D3;

void init_Spi(){
	s32 ret;
	s32 spi_usr_type=1;
//	    APP_DEBUG("\r\n<-- OpenCPU: SPI TEST! -->\r\n");

	               		  //chnnlNo, 	      //pinClk,   	 //pinMiso,      //pinMosi,     //pinCs,       	    //spiType
	    ret = Ql_SPI_Init(USR_SPI_CHANNAL,PINNAME_PCM_IN,PINNAME_PCM_SYNC,PINNAME_PCM_OUT,PINNAME_PCM_CLK,spi_usr_type);

	    if(ret <0)
	    {
//	        APP_DEBUG("\r\n<-- Failed!! Ql_SPI_Init fail , ret =%d-->\r\n",ret);
	    }
	    else
	    {
//	        APP_DEBUG("\r\n<-- Ql_SPI_Init ret =%d -->\r\n",ret);
	    }
	    ret = Ql_SPI_Config(USR_SPI_CHANNAL,1,0,0,10000); //config sclk about 10MHz;
	    if(ret <0)
	    {
//	        APP_DEBUG("\r\n<--Failed!! Ql_SPI_Config fail  ret=%d -->\r\n",ret);
	    }
	    else
	    {
//	        APP_DEBUG("\r\n<-- Ql_SPI_Config  =%d -->\r\n",ret);
	    }

		//init cs pin
		if (!spi_usr_type)
		{
//			APP_DEBUG("\r\n<--ok-->\r\n");
			Ql_GPIO_Init(PINNAME_RI,PINDIRECTION_OUT,PINLEVEL_HIGH,PINPULLSEL_PULLUP);   //CS high
		}

}

void disp_gpio_init(){
	        pinMode(LCD_CS,OUTPUT,LOW,PINPULLSEL_DISABLE);  //PINNAME_CLK//CS
			pinMode(LCD_DC,OUTPUT,LOW,PINPULLSEL_DISABLE); //PINNAME_RI//DC
			pinMode(LCD_RST,OUTPUT,LOW,PINPULLSEL_DISABLE); //PINNAME_DCD//RST

			digitalWrite(LCD_DC,HIGH);
			digitalWrite(LCD_RST,HIGH);

//			APP_DEBUG("\r\n<-- LCD_CS==%d -->\r\n",LCD_CS);
//			APP_DEBUG("\r\n<-- LCD_DC==%d -->\r\n",LCD_DC);
//			APP_DEBUG("\r\n<-- LCD_RST==%d -->\r\n",LCD_RST);
//			digitalWrite(D3,HIGH);

}

/////////////////////////////////////////////////////////////////////////
void LcdInitSettings()
	{
		/* Set default settings */
	ILI9341_x = ILI9341_y = 0;
	ILI9341_Opts.width = ILI9341_WIDTH;
	ILI9341_Opts.height = ILI9341_HEIGHT;
	ILI9341_Opts.orientation = TM_ILI9341_Landscape;//
	}

	//1. Write Command to LCD
	void ILI9341_SendCommand(u8 com)
	{
//		APP_DEBUG("\r\n send command---%d\r\n",com);
//		delay(6000);
	//*(__IO u8 *)(0x60000000) = com;
	u8 tmpCmd = com;
	//Set DC HIGH for COMMAND mode
	//HAL_GPIO_WritePin(tftDC_GPIO, tftDC_PIN, GPIO_PIN_RESET);
	digitalWrite(LCD_DC,LOW);
	//Put CS LOW
	//HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_RESET);
	digitalWrite(LCD_CS,LOW);
	//Write byte using SPI
//	HAL_SPI_Transmit(&lcdSPIhandle, &tmpCmd, 1, 5);
	Ql_SPI_Write(USR_SPI_CHANNAL,&tmpCmd, 1,5);
	//Bring CS HIGH
	//HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
	digitalWrite(LCD_CS,HIGH);
	}

	//2. Write data to LCD
	void ILI9341_SendData(u8 data)
	{
		//APP_DEBUG("\r\n send_data---%d\r\n",data);
	//*(__IO u8 *)(0x60040000) = data;
	u8 tmpCmd = data;
	//Set DC LOW for DATA mode
	//HAL_GPIO_WritePin(tftDC_GPIO, tftDC_PIN, GPIO_PIN_SET);
	digitalWrite(LCD_DC,HIGH);
	//Put CS LOW
//	HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_RESET);
	digitalWrite(LCD_CS,LOW);
	//Write byte using SPI
//	HAL_SPI_Transmit(&lcdSPIhandle, &tmpCmd, 1, 5);
	Ql_SPI_Write(USR_SPI_CHANNAL, &tmpCmd, 1,5);
	//Bring CS HIGH
//	HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
	digitalWrite(LCD_CS,HIGH);
	}
	//2.2 Write multiple/DMA
	void ILI9341_SendData_Multi(u16 Colordata, u32 size)
	{
	u8 colorL,colorH;

	//Set DC LOW for DATA mode
//	HAL_GPIO_WritePin(tftDC_GPIO, tftDC_PIN, GPIO_PIN_SET);
	digitalWrite(LCD_DC,HIGH);
	//Put CS LOW
//	HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_RESET);
	digitalWrite(LCD_CS,LOW);
	//Write byte using SPI
//	HAL_SPI_Transmit(&lcdSPIhandle, (u8 *)&Colordata, size, 1000);
	Ql_SPI_Write(USR_SPI_CHANNAL, (u8 *)&Colordata, size, 1000);
	//Wait for end of DMA transfer
	//Bring CS HIGH
//	HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
	digitalWrite(LCD_CS,HIGH);
	}

	//3. Set cursor position
	void ILI9341_SetCursorPosition(u16 x1, u16 y1, u16 x2, u16 y2) {

	ILI9341_SendCommand (ILI9341_COLUMN_ADDR);
	ILI9341_SendData(x1>>8);
	ILI9341_SendData(x1 & 0xFF);
	ILI9341_SendData(x2>>8);
	ILI9341_SendData(x2 & 0xFF);

	ILI9341_SendCommand (ILI9341_PAGE_ADDR);
	ILI9341_SendData(y1>>8);
	ILI9341_SendData(y1 & 0xFF);
	ILI9341_SendData(y2>>8);
	ILI9341_SendData(y2 & 0xFF);
	ILI9341_SendCommand (ILI9341_GRAM);
	}


	//4. Initialise function
	void ILI9341_Init()
	{
	 //Copy SPI settings
//	 memcpy(&lcdSPIhandle, spiLcdHandle, sizeof(*spiLcdHandle));
//	 //CS pin
//	 tftCS_GPIO = csPORT;
//	 tftCS_PIN = csPIN;
//	 //DC pin
//	 tftDC_GPIO = dcPORT;
//	 tftDC_PIN = dcPIN;
//	 HAL_GPIO_WritePin(tftCS_GPIO, tftCS_PIN, GPIO_PIN_SET);
	 digitalWrite(LCD_CS,HIGH);
	 //RESET pin
//	 tftRESET_GPIO = resetPORT;
//	 tftRESET_PIN = resetPIN;
//	 HAL_GPIO_WritePin(resetPORT, resetPIN, GPIO_PIN_SET);  //Turn LCD ON
	 digitalWrite(LCD_RST,HIGH);

	 ILI9341_SendCommand (ILI9341_RESET); // software reset comand
	 delay(100);
	 ILI9341_SendCommand (ILI9341_DISPLAY_OFF); // display off
	 //--------------VCOM-------------------------------------
	 ILI9341_SendCommand (ILI9341_VCOM1); // vcom control
	 ILI9341_SendData   (0x35); // Set the VCOMH voltage (0x35 = 4.025v)
	 ILI9341_SendData   (0x3e); // Set the VCOML voltage (0x3E = -0.950v)
	 ILI9341_SendCommand (ILI9341_VCOM2); // vcom control
	 ILI9341_SendData   (0xbe);
	 //------------memory access control------------------------
	 ILI9341_SendCommand (ILI9341_MAC); // memory access control
	 ILI9341_SendData(0x48);
	 ILI9341_SendCommand (ILI9341_PIXEL_FORMAT);  // pixel format set
	 ILI9341_SendData   (0x55);                   // 16bit /pixel
	 ILI9341_SendCommand(ILI9341_FRC);
	 ILI9341_SendData(0);
	 ILI9341_SendData(0x1F);
	 ILI9341_SendCommand (ILI9341_SLEEP_OUT);     // sleep out
	 delay(100);
	 ILI9341_SendCommand (ILI9341_DISPLAY_ON);   // display on
	 delay(100);
	 ILI9341_SendCommand (ILI9341_GRAM);         // memory write
	 delay(5);
	 LcdInitSettings();
	}

	//5. Write data to a single pixel
	void ILI9341_DrawPixel(u16 x, u16 y, u16 color) {
	ILI9341_SetCursorPosition(x, y,x,y);
	ILI9341_SendCommand(ILI9341_GRAM);
	ILI9341_SendData(color>>8);
	ILI9341_SendData(color&0xFF);
	}

	//6. Fill the entire screen with a background color
	void ILI9341_Fill(u16 color) {
	u32 n = ILI9341_PIXEL_COUNT;
	u16 myColor = 0xFF;

	if(rotationNum==1 || rotationNum==3)
	{
		ILI9341_SetCursorPosition(0, 0,   ILI9341_WIDTH -1, ILI9341_HEIGHT -1);
	}
	else if(rotationNum==2 || rotationNum==4)
	{
		ILI9341_SetCursorPosition(0, 0, ILI9341_HEIGHT -1, ILI9341_WIDTH -1);
	}


	while (n) {
			n--;
			 ILI9341_SendData(color>>8);
				ILI9341_SendData(color&0xff);
	}
	}
	//7. Rectangle drawing functions
	void ILI9341_Fill_Rect(unsigned int x0,unsigned int y0, unsigned int x1,unsigned int y1, u16 color) {
	u32 n = ((x1+1)-x0)*((y1+1)-y0);
	if (n>ILI9341_PIXEL_COUNT) n=ILI9341_PIXEL_COUNT;
	ILI9341_SetCursorPosition(x0, y0, x1, y1);
	while (n) {
			n--;
			ILI9341_SendData(color>>8);
				ILI9341_SendData(color&0xff);
	}
	}

	//8. Circle drawing functions
	void ILI9341_drawCircle(s16 x0, s16 y0, s16 r, u16 color)
	{
	s16 f = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x = 0;
	s16 y = r;

	ILI9341_DrawPixel(x0  , y0+r, color);
	ILI9341_DrawPixel(x0  , y0-r, color);
	ILI9341_DrawPixel(x0+r, y0  , color);
	ILI9341_DrawPixel(x0-r, y0  , color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		ILI9341_DrawPixel(x0 + x, y0 + y, color);
		ILI9341_DrawPixel(x0 - x, y0 + y, color);
		ILI9341_DrawPixel(x0 + x, y0 - y, color);
		ILI9341_DrawPixel(x0 - x, y0 - y, color);
		ILI9341_DrawPixel(x0 + y, y0 + x, color);
		ILI9341_DrawPixel(x0 - y, y0 + x, color);
		ILI9341_DrawPixel(x0 + y, y0 - x, color);
		ILI9341_DrawPixel(x0 - y, y0 - x, color);
	}
	}
	static void drawCircleHelper( s16 x0, s16 y0, s16 r, u8 cornername, u16 color)
	{
	s16 f     = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x     = 0;
	s16 y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4) {
			ILI9341_DrawPixel(x0 + x, y0 + y, color);
			ILI9341_DrawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2) {
			ILI9341_DrawPixel(x0 + x, y0 - y, color);
			ILI9341_DrawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			ILI9341_DrawPixel(x0 - y, y0 + x, color);
			ILI9341_DrawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			ILI9341_DrawPixel(x0 - y, y0 - x, color);
			ILI9341_DrawPixel(x0 - x, y0 - y, color);
		}
	}
	}
	static void fillCircleHelper(s16 x0, s16 y0, s16 r, u8 cornername, s16 delta, u16 color)
	{
	s16 f     = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x     = 0;
	s16 y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			ILI9341_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			ILI9341_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			ILI9341_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			ILI9341_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
	}
	void ILI9341_fillCircle(s16 x0, s16 y0, s16 r, u16 color)
	{
	ILI9341_drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
	}

	//9. Line drawing functions
	void ILI9341_drawLine(s16 x0, s16 y0, s16 x1, s16 y1, u16 color)
	{
	s16 steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	s16 dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	s16 err = dx / 2;
	s16 ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			ILI9341_DrawPixel(y0, x0, color);
		} else {
			ILI9341_DrawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
	}

	void ILI9341_drawFastHLine(s16 x, s16 y, s16 w, u16 color)
	{
	ILI9341_drawLine(x, y, x+w-1, y, color);
	}

	void ILI9341_drawFastVLine(s16 x, s16 y, s16 h, u16 color)
	{
	ILI9341_drawLine(x, y, x, y+h-1, color);
	}
	//10. Triangle drawing
	void ILI9341_drawTriangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color)
	{
	ILI9341_drawLine(x0, y0, x1, y1, color);
	ILI9341_drawLine(x1, y1, x2, y2, color);
	ILI9341_drawLine(x2, y2, x0, y0, color);
	}
	void ILI9341_fillTriangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color)
	{
	s16 a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}

	if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		ILI9341_drawFastHLine(a, y0, b-a+1, color);
		return;
	}

	s16
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1,
		sa   = 0,
		sb   = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it

	for(y=y0; y<=last; y++) {
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;

		if(a > b) swap(a,b);
		ILI9341_drawFastHLine(a, y, b-a+1, color);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;

		if(a > b) swap(a,b);
		ILI9341_drawFastHLine(a, y, b-a+1, color);
	}
	}

	//11. Text printing functions
	void ILI9341_drawChar(s16 x, s16 y, unsigned char c, u16 color, u16 bg, u8 size)
	{
	if(rotationNum == 1 || rotationNum ==3)
	{
		if((x >= ILI9341_WIDTH)            || // Clip right
		 (y >= ILI9341_HEIGHT)           || // Clip bottom
		 ((x + 6 * size - 1) < 0) || // Clip left
		 ((y + 8 * size - 1) < 0))   // Clip top
		return;
	}
	else
	{
		if((y >= ILI9341_WIDTH)            || // Clip right
		 (x >= ILI9341_HEIGHT)           || // Clip bottom
		 ((y + 6 * size - 1) < 0) || // Clip left
		 ((x + 8 * size - 1) < 0))   // Clip top
		return;
	}


	if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

	for (s8 i=0; i<6; i++ ) {
		u8 line;
		if (i == 5)
			line = 0x0;
		else
			line = pgm_read_byte(font1+(c*5)+i); //
		for (s8 j = 0; j<8; j++) {
			if (line & 0x1) {
				if (size == 1) // default size
					ILI9341_DrawPixel(x+i, y+j, color);
				else {  // big size
					ILI9341_Fill_Rect(x+(i*size), y+(j*size), size + x+(i*size), size+1 + y+(j*size), color);
				}
			} else if (bg != color) {
				if (size == 1) // default size
					ILI9341_DrawPixel(x+i, y+j, bg);
				else {  // big size
					ILI9341_Fill_Rect(x+i*size, y+j*size, size + x+i*size, size+1 + y+j*size, bg);
				}
			}
			line >>= 1;
		}
	}
	}
	void ILI9341_printText(char text[], s16 x, s16 y, u16 color, u16 bg, u8 size)
	{
	s16 offset;
	offset = size*6;
	for(u16 i=0; i<40 && text[i]!=NULL; i++)
	{
		ILI9341_drawChar(x+(offset*i), y, text[i],color,bg,size);
	}
	}

	//12. Image print (RGB 565, 2 bytes per pixel)
	void ILI9341_printImage(u16 x, u16 y, u16 w, u16 h, u8 *data, u32 size)
	{
	u32 n = size;
	ILI9341_SetCursorPosition(x, y, w+x-1, h+y-1);
	for(u32 i=0; i<n ; i++)
	{
		ILI9341_SendData(data[i]);
	}
	}

	//13. Set screen rotation
	void ILI9341_setRotation(u8 rotate)
	{
	switch(rotate)
	{
		case 1:
			rotationNum = 1;
			ILI9341_SendCommand(ILI9341_MEMCONTROL);
			ILI9341_SendData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
			break;
		case 2:
			rotationNum = 2;
			ILI9341_SendCommand(ILI9341_MEMCONTROL);
			ILI9341_SendData(ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
			break;
		case 3:
			rotationNum = 3;
			ILI9341_SendCommand(ILI9341_MEMCONTROL);
			ILI9341_SendData(ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR);
			break;
		case 4:
			rotationNum = 4;
			ILI9341_SendCommand(ILI9341_MEMCONTROL);
			ILI9341_SendData(ILI9341_MADCTL_MX | ILI9341_MADCTL_MY | ILI9341_MADCTL_MV | ILI9341_MADCTL_BGR);
			break;
		default:
			rotationNum = 1;
			ILI9341_SendCommand(ILI9341_MEMCONTROL);
			ILI9341_SendData(ILI9341_MADCTL_MY | ILI9341_MADCTL_BGR);
			break;
	}
	}
	//14. Get screen rotation
	u8 ILI9341_getRotation(void)
	{
	return rotationNum;
	}
	//15. reset lcd  screen
	void ILI9341_Resetsytem()
	{
	 ILI9341_SendCommand (ILI9341_RESET); // software reset comand
	 delay(100);
	 ILI9341_SendCommand (ILI9341_DISPLAY_OFF); // display off
	 ILI9341_SendCommand (ILI9341_SLEEP_OUT); // sleep out
	 delay(100);
	 ILI9341_SendCommand (ILI9341_DISPLAY_ON); // display on
	 delay(100);
	 ILI9341_SendCommand (ILI9341_GRAM); // memory write
	 delay(5);
	}
	//16. clear lcd position
	void ILI9341_clrpos(u16 x, u16 y,u16 x1, u16 y1, u16 color)
	{
	u16 i,j;
	u32 width,height;
	u16 myColor = 0xFF;

	//	if(rotationNum==1 || rotationNum==3)
	//	{
	//		ILI9341_SetCursorPosition(x, y,   ILI9341_WIDTH -1, ILI9341_HEIGHT -1);
	//	}
	//	else if(rotationNum==2 || rotationNum==4)
	//	{
	//		ILI9341_SetCursorPosition(x, y, ILI9341_HEIGHT -1, ILI9341_WIDTH -1);
	//	}


	for(i=x;i<x1;i++)
	{
		for(j=y;j<y1;j++)
		{
			ILI9341_DrawPixel(i,j,color);
		}
	}

	}

//17. print string
	void ILI9341_Puts(u16 x, u16 y, char *str, TM_FontDef_t *font, u32 foreground, u32 background) {
		u16 startX = x;

	/* Set X and Y coordinates */
	ILI9341_x = x;
	ILI9341_y = y;

	while (*str) {
		/* New line */
		if (*str == '\n') {
			ILI9341_y += font->FontWidth + 1;
			/* if after \n is also \r, than go to the left of the screen */
			if (*(str + 1) == '\r') {
				ILI9341_x = 0;
				str++;
			} else {
				ILI9341_x = startX;
			}
			str++;
			continue;
		} else if (*str == '\r') {
			str++;
			continue;
		}

		/* Put character to LCD */
		ILI9341_Putc(ILI9341_x, ILI9341_y, *str++, font, foreground, background);
	}
	}

  //18. Getstring
	void ILI9341_GetStringSize(char *str, TM_FontDef_t *font, u16 *width, u16 *height) {
	u16 w = 0;
	*height = font->FontHeight;
	while (*str++) {
		w += font->FontWidth;
	}
	*width = w;
	}

	//19. print char
	void ILI9341_Putc(u16 x, u16 y, char c, TM_FontDef_t *font, u32 foreground, u32 background) {
	u32 i, b, j;
	/* Set coordinates */
	ILI9341_x = x;
	ILI9341_y = y;

	if ((ILI9341_y + font->FontHeight) > ILI9341_Opts.height) {
		/* If at the end of a line of display, go to new line and set x to 0 position */
		ILI9341_x += font->FontWidth;
		ILI9341_y = 0;
	}

	/* Draw font data */
	for (i = 0; i < font->FontHeight; i++) {
		b = font->data[(c - 32) * font->FontHeight + i];
		for (j = 0; j < font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
			ILI9341_DrawPixel(ILI9341_x + j, (ILI9341_y + i), foreground);
			}
		}
	}

	/* Set new pointer */
	ILI9341_x += font->FontWidth;
	}

//------------------------------Draw Corss----------------------------------------------------------------------------------------------------
//20. Draw Cross
void ILI9341_DrawCross(u16 Xpos, u16 Ypos, u16 in_color, u16 out_color)
{
	ILI9341_drawLine(Xpos-15,Ypos,Xpos-2,Ypos,in_color);
	ILI9341_drawLine(Xpos+2,Ypos,Xpos+15,Ypos,in_color);
	ILI9341_drawLine(Xpos,Ypos-15,Xpos,Ypos-2,in_color);
	ILI9341_drawLine(Xpos,Ypos+2,Xpos,Ypos+15,in_color);


	ILI9341_drawLine(Xpos-15,Ypos+15,Xpos-7,Ypos+15,out_color);
	ILI9341_drawLine(Xpos-15,Ypos+7,Xpos-15,Ypos+15,out_color);


	ILI9341_drawLine(Xpos-15,Ypos-15,Xpos-7,Ypos-15,out_color);
	ILI9341_drawLine(Xpos-15,Ypos-7,Xpos-15,Ypos-15,out_color);


  ILI9341_drawLine(Xpos+7,Ypos+15,Xpos+15,Ypos+15,out_color);
	ILI9341_drawLine(Xpos+15,Ypos+7,Xpos+15,Ypos+15,out_color);

  ILI9341_drawLine(Xpos+7,Ypos-15,Xpos+15,Ypos-15,out_color);
  ILI9341_drawLine(Xpos+15,Ypos-15,Xpos+15,Ypos-7,out_color);
}

//////////////////////////////////////////////////////lcd close///////////////////////

#endif /* DISP_INIT_H_ */
