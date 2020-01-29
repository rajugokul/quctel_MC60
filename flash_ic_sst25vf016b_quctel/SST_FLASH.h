/*
 * SST_FLASH.h
 *
 *  Created on: 25-Jan-2020
 *      Author: admin
 */

#ifndef SST_FLASH_H_
#define SST_FLASH_H_
u8 buff[255]={0};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
s8 status_reg = 0;          //status register low 8 bits
s8 status_suspend_reg = 0;  //status register high 8 bits
///////////////////////////////////////////function_dec.////////////////////
void time_delay(u32 cnt);
void flash_rd_id2(void);
void SST_Flash_test();









///////////////////////////////////////////fun._define///////////////
void time_delay(u32 cnt)
{
    u32 i = 0;
    u32 j = 0;
    for(i=0;i<cnt;i++)
        for(j=0;j<1000000;j++);
}

void Write_init(){
	u8  cmd = 0x50;
	u8  cmd1 = 0x01;
	  spi_flash_cs(0);
	  Ql_SPI_Write(USR_SPI_CHANNAL, &cmd, 1);
	  spi_flash_cs(1);
	  spi_flash_cs(0);
	  Ql_SPI_Write(USR_SPI_CHANNAL, &cmd1, 1);
	  spi_flash_cs(1);

}
s8 cmd_is_over(void)
{
    u32 i=0;
    s8 ret = TRUE;
    u32 cnt1 = 100000;
    u32 cnt2 = 0;
    flash_rd_status_reg();

    while(status_reg & 0x01)
    {
        time_delay(1000000);
        flash_rd_status_reg();
    }
    if (status_reg & 0x01)
    {
        ret = FALSE;
    }
    return ret;
}

//@flash write enable
void flash_wr_enable()
{
    s32 ret = 0;
    u8  cmd = 0x06;
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL, &cmd, 1);
	spi_flash_cs(1);
    if(ret==1)
    {
//        APP_DEBUG("write enable.\r\n")
    }
    else
    {
        APP_DEBUG("write enable failed.\r\n")
    }
}

//@read the flash id
//manufacturer ID | memory type | memory density
//      C2        |      20     |     15
void flash_rd_id(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0x9f};
    u8 rd_buff[32]={0xff};

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_WriteRead(USR_SPI_CHANNAL,wr_buff,1,rd_buff,3);
	spi_flash_cs(1);
    if(ret==3)
    {
        APP_DEBUG("0x%x 0x%x 0x%x\r\n", rd_buff[0],rd_buff[1],rd_buff[2]);
    }
    else
    {
        APP_DEBUG("func(%s),line(%d),here has a failed operation.\r\n",__func__,__LINE__)
    }
}

//@REMS  manufacturer ID device ID
void flash_rd_id2(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0x90,0xFF,0xFF,0x00};
    u8 rd_buff[32]={0xff};

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_WriteRead(USR_SPI_CHANNAL,wr_buff,4,rd_buff,2);
	spi_flash_cs(1);
    if(ret==2)
    {
        APP_DEBUG("[Debug Log]0x%x 0x%x\r\n", rd_buff[0],rd_buff[1]);
    }
    else
    {
        APP_DEBUG("[Debug Log]read flash id 2 failed, ret=%d", ret);
    }
}

//read status register low 8 bits
void flash_rd_status_reg(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0x05};

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_WriteRead(USR_SPI_CHANNAL,wr_buff,1,&status_reg,1);
	spi_flash_cs(1);
    if(ret==1)
    {
        APP_DEBUG("[Debug Log]status_reg: 0x%x.\r\n", status_reg);
    }
    else
    {
        APP_DEBUG("[Debug Log]read status register low 8 bits failed, ret=%d.\r\n",ret);
    }
}

//@read status register high 8 bits
void flash_rd_suspend_status_reg(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0x35};

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_WriteRead(USR_SPI_CHANNAL,wr_buff,1,&status_suspend_reg,1);
	spi_flash_cs(1);
    if(ret==1)
    {
        APP_DEBUG("[Debug Log]status_suspend_reg: 0x%x.\r\n", status_suspend_reg);
    }
    else
    {
        APP_DEBUG("[Debug Log]read status register high 8 bits failed, ret=%d.\r\n", ret);
    }
}

//@20160803 lock flash lower 1/2, for Winbond W25Q64DW
void ql_winbond_flash_block_lock(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0};

    wr_buff[0] = 0x01;
    wr_buff[1] = (status_reg & (~0x7C)) | 0x18;
    wr_buff[2] = status_suspend_reg | 0x40;

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,wr_buff,3);
	spi_flash_cs(1);

    if(ret == 3)
    {
        APP_DEBUG("[Debug Log]flash lock ok.\r\n");
    }
    else
    {
        APP_DEBUG("[Debug Log]flash lock ok failed, ret=%d.\r\n", ret);
    }
}

