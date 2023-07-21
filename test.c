#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "oled.h"
#include "key.h"
//ALIENTEK精英STM32F103开发板 实验12
//OLED显示 实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
int main(void)
{	
 	u8 Key_value=0;	    	
 	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);	   	 	//延时初始化
	uart_init(72,115200);	//串口初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
	OLED_Init();			//初始化OLED
	Key_Config();
	OLED_ShowString(0,0,"A403",24);
	OLED_ShowString(0,24,"KEY test",16);
	OLED_ShowString(0,40,"buttun:",12);
	OLED_Refresh_Gram();//更新显示到OLED
	while(1) 
	{
		Key_value=KeyScan();
		if(Key_value!=20)
		{
			Key_Character(Key_value);
  	  delay_ms(500);
	    LED0=!LED0;
		}
	}	
}


