/**
  ******************************************************************************
  * File Name          : LTDC.c
  * Description        : This file provides code for the configuration
  *                      of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ltdc.h"

/* USER CODE BEGIN 0 */
#include "dma2d.h"

//����������ֱ���ʱ,LCD�����֡���������С
uint16_t g_ltdc_framebuf[PIXELS_W][PIXELS_H] __attribute__((at(LCD_FRAME_BUF_ADDR)));
void LTDC_Layer_Parameter_Config(uint8_t layerx,uint32_t bufaddr,uint8_t pixformat,uint8_t alpha,uint8_t alpha0,uint8_t bfac1,uint8_t bfac2,uint32_t bkcolor);

/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{
  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 20-1;
  hltdc.Init.VerticalSync = 2;
  hltdc.Init.AccumulatedHBP = 20-1+140;
  hltdc.Init.AccumulatedVBP = 22;
  hltdc.Init.AccumulatedActiveW = 20-1+140+PIXELS_W;
  hltdc.Init.AccumulatedActiveH = 622;
  hltdc.Init.TotalWidth = 20-1+140+PIXELS_W+160;
  hltdc.Init.TotalHeigh = 634;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = PIXELS_W;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = PIXELS_H;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = LTDC_BUFF_ADDR;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = 0;
  pLayerCfg1.WindowX1 = 1024;
  pLayerCfg1.WindowY0 = 0;
  pLayerCfg1.WindowY1 = 600;
  pLayerCfg1.Alpha = 0;
  pLayerCfg1.Alpha0 = 255;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg1.FBStartAdress = 0;
  pLayerCfg1.ImageWidth = 0;
  pLayerCfg1.ImageHeight = 0;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */
    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* USER CODE BEGIN LTDC_MspInit 1 */



  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11);

  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

// ��Դ��
void LTDC_ON(void)
{
    HAL_GPIO_WritePin(LCD_BK_GPIO_Port,LCD_BK_Pin,1);
}
// ��Դ�ر�
void LTDC_OFF(void)
{
    HAL_GPIO_WritePin(LCD_BK_GPIO_Port,LCD_BK_Pin,0);
}

uint8_t LTDC_Clk_Set(uint32_t pllsain,uint32_t pllsair,uint32_t pllsaidivr)
{
	RCC_PeriphCLKInitTypeDef PeriphClkIniture;
	
	//LTDC�������ʱ�ӣ���Ҫ�����Լ���ʹ�õ�LCD�����ֲ������ã�
    PeriphClkIniture.PeriphClockSelection=RCC_PERIPHCLK_LTDC;	//LTDCʱ�� 	
	PeriphClkIniture.PLLSAI.PLLSAIN=pllsain;    
	PeriphClkIniture.PLLSAI.PLLSAIR=pllsair;  
	PeriphClkIniture.PLLSAIDivR=pllsaidivr;
	if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkIniture)==HAL_OK)    //��������ʱ��
    {
        return 0;   //�ɹ�
    }
    else return 1;  //ʧ��    
}


// ��ʼ��
void LTDC_Init(void)
{
		
	  __HAL_RCC_DMA2D_CLK_ENABLE();               //ʹ��DMA2Dʱ��
	
		LTDC_Layer_Parameter_Config(0,0XC0000000,0X02,255,0,6,7,0X000000);//���������
    HAL_LTDC_SetWindowPosition(&hltdc,0,0,0);  //���ô��ڵ�λ��
    HAL_LTDC_SetWindowSize(&hltdc,PIXELS_W,PIXELS_H,0);//���ô��ڴ�С
    LTDC_ON();
    LTDC_Clear(0XFFFFFFFF);         //����
    return;
}

// ����
void LTDC_Clear(uint32_t color)
{
	if(PIXELS_DIR){
		 LTDC_Fill(0,0,PIXELS_W-1,PIXELS_H-1,color);
	}else{
		 LTDC_Fill(0,0,PIXELS_H-1,PIXELS_W-1,color);
	}
   
}

//���㺯��
void LTDC_Draw_Point(uint16_t x,uint16_t y,uint32_t color)
{
    //����ϵת��
    if(PIXELS_DIR)	//����
    {
        *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*y+x))=color;
    } else			//����
    {
        *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*(PIXELS_H-x-1)+y))=color;
    }
}
//���㺯��
uint32_t LTDC_Read_Point(uint16_t x,uint16_t y)
{
    //����ϵת��
    if(PIXELS_DIR)	//����
    {
        return *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*y+x));
    } else			//����
    {
        return *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*(PIXELS_H-x-1)+y));
    }
}