//@20160803 unlock flash lower 1/2, for Winbond W25Q64DW
void ql_winbond_flash_block_unlock(void)
{
    s32 ret = 0;
    u8 wr_buff[32]={0};

    wr_buff[0] = 0x01;

    if(status_suspend_reg & 0x40)
        wr_buff[1] = status_reg | 0x7C;
    else
        wr_buff[1] = status_reg & (~0x7C);

	flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,wr_buff,2);
	spi_flash_cs(1);
    if(ret==2)
    {
        APP_DEBUG("[Debug Log]flash unlock ok.\r\n");
    }
    else
    {
        APP_DEBUG("[Debug Log]flash unlock ok failed, ret=%d.\r\n", ret);
    }
}

//@flash chip erase()
void flash_erase_chip()
{
    s32 ret = 0;
    u8 cmd = 0x60;
    u32 j=1000000,i=0;
    flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,&cmd,1);
	spi_flash_cs(1);
    //Because erase the whole chip must need more time to wait,
    time_delay(10000000);
    if(ret==1)
    {
        //Because erase the whole chip must need more time to wait ,so we must check the bit 1 of status register .
        APP_DEBUG("chip erase done.\r\n");
    }
    else
    {
        APP_DEBUG("func(%s),line(%d),here has a failed operation.\r\n",__func__,__LINE__)
    }
}

//@flash block erase(0-31)
void flash_erase_block(s8 nblock)
{
    u8 cmd = 0x52;
    s32 ret = 0;
    u32 addr = nblock * 0x10000;
    u8 wr_buff[4]={cmd,(addr>>16)&0xff,(addr>>8)&0xff,addr & 0xff};
    if (nblock > 31)
    {
        APP_DEBUG("nblock is error para.\r\n")
        return ;
    }
    flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,wr_buff,4);
	spi_flash_cs(1);
    if(ret==4)
    {
        APP_DEBUG("chip erase ok.\r\n")
    }
    else
    {
        APP_DEBUG("func(%s),line(%d),here has a failed operation.\r\n",__func__,__LINE__)
    }
}

//@flash sector erase(0-511)
void flash_erase_sector(s16 nsector)
{
    u8 cmd = 0x20;
    s32 ret = 0;
    u32 addr = nsector * 0x1000;
    u8 wr_buff[4]={cmd,(addr>>16)&0xff,(addr>>8)&0xff,addr & 0xff};

    if (nsector > 511)
    {
        APP_DEBUG("nsector is error para.\r\n")
        return ;
    }
    flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,wr_buff,4);
	spi_flash_cs(1);
    if(ret==4)
    {
        APP_DEBUG("sector erase ok.\r\n")
    }
    else
    {
        APP_DEBUG("func(%s),line(%d),here has a failed operation.\r\n",__func__,__LINE__)
    }
}
u8 data=20;
//@flash write data (page program)
void flash_wr_data(u32 addr, u8 *pbuff,u32 len)
{
    u8 *p_buff = pbuff;
    s32 ret = 0;
    s16 i=0;
    u8 cmd = 0x02;
    u8 wr_buff[2048]={cmd,(addr>>16)&0xff, (addr>>8)&0xff, addr&0xff,data};
    data++;
    if (len > 1024)
    {
        APP_DEBUG("length is too long.\r\n")
        return ;
    }
//    for(i=0; i<255; i++)
//    {
//       wr_buff[6] = 20 ;
//       p_buff++;
//    }
    Write_init();
    flash_wr_enable();
	spi_flash_cs(0);
    ret = Ql_SPI_Write(USR_SPI_CHANNAL,wr_buff,6);
	spi_flash_cs(1);
}

//@flash read data
void flash_rd_data(u32 addr, u8 *pbuff, u32 len)
{
    s32 ret = 0;
    u8 cmd = 0x03;
    u8 wr_buff[4]={cmd,(addr>>16)&0xff,(addr>>8)&0xff,addr & 0xff};

    if (len > 1024)
    {
        APP_DEBUG("length is too long.\r\n")
        return ;
    }
	spi_flash_cs(0);
    ret = Ql_SPI_WriteRead(USR_SPI_CHANNAL,wr_buff,4, pbuff,len);
	spi_flash_cs(1);
    if(ret==len)
    {
        u16 i=0;
        APP_DEBUG("Read data= ")
        for(i=0;i<len;i++)
        {
            APP_DEBUG("%d ",pbuff[i])
        }
        APP_DEBUG("\r\n")
    }
    else
    {
        APP_DEBUG("func(%s),line(%d),here has a failed operation.\r\n",__func__,__LINE__)
    }
}



////////////////////////////////////////////sst_flsh_test_function/////////////////////////////////
void SST_Flash_test(){
	    SPI_INIT();
		flash_rd_id();
		ql_winbond_flash_block_lock();
		ql_winbond_flash_block_unlock();
		flash_rd_id2();
		flash_rd_data(0,buff,255);
		flash_erase_sector(0);
		flash_erase_block(0);
		flash_erase_chip();
		flash_rd_data(0,buff,255);
		ql_winbond_flash_block_unlock();
		APP_DEBUG("\r\n Write_data: ok\r\n");
		delay(50);
				for(int j=0;j<=255;j++){
				flash_wr_data(j,buff,255);
				}
		flash_rd_data(0,buff,255);
}




#endif /* SST_FLASH_H_ */
