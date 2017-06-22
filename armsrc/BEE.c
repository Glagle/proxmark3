
#include "usb_cdc.h"
#include "cmd.h"

#include "proxmark3.h"
#include "apps.h"
#include "util.h"
#include "printf.h"
#include "string.h"

#include <stdarg.h>

#include "legicrf.h"
#include <hitag2.h>
#include <hitagS.h>
#include "lfsampling.h"
#include "BigBuf.h"
#include "mifareutil.h"
#include "pcf7931.h"
#include  "BEE.h"


void Ring_BEE_ONCE(uint16_t music_note)
{
   
    BEE_ON();
	SpinDelayUs(music_note);
	BEE_OFF();
	SpinDelayUs(music_note);

}

void ring_2_7khz(uint16_t count)
{

   Ring_BEE_TIME(n_2_7khz,count);


}


void Ring_BEE_TIME(uint16_t music_note,uint16_t count)
{
	uint16_t i;
   for(i=0;i<count;i++)
   	{
      Ring_BEE_ONCE(music_note);     
   	}
   SpinDelay(9);

}



void Ring_ALL(uint16_t count)
{

   Ring_BEE_TIME(note_1,count);
   Ring_BEE_TIME(note_2,count);
   Ring_BEE_TIME(note_3,count);
   Ring_BEE_TIME(note_4,count);
   Ring_BEE_TIME(note_5,count);
   Ring_BEE_TIME(note_6,count);
   Ring_BEE_TIME(note_7,count);
   //Ring_BEE_TIME(note_8,count);
   SpinDelay(10);

}



void Ring_Little_Star(uint16_t count)
{   
   Ring_BEE_TIME(note_1,count);  

   Ring_BEE_TIME(note_1,count);  

   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_5,count);
  
   Ring_BEE_TIME(note_6,count);
    
   Ring_BEE_TIME(note_6,count);
  
   Ring_BEE_TIME(note_5,2*count);
   

   LED_A_ON(); 
/**
   Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_4,count);
   
   Ring_BEE_TIME(note_3,count);
  
   Ring_BEE_TIME(note_3,count);
   
   Ring_BEE_TIME(note_2,count);
  
   Ring_BEE_TIME(note_2,count);
   
   Ring_BEE_TIME(note_1,2*count);
 

   LED_A_OFF(); 
  ***/

  /**
   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_5,count);
   
   Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_3,count);
   
   Ring_BEE_TIME(note_3,count);

   Ring_BEE_TIME(note_2,2*count);


   LED_A_ON(); 

   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_3,count);

   Ring_BEE_TIME(note_3,count);

   Ring_BEE_TIME(note_2,2*count);
      LED_A_OFF(); 



   Ring_BEE_TIME(note_1,count);

    Ring_BEE_TIME(note_1,count);

   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_5,count);

   Ring_BEE_TIME(note_6,count);

  Ring_BEE_TIME(note_6,count);

   Ring_BEE_TIME(note_5,2*count);
    LED_A_ON(); 

   Ring_BEE_TIME(note_4,count);

  Ring_BEE_TIME(note_4,count);

   Ring_BEE_TIME(note_3,count);

  Ring_BEE_TIME(note_3,count);

   Ring_BEE_TIME(note_2,count);

  Ring_BEE_TIME(note_2,count);

   Ring_BEE_TIME(note_1,2*count);

  LED_B_ON();
  ****/
}















