#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "oled.h"
#include "key.h"
//ALIENTEK��ӢSTM32F103������ ʵ��12
//OLED��ʾ ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾  
int main(void)
{	
 	u8 Key_value=0;	    	
 	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);	   	 	//��ʱ��ʼ��
	uart_init(72,115200);	//���ڳ�ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	OLED_Init();			//��ʼ��OLED
	Key_Config();
	OLED_ShowString(0,0,"A403",24);
	OLED_ShowString(0,24,"KEY test",16);
	OLED_ShowString(0,40,"buttun:",12);
	OLED_Refresh_Gram();//������ʾ��OLED
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


