#include "proxmark3.h"
#include "apps.h"
#include "flash.h"
#include "fonts.h"
#include "usb_cdc.h"

#define address_length 3
extern void Dbprintf(const char *fmt, ...);

uint8_t  GET_MISO(void)
{
   
   if(MISO_VALUE)
   	return true;
   else 
   	return false;

}


uint8_t EXFLASH_spi_write_read(uint8_t wData)    //  IO模拟
{
	
	
		uint8_t i, tmp = 0;
		
		SCK_low;
	   
		nCS_low;
	   
		for(i = 0;i < 8;i++)
		{
		   SCK_low;
		   SpinDelayUs(2);
	   
			if(wData&0x80)
			{
				MOSI_high;
			   
			}
			else
			{
				MOSI_low;
				SpinDelayUs(2);
			}
			wData <<= 1;
			SCK_high;
		  
			
			tmp <<= 1;
			tmp |= GET_MISO();
		   
	
		}
		SCK_low;
	
		return tmp;
}

  



uint8_t EXFLASH_readStat1(void) 
{
	uint8_t stat1=3 ;

  EXFLASH_spi_write_read(READSTAT1);

  stat1	= EXFLASH_spi_write_read(0xff);
  nCS_high;
 return stat1;
}


uint8_t EXFLASH_readStat2(void) 
{
	uint8_t stat2 ;

  EXFLASH_spi_write_read(READSTAT2);

  stat2	= EXFLASH_spi_write_read(0xff);
  nCS_high;
 return stat2;
}


bool ESFLASH_NOTBUSY(void)
{
    uint8_t state,count=0;
	do {
    state = EXFLASH_readStat1();
		if(count>100)
			{
             
			return false;
		}
		count++;
	} while(state & BUSY);
	return true;

}

void EXFLASH_Write_Enable(void) 
{
    
    EXFLASH_spi_write_read(WRITEENABLE);
	  nCS_high;

}



uint8_t EXFLASH_Read(uint8_t  address[]) 
{
	uint8_t i,tmp;
	if(!ESFLASH_NOTBUSY())
			return false;

  EXFLASH_spi_write_read(READDATA);
  
    for(i=0;i<address_length;i++)
   	{
    EXFLASH_spi_write_read(address[i]);

   }  
	
   tmp=EXFLASH_spi_write_read(0xff);

	
	nCS_high;
	return tmp;

}

uint8_t EXFLASH_Program(uint8_t  address[],uint8_t array[], uint8_t len) 
{
  uint8_t state1,count=0,i;

   EXFLASH_Write_Enable();
   
   do {
    state1 = EXFLASH_readStat1();
		if(count>100)
			{
             
			return false;
		}
		count++;
	} while((state1 & WRTEN)!=WRTEN);
   
   EXFLASH_spi_write_read(PAGEPROG);
   
   for(i=0;i<address_length;i++)
   	{
    EXFLASH_spi_write_read(address[i]);
   
   }  

   for(i=0;i<len;i++)
   	{
    EXFLASH_spi_write_read(array[i]);
   }  

     nCS_high;
   
  return true;
}


uint8_t EXFLASH_ReadID(void) 
{
    uint8_t ManID;   //,DevID
	if(!ESFLASH_NOTBUSY())
			return true;
	EXFLASH_spi_write_read(MANID);
    EXFLASH_spi_write_read(0x00);
    EXFLASH_spi_write_read(0x00); 
    EXFLASH_spi_write_read(0x00);
	ManID=EXFLASH_spi_write_read(0xff);
//	DevID=EXFLASH_spi_write_read(0xff);
	nCS_high;
	return ManID;
}


bool EXFLASH_Erase(void) 
{
	uint8_t state1,count=0;

   EXFLASH_Write_Enable();
   
   do {
    state1 = EXFLASH_readStat1();
		if(count>100)
			{
             
			return false;
		}
		count++;
	} while((state1 & WRTEN)!=WRTEN);
   
   EXFLASH_spi_write_read(CHIPERASE);
   nCS_high;
   return true;
}

bool EXFLASH_Reset(void)
{
	LED_A_ON();                     //blue
	SetupSpi(SPI_FLASH_MODE);
	
    	if(!ESFLASH_NOTBUSY())
			return false;
	EXFLASH_spi_write_read(Enable_Reset);
	nCS_high;
	EXFLASH_spi_write_read(Reset);
	nCS_high;
	SpinDelayUs(10);
	LED_A_ON();
	return true;
}


void EXFLASH_Init(void)
{

   EXFLASH_Reset();
   
}

#define data_len  3

void EXFLASH_TEST(void)
{
	 uint8_t a[3]={0x00,0x00,0x00};		 //测试用地址
	 uint8_t b[data_len]={0x00,0x01,0x02};	 //测试用数组
     uint8_t f[3]={0x00,0x00,0x01};		 //测试用地址
     uint8_t e[3]={0x00,0x00,0x02};		 //测试用地址
	 uint8_t d=0;
	 //uint8_t c[data_len]={'0','1','2'};
	 //uint8_t head[]="write 012 to 0x00 0x01 0x02\r\n";
	 
	 //uint8_t tail[]="write done!\r\n";
	 
	 EXFLASH_Init();
    // c=EXFLASH_ReadID();
	
    //EXFLASH_Write_Enable();
	//EXFLASH_readStat1();
	//usb_write(head,sizeof(head));
    Dbprintf("%s \r\n","write 012 to 0x00 0x01 0x02");
	 
	//EXFLASH_Erase();
	
   	Dbprintf("%s \r\n"," wait... ");

    EXFLASH_Program(a,b,data_len);
  
    
	d=EXFLASH_Read(a);	  
    Dbprintf(" %d ",d);
   
    d=EXFLASH_Read(f);  
    Dbprintf(" %d ",d);
	
	d=EXFLASH_Read(e);	
	Dbprintf(" %d ",d);

    Dbprintf("\r\n");
    //usb_write(tail,sizeof(tail));
    Dbprintf("%s \r\n","TEST done!");
	EXFLASH_Erase();

 

}
































