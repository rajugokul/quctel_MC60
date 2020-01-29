/*
 * MC60_SPI.h
 *
 *  Created on: 29-Jan-2020
 *      Author: admin
 */

#ifndef MC60_SPI_H_
#define MC60_SPI_H_

///////////////////////////////////////SPI_defines/////////////////////////////
#define USR_SPI_CHANNAL		     (1)
u8 spi_usr_type = 0 ;

////////////////////////////////////////SPI_function_decleration////////////////////////////
void SPI_INIT();
void spi_flash_cs(bool CS);






/////////////////////////////////////////////////SPI_function//////////////////////////////
void spi_flash_cs(bool CS)
{
	if (!spi_usr_type)
	{
		if (CS)
			Ql_GPIO_SetLevel(PINNAME_PCM_CLK,PINLEVEL_HIGH);
		else
			Ql_GPIO_SetLevel(PINNAME_PCM_CLK,PINLEVEL_LOW);
	}
}

void SPI_INIT(){
	APP_DEBUG("\r\n<-- OpenCPU: SPI TEST! -->\r\n")
      u8 ret;
	               		  //chnnlNo, 	          //pinClk,   	         //pinMiso,      	   //pinMosi,      	   //pinCs,       	    //spiType
	    ret = Ql_SPI_Init(USR_SPI_CHANNAL,PINNAME_PCM_IN,PINNAME_PCM_SYNC,PINNAME_PCM_OUT,PINNAME_PCM_CLK,spi_usr_type);

	    if(ret <0)
	    {
	        APP_DEBUG("\r\n<-- Failed!! Ql_SPI_Init fail , ret =%d-->\r\n",ret);
	    }
	    else
	    {
	        APP_DEBUG("\r\n<-- Ql_SPI_Init ret =%d -->\r\n",ret);
	    }
	    ret = Ql_SPI_Config(USR_SPI_CHANNAL,1,0,0,10000); //config sclk about 10MHz;
	    if(ret <0)
	    {
	        APP_DEBUG("\r\n<--Failed!! Ql_SPI_Config fail  ret=%d -->\r\n",ret);
	    }
	    else
	    {
	        APP_DEBUG("\r\n<-- Ql_SPI_Config  =%d -->\r\n",ret);
	    }

		//init cs pin
		if (!spi_usr_type)
		{
			Ql_GPIO_Init(PINNAME_PCM_CLK,PINDIRECTION_OUT,PINLEVEL_HIGH,PINPULLSEL_PULLUP);   //CS high
		}

}








#endif /* MC60_SPI_H_ */
