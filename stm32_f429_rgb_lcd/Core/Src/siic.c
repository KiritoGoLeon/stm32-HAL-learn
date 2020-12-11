#include "siic.h"


#define SIIC_SDA_PORT      GPIOI
#define SIIC_SDA_PIN  	GPIO_PIN_3
#define SIIC_SDA_PORT_LCK __HAL_RCC_GPIOI_CLK_ENABLE();   //ʹ��GPIOHʱ��


#define SIIC_SCL_PORT      GPIOH
#define SIIC_SCL_PIN  	GPIO_PIN_6
#define SIIC_SCL_PORT_LCK __HAL_RCC_GPIOH_CLK_ENABLE();   //ʹ��GPIOHʱ��


#define SIIC_SDA_H  HAL_GPIO_WritePin(SIIC_SDA_PORT,SIIC_SDA_PIN,GPIO_PIN_SET)
#define SIIC_SDA_L  HAL_GPIO_WritePin(SIIC_SDA_PORT,SIIC_SDA_PIN,GPIO_PIN_RESET)

#define SIIC_SCL_H  HAL_GPIO_WritePin(SIIC_SCL_PORT,SIIC_SCL_PIN,GPIO_PIN_SET)
#define SIIC_SCL_L  HAL_GPIO_WritePin(SIIC_SCL_PORT,SIIC_SCL_PIN,GPIO_PIN_RESET)

#define SIIC_SPEED_DELAY()       delay_us(2)
#define SIIC_SPEED_START_DELAY()  delay_us(30)


void SIIC_SDA_OUT()
{
		GPIO_InitTypeDef GPIO_Initure;
    //SDA
    GPIO_Initure.Pin=SIIC_SDA_PIN;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(SIIC_SDA_PORT,&GPIO_Initure);     //��ʼ��
}
void SIIC_SIIC_SDA_IN()
{
		GPIO_InitTypeDef GPIO_Initure;
    //SDA
    GPIO_Initure.Pin=SIIC_SDA_PIN;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(SIIC_SDA_PORT,&GPIO_Initure);     //��ʼ��
}

uint8_t SIIC_SIIC_SDA_Read(void)
{
	
    return HAL_GPIO_ReadPin(SIIC_SDA_PORT,SIIC_SDA_PIN);
}

void SIIC_SIIC_SDA_Write(uint8_t state)
{
    HAL_GPIO_WritePin(SIIC_SDA_PORT,SIIC_SDA_PIN,state);
}



//SIIC��ʼ��
void SIIC_Init(void)
{
		GPIO_InitTypeDef GPIO_Initure;

    SIIC_SDA_PORT_LCK;
    SIIC_SCL_PORT_LCK;

    // SCL
    GPIO_Initure.Pin=SIIC_SCL_PIN;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(SIIC_SCL_PORT,&GPIO_Initure);     //��ʼ��

    //SDA
    GPIO_Initure.Pin=SIIC_SDA_PIN;
    HAL_GPIO_Init(SIIC_SDA_PORT,&GPIO_Initure);     //��ʼ��

    SIIC_SDA_H;
    SIIC_SCL_H;
}

//����SIIC��ʼ�ź�
void SIIC_Start(void)
{
    SIIC_SDA_OUT();     //sda�����
    SIIC_SDA_H;
    SIIC_SCL_H;
    SIIC_SPEED_START_DELAY();
    SIIC_SDA_L;//START:when CLK is high,DATA change form high to low
    SIIC_SPEED_DELAY();
    SIIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����SIICֹͣ�ź�
void SIIC_Stop(void)
{
    SIIC_SDA_OUT();//sda�����
    SIIC_SCL_L;
    SIIC_SDA_L;//STOP:when CLK is high DATA change form low to high
    SIIC_SPEED_START_DELAY();
    SIIC_SCL_H;
    SIIC_SPEED_DELAY();
    SIIC_SDA_H;//����I2C���߽����ź�

}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t SIIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    SIIC_SIIC_SDA_IN();
    SIIC_SDA_H;
    SIIC_SCL_H;
    SIIC_SPEED_DELAY();
    while(SIIC_SIIC_SDA_Read())
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            SIIC_Stop();
            return 1;
        }
        SIIC_SPEED_DELAY();
    }
    SIIC_SCL_L;//ʱ�����0
    return 0;
}
//����ACKӦ��
void SIIC_Ack(void)
{
    SIIC_SCL_L;
    SIIC_SDA_OUT();
    SIIC_SDA_L;
    SIIC_SPEED_DELAY();
    SIIC_SCL_H;
    SIIC_SPEED_DELAY();
    SIIC_SCL_L;
}
//������ACKӦ��
void SIIC_NAck(void)
{
    SIIC_SCL_L;
    SIIC_SDA_OUT();
    SIIC_SDA_H;
    SIIC_SPEED_DELAY();
    SIIC_SCL_H;
    SIIC_SPEED_DELAY();
    SIIC_SCL_L;
}
//SIIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void SIIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SIIC_SDA_OUT();
    SIIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0; t<8; t++)
    {

        SIIC_SIIC_SDA_Write(((txd&0x80)>>7));
        txd<<=1;
        SIIC_SPEED_DELAY();   //��TEA5767��������ʱ���Ǳ����
        SIIC_SCL_H;
        SIIC_SPEED_DELAY();
        SIIC_SCL_L;
        SIIC_SPEED_DELAY();
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t SIIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SIIC_SIIC_SDA_IN();//SDA����Ϊ����
    SIIC_SPEED_START_DELAY();
    for(i=0; i<8; i++ )
    {
        SIIC_SCL_L;
        SIIC_SPEED_DELAY();
        SIIC_SCL_H;
        receive<<=1;
        if(SIIC_SIIC_SDA_Read())
        {

            receive++;
        }
        SIIC_SPEED_DELAY();
    }
    if (!ack)
        SIIC_NAck();//����nACK
    else
        SIIC_Ack(); //����ACK
    return receive;
}