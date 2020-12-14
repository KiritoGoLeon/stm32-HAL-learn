#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "touch.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��30
 ������ʵ��-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
#include "timer.h"
#include "lvgl.h"


int main(void)
{
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ��USART
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    SDRAM_Init();                   //��ʼ��SDRAM
	
		TIM3_Init(999,89);							//��ʱ����ʼ��(1ms�ж�),���ڸ�lvgl�ṩ��������
	
    LCD_Init();                     //��ʼ��LCD
		LCD_Display_Dir(1);						//�����RGB���Ļ�,��ǿ������Ϊ������ʾ
	
	  tp_dev.init();				    //��������ʼ�� 

	lv_init();											//lvglϵͳ��ʼ��
	lv_port_disp_init();						//lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ���
	lv_port_indev_init();						//lvgl����ӿڳ�ʼ��,����lv_init()�ĺ���
	lv_demo_widgets();

	//lv_demo_benchmark();
		while(1)
		{
			tp_dev.scan(0);//����ɨ��
			lv_task_handler();//lvgl��������
			 delay_ms(2);
		}
}