//LTDC������,DMA2D���
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)
//color:Ҫ������ɫ
//��ʱ����ҪƵ���ĵ�����亯��������Ϊ���ٶȣ���亯�����üĴ����汾��
//���������ж�Ӧ�Ŀ⺯���汾�Ĵ��롣
void LTDC_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{
    uint32_t psx,psy,pex,pey;	//��LCD���Ϊ��׼������ϵ,����������仯���仯
    uint32_t timeout=0;
    uint16_t offline;
    uint32_t addr;

    //����ϵת��
    if(PIXELS_DIR)	//����
    {
        psx=sx;
        psy=sy;
        pex=ex;
        pey=ey;
    } else			//����
    {
        psx=sy;
        psy=PIXELS_H-ex-1;
        pex=ey;
        pey=PIXELS_H-sx-1;
    }
    offline=PIXELS_W-(pex-psx+1);
    addr=(LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*psy+psx));

    __HAL_RCC_DMA2D_CLK_ENABLE();	//ʹ��DM2Dʱ��
    DMA2D->CR&=~(DMA2D_CR_START);	//��ֹͣDMA2D
    DMA2D->CR=DMA2D_R2M;			//�Ĵ������洢��ģʽ
    DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;	//������ɫ��ʽ
    DMA2D->OOR=offline;				//������ƫ��

    DMA2D->OMAR=addr;				//����洢����ַ
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//�趨�����Ĵ���
    DMA2D->OCOLR=color;						//�趨�����ɫ�Ĵ���
    DMA2D->CR|=DMA2D_CR_START;				//����DMA2D
    while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//�ȴ��������
    {

    }
    DMA2D->IFCR|=DMA2D_FLAG_TC;		//���������ɱ�־
}

//LTDC,������������.
//ע��:�˺���,������LTDC_Layer_Window_Config֮ǰ����.
//layerx:��ֵ,0/1.
//bufaddr:����ɫ֡������ʼ��ַ
//pixformat:��ɫ��ʽ.0,ARGB8888;1,RGB888;2,RGB565;3,ARGB1555;4,ARGB4444;5,L8;6;AL44;7;AL88
//alpha:����ɫAlphaֵ,0,ȫ͸��;255,��͸��
//alpha0:Ĭ����ɫAlphaֵ,0,ȫ͸��;255,��͸��
//bfac1:���ϵ��1,4(100),�㶨��Alpha;6(101),����Alpha*�㶨Alpha
//bfac2:���ϵ��2,5(101),�㶨��Alpha;7(111),����Alpha*�㶨Alpha
//bkcolor:��Ĭ����ɫ,32λ,��24λ��Ч,RGB888��ʽ
//����ֵ:��
void LTDC_Layer_Parameter_Config(uint8_t layerx,uint32_t bufaddr,uint8_t pixformat,uint8_t alpha,uint8_t alpha0,uint8_t bfac1,uint8_t bfac2,uint32_t bkcolor)
{
	LTDC_LayerCfgTypeDef pLayerCfg;
	
	pLayerCfg.WindowX0=0;                       //������ʼX����
	pLayerCfg.WindowY0=0;                       //������ʼY����
	pLayerCfg.WindowX1=PIXELS_W ;          //������ֹX����
	pLayerCfg.WindowY1=PIXELS_H;         //������ֹY����
	pLayerCfg.PixelFormat=pixformat;		    //���ظ�ʽ
	pLayerCfg.Alpha=alpha;				        //Alphaֵ���ã�0~255,255Ϊ��ȫ��͸��
	pLayerCfg.Alpha0=alpha0;			        //Ĭ��Alphaֵ
	pLayerCfg.BlendingFactor1=(uint32_t)bfac1<<8;    //���ò���ϵ��
	pLayerCfg.BlendingFactor2=(uint32_t)bfac2<<8;	//���ò���ϵ��
	pLayerCfg.FBStartAdress=bufaddr;	        //���ò���ɫ֡������ʼ��ַ
	pLayerCfg.ImageWidth=PIXELS_W;        //������ɫ֡�������Ŀ��    
	pLayerCfg.ImageHeight=PIXELS_H;      //������ɫ֡�������ĸ߶�
	pLayerCfg.Backcolor.Red=(uint8_t)(bkcolor&0X00FF0000)>>16;   //������ɫ��ɫ����
	pLayerCfg.Backcolor.Green=(uint8_t)(bkcolor&0X0000FF00)>>8;  //������ɫ��ɫ����
	pLayerCfg.Backcolor.Blue=(uint8_t)bkcolor&0X000000FF;        //������ɫ��ɫ����
	HAL_LTDC_ConfigLayer(&hltdc,&pLayerCfg,layerx);   //������ѡ�еĲ�
}  

//���β�ɫ��亯��
void LTDC_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
		uint32_t psx,psy,pex,pey;	//��LCD���Ϊ��׼������ϵ,����������仯���仯
    uint32_t timeout=0;
    uint16_t offline;
    uint32_t addr;

    //����ϵת��
    if(PIXELS_DIR)	//����
    {
        psx=sx;
        psy=sy;
        pex=ex;
        pey=ey;
    } else			//����
    {
        psx=sy;
        psy=PIXELS_H-ex-1;
        pex=ey;
        pey=PIXELS_H-sx-1;
    }
    offline=PIXELS_W-(pex-psx+1);
    addr=(LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*psy+psx));

	__HAL_RCC_DMA2D_CLK_ENABLE();	//ʹ��DM2Dʱ��
	DMA2D->CR&=~(DMA2D_CR_START);	//��ֹͣDMA2D
	DMA2D->CR=DMA2D_M2M;			//�洢�����洢��ģʽ
	DMA2D->FGPFCCR=0X02;	//������ɫ��ʽ
	DMA2D->FGOR=0;					//ǰ������ƫ��Ϊ0
	DMA2D->OOR=offline;				//������ƫ�� 

	DMA2D->FGMAR=(uint32_t)color;		//Դ��ַ
	DMA2D->OMAR=addr;				//����洢����ַ
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//�趨�����Ĵ��� 
	DMA2D->CR|=DMA2D_CR_START;					//����DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)		//�ȴ��������
	{

	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;				//���������ɱ�־  	
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
