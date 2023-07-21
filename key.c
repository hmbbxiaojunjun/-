#include "oled.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include "usart.h"		
#include "stm32f10x.h"

/**
** PC0-PC3,行，输出。 PE0-PE3,列，输入
**/

void Key_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE,ENABLE);
	/****4行输出****/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/******4列输入********/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

/************************************
按键表盘为:  1  2  3  a
            4  5  6  b
			      7  8  9  c 
			      *  0  #  d 
// ************************************/
int KeyScan(void)
{
	u8 KeyVal=0;
	GPIO_Write(GPIOC,(GPIOC->ODR & 0xfff0 | 0x000f)); //不管其余12位0xf0ff，先让PC0到PC3全部输出高。
	if(((GPIOC->IDR & 0x00f0)|(GPIOE->IDR & 0x000f))==0x0000)  //如果PC4、PC5、PA0、PA1全为零则没有按键按下
	{  
		printf("\r\n20\r\n");
		return 20;
	}
	
	GPIO_Write(GPIOC,((GPIOC->ODR & 0xfff0) | 0x0001));   //仅将PC0置高	
	switch((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))       //第一行，由低到高，同理，不赘述
	{
		case 0x0001: return KeyVal=1;
		case 0x0002: return KeyVal=2;
		case 0x0004: return KeyVal=3;
		case 0x0008: return KeyVal=10;
	}
	while(((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))> 0)  //等待按键释放，同理，不赘述
	GPIO_Write(GPIOC,0x0000);   //重新让PC0到PC3全部输出低。	

	GPIO_Write(GPIOC,((GPIOC->ODR & 0xfff0) | 0x0002));	//仅将PC1置高
	switch((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))       //第一行，由低到高，同理，不赘述
	{
		case 0x0001:return KeyVal=4;
		case 0x0002:return KeyVal=5;
		case 0x0004:return KeyVal=6;
		case 0x0008:return KeyVal=11;
	}
	while(((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))> 0)  //等待按键释放，同理，不赘述
    GPIO_Write(GPIOC,0x0000);   //重新让PC0到PC3全部输出低。   
	
	
	GPIO_Write(GPIOC,((GPIOC->ODR & 0xfff0) | 0x0004));	//仅将PC2置高
	switch((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))       //第一行，由低到高，同理，不赘述
	{
		case 0x0001:return KeyVal=7;
		case 0x0002:return KeyVal=8;
		case 0x0004:return KeyVal=9;
		case 0x0008:return KeyVal=12;
	}
	while(((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))> 0)  //等待按键释放，同理，不赘述
    GPIO_Write(GPIOC,0x0000);   //重新让PC0到PC3全部输出低。   
	
		
	GPIO_Write(GPIOC,((GPIOC->ODR & 0xfff0) | 0x0008));	//仅将PC3置高
    switch((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))       //第一行，由低到高，同理，不赘述
	{
		case 0x0001:return KeyVal=13;
		case 0x0002:return KeyVal=14;
		case 0x0004:return KeyVal=15;
		case 0x0008:return KeyVal=16;
	}
	while(((GPIOC->IDR & 0x00f0) | (GPIOE->IDR & 0x000f))> 0)  //等待按键释放，同理，不赘述
	GPIO_Write(GPIOC,0x0000);   //重新让PC0到PC3全部输出低。  
}

void Key_Character(u16 KeyVal){
	char character=0;
	switch (KeyVal)
	{
		case 1: {
			character='1';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'1',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 2: {
			character='2';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'2',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 3: {
			character='3';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'3',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 4: {
			character='4';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'4',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 5: {
			character='5';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'5',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 6: {
			character='6';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'6',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 7: {
			character='7';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'7',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 8: {
			character='8';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'8',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 9: {
			character='9';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'9',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 10: {
			character='A';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'A',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 11: {
			character='B';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'B',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 12: {
			character='C';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'C',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 13: {
			character='*';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'*',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 14: {
			character='0';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'0',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 15: {
			character='#';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'#',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		case 16: {
			character='D';
			printf("\r\n%c\r\n",character);
			OLED_ShowChar(64,40,'D',12,1);
		}
		OLED_Refresh_Gram();
		break;
		
		default:break;
	}
	
}






