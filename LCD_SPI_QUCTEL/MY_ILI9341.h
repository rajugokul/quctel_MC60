/*
Library:					SPI LCD - ILI9341
Written by:				Mohamed Yaqoob (MYaqoobEmbedded YouTube Channel)
Date Written:			09/12/2018
Last modified:		-/-
Description:			This is an STM32 device driver library for the ILI9341 SPI LCD display, using STM HAL libraries
										
* Copyright (C) 2018 - M. Yaqoob
   This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
   of the GNU General Public Licenseversion 3 as published by the Free Software Foundation.
	
   This software library is shared with puplic for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
   or indirectly by this software, read more about this on the GNU General Public License.
*/

//List of includes
//#include <stdbool.h>
//** CHANGE BASED ON STM32 CHIP F4/F7/F1...**//
//#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "ql_type.h"
//--------------------------TM_EXAMPLE------------------------------------------------------------------------------------------------------------
#include "tm_stm32f4_fonts.h"
//------------------------------END---------------------------------------------------------------------------------------------------------------

//LCD dimensions defines
#define ILI9341_WIDTH       320  //X AXIS
#define ILI9341_HEIGHT      480  //Y AXIS
#define ILI9341_PIXEL_COUNT	 ILI9341_WIDTH * ILI9341_HEIGHT
//ILI9341 LCD commands
#define ILI9341_RESET			 		    	0x01
#define ILI9341_SLEEP_OUT		  			0x11
#define ILI9341_GAMMA			    			0x26
#define ILI9341_DISPLAY_OFF					0x28
#define ILI9341_DISPLAY_ON					0x29
#define ILI9341_COLUMN_ADDR					0x2A
#define ILI9341_PAGE_ADDR			  		0x2B
#define ILI9341_GRAM				    		0x2C
#define ILI9341_TEARING_OFF					0x34
#define ILI9341_TEARING_ON					0x35
#define ILI9341_DISPLAY_INVERSION		0xb4
#define ILI9341_MAC			        		0x36
#define ILI9341_PIXEL_FORMAT    		0x3A
#define ILI9341_WDB			    	  		0x51
#define ILI9341_WCD				      		0x53
#define ILI9341_RGB_INTERFACE   		0xB0
#define ILI9341_FRC					    	  0xB1
#define ILI9341_BPC					    	  0xB5
#define ILI9341_DFC				 	    	  0xB6
#define ILI9341_Entry_Mode_Set		  0xB7
#define ILI9341_POWER1						  0xC0
#define ILI9341_POWER2						  0xC1
#define ILI9341_VCOM1							  0xC5
#define ILI9341_VCOM2							  0xC7
#define ILI9341_POWERA						  0xCB
#define ILI9341_POWERB						  0xCF
#define ILI9341_PGAMMA						  0xE0
#define ILI9341_NGAMMA						  0xE1
#define ILI9341_DTCA							  0xE8
#define ILI9341_DTCB							  0xEA
#define ILI9341_POWER_SEQ					  0xED
#define ILI9341_3GAMMA_EN					  0xF2
#define ILI9341_INTERFACE					  0xF6
#define ILI9341_PRC				   	  	  0xF7
#define ILI9341_VERTICAL_SCROLL 	  0x33

#define ILI9341_MEMCONTROL 0x36
#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

//List of colors
#define COLOR_BLACK           0x0000  
#define COLOR_NAVY            0x000F      
#define COLOR_DGREEN          0x03E0     
#define COLOR_DCYAN           0x03EF  
#define COLOR_MAROON          0x7800 
#define COLOR_PURPLE          0x780F //GOOD
#define COLOR_OLIVE           0x7BE0     
#define COLOR_LGRAY           0xC618      
#define COLOR_DGRAY           0x7BEF    
#define COLOR_BLUE            0x001F //GOOD   
#define COLOR_BLUE2			      0x051D
#define COLOR_GREEN           0x07E0 //GOOD     
#define COLOR_GREEN2		      0xB723
#define COLOR_GREEN3		      0x8000
#define COLOR_CYAN            0x07FF   
#define COLOR_RED             0xF800    
#define COLOR_MAGENTA         0xF81F    
#define COLOR_YELLOW          0xFFE0   
#define COLOR_WHITE           0xFFFF     
#define COLOR_ORANGE          0xFD20     
#define COLOR_GREENYELLOW     0xAFE5     
#define COLOR_BROWN 			    0XBC40 
#define COLOR_BRRED 			    0XFC07 

