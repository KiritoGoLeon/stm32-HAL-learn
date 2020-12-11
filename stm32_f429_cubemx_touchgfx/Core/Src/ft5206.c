#include "ft5206.h"
#include "siic.h"


//I2C��д����
#define FT_CMD_WR 				0X70    	//д����
#define FT_CMD_RD 				0X71		//������

//FT5206 ���ּĴ�������
#define FT_DEVIDE_MODE 					0x00   		//FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER       0x02		//����״̬�Ĵ���

#define FT_TP1_REG 				0X03	  	//��һ�����������ݵ�ַ
#define FT_TP2_REG 				0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 				0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 				0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 				0X1B		//��������������ݵ�ַ  


#define	FT_ID_G_LIB_VERSION		0xA1		//�汾		
#define FT_ID_G_MODE 			   	0xA4   		//FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP				0x80   		//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88   		//����״̬�������üĴ���


static const uint16_t FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};

static void delay_ms(uint32_t time)
{
    HAL_Delay(time);
}
uint8_t FT5206_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t i;
    uint8_t ret=0;
    SIIC_Start();
    SIIC_Send_Byte(FT_CMD_WR);	//����д����
    SIIC_Wait_Ack();
    SIIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
    SIIC_Wait_Ack();
    for(i=0; i<len; i++)
    {
        SIIC_Send_Byte(buf[i]);  	//������
        ret=SIIC_Wait_Ack();
        if(ret)break;
    }
    SIIC_Stop();					//����һ��ֹͣ����
    return ret;
}
//��FT5206����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���
void FT5206_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
    uint8_t i;
    SIIC_Start();
    SIIC_Send_Byte(FT_CMD_WR);   	//����д����
    SIIC_Wait_Ack();
    SIIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
    SIIC_Wait_Ack();
    SIIC_Start();
    SIIC_Send_Byte(FT_CMD_RD);   	//���Ͷ�����
    SIIC_Wait_Ack();
    for(i=0; i<len; i++)
    {
        buf[i]=SIIC_Read_Byte(i==(len-1)?0:1); //������
    }
    SIIC_Stop();	//����һ��ֹͣ����
}

void ft5206_init(void)
{
    uint8_t temp[2];
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��

    //PH7
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��

    //PI8
    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��

    SIIC_Init();

		HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET);				//��λ
    delay_ms(20);
    HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET);				//�ͷŸ�λ
    delay_ms(50);
    temp[0]=0;
    FT5206_WR_Reg(FT_DEVIDE_MODE,temp,1);	//������������ģʽ
    FT5206_WR_Reg(FT_ID_G_MODE,temp,1);		//��ѯģʽ
    temp[0]=22;								//������Чֵ��22��ԽСԽ����
    FT5206_WR_Reg(FT_ID_G_THGROUP,temp,1);	//���ô�����Чֵ
    temp[0]=12;								//�������ڣ�����С��12�����14
    FT5206_WR_Reg(FT_ID_G_PERIODACTIVE,temp,1);
    //��ȡ�汾�ţ��ο�ֵ��0x3003
    FT5206_RD_Reg(FT_ID_G_LIB_VERSION,&temp[0],2);
    if((temp[0]==0X30&&temp[1]==0X03)||temp[1]==0X01||temp[1]==0X02)//�汾:0X3003/0X0001/0X0002
    {
        printf("CTP ID:%x\r\n",((uint16_t)temp[0]<<8)+temp[1]);
        return ;
    }
		printf("CTP ID:%x\r\n",((uint16_t)temp[0]<<8)+temp[1]);
}


// ɨ��
uint8_t ft5206_scan(TouchTypedef *touch)
{
	uint8_t buf[4];
	uint8_t touch_num;
	uint8_t i = 0;
	uint8_t touch_state = 0;
	FT5206_RD_Reg(FT_REG_NUM_FINGER,&touch_num,1);//��ȡ�������״̬  
	touch->touch_num = touch_num;
	if((touch_num&0XF)&&((touch_num&0XF)<6))
 {
	 for(int i = 0;i<touch_num;i++){
		 FT5206_RD_Reg(FT5206_TPX_TBL[i],buf,4);
		 uint16_t x = 0;
		 uint16_t y = 0;
		 
		 if(touch->dir){
			 y = ((uint16_t)(buf[0]&0X0F)<<8)+buf[1];
			 x = ((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
		 }else{
			x = touch->pix_h - (((uint16_t)(buf[0]&0X0F)<<8)+buf[1]);
		  y = ((uint16_t)(buf[2]&0X0F)<<8)+buf[3];
		 }
		 touch->x[i] = x;
		 touch->y[i] = y;
	 }
 }else{
	 touch->touch_num = 0;
	 return 0;
 }
 return touch_num;
}