//Functions defines Macros
#define RGB565CONVERT(red, green, blue) (int) (((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3))
#define swap(a, b) { s16 t = a; a = b; b = t; }
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define min(a,b) (((a)<(b))?(a):(b))

#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
void draw_pixel_char(int x, int y, u16 color);
int font_is_set(unsigned char c, int x, int y);
u16 set_color(u8 r, u8 g, u8 b);
void lcd_char(char c, int x, int y, u16 color);
void lcd_printf(const char *str, int x, int y, u16 color);

//***** Functions prototypes *****//
//Lcd Settings
void LcdInitSettings();
//1. Write Command to LCD
void ILI9341_SendCommand(u8 com);
//2. Write data to LCD
void ILI9341_SendData(u8 data);
//2.2 Write multiple/DMA
void ILI9341_SendData_Multi(u16 Colordata, u32 size);
//3. Set cursor position
void ILI9341_SetCursorPosition(u16 x1, u16 y1, u16 x2, u16 y2);
//4. Initialise function
void ILI9341_Init();
//5. Write data to a single pixel
void ILI9341_DrawPixel(u16 x, u16 y, u16 color); //Draw single pixel to ILI9341
//6. Fill the entire screen with a background color
void ILI9341_Fill(u16 color); //Fill entire ILI9341 with color
//7. Rectangle drawing functions
void ILI9341_Fill_Rect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, u16 color);
//8. Circle drawing functions
void ILI9341_drawCircle(s16 x0, s16 y0, s16 r, u16 color);
static void drawCircleHelper( s16 x0, s16 y0, s16 r, u8 cornername, u16 color);
static void fillCircleHelper(s16 x0, s16 y0, s16 r, u8 cornername, s16 delta, u16 color);
void ILI9341_fillCircle(s16 x0, s16 y0, s16 r, u16 color);
//9. Line drawing functions
void ILI9341_drawLine(s16 x0, s16 y0, s16 x1, s16 y1, u16 color);
void ILI9341_drawFastHLine(s16 x, s16 y, s16 w, u16 color);
void ILI9341_drawFastVLine(s16 x, s16 y, s16 h, u16 color);
//10. Triangle drawing
void ILI9341_drawTriangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color);
void ILI9341_fillTriangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2, u16 color);
//---------------------------------------------5x7**front--------------------------------------------------------------------------------------------------
//11. Text printing functions
void ILI9341_drawChar(s16 x, s16 y, unsigned char c, u16 color, u16 bg, u8 size);
void ILI9341_printText(char text[], s16 x, s16 y, u16 color, u16 bg, u8 size);
//12. Image print (RGB 565, 2 bytes per pixel)
void ILI9341_printImage(u16 x, u16 y, u16 w, u16 h, u8 *data, u32 size);
//13. Set screen rotation
void ILI9341_setRotation(u8 rotate);
//14. Get screen rotation
u8 ILI9341_getRotation(void);
//15. reset lcd  screen 
void ILI9341_Resetsytem();
//16. clear lcd position 
void ILI9341_clrpos(u16 x, u16 y,u16 x1, u16 y1, u16 color);
//---------------------------------------------7x10,11x18,16x26--fronts--------------------------------------------------------------------------------------------------
//17. print string  
void ILI9341_Puts(u16 x, u16 y, char *str, TM_FontDef_t *font, u32 foreground, u32 background);
//18. Getstring
void ILI9341_GetStringSize(char *str, TM_FontDef_t *font, u16 *width, u16 *height);
//19. print char 
void ILI9341_Putc(u16 x, u16 y, char c, TM_FontDef_t *font, u32 foreground, u32 background);
//20. Draw Cross
void ILI9341_DrawCross(u16 Xpos, u16 Ypos, u16 in_color, u16 out_color);
