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
#include "string.h"



//定义最大屏分辨率时,LCD所需的帧缓存数组大小
uint16_t g_ltdc_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));

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
  hltdc.Init.HorizontalSync = 19;
  hltdc.Init.VerticalSync = 2;
  hltdc.Init.AccumulatedHBP = 159;
  hltdc.Init.AccumulatedVBP = 22;
  hltdc.Init.AccumulatedActiveW = 159+PIXELS_W;
  hltdc.Init.AccumulatedActiveH = 622;
  hltdc.Init.TotalWidth = 159+PIXELS_W+160;
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
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = LTDC_BUFF_ADDR;
  pLayerCfg.ImageWidth = PIXELS_W;
  pLayerCfg.ImageHeight = PIXELS_H;
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

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
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

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

// 电源打开
void LTDC_ON(void)
{
    HAL_GPIO_WritePin(LCD_BK_GPIO_Port,LCD_BK_Pin,1);
}
// 电源关闭
void LTDC_OFF(void)
{
    HAL_GPIO_WritePin(LCD_BK_GPIO_Port,LCD_BK_Pin,0);
}



// 初始化
void LTDC_Init(void)
{
		
		__HAL_RCC_DMA2D_CLK_ENABLE();               //使能DMA2D时钟
		__HAL_LTDC_LAYER_ENABLE(&hltdc,0);
		__HAL_LTDC_LAYER_DISABLE(&hltdc,1);
		__HAL_LTDC_RELOAD_CONFIG(&hltdc);

    LTDC_ON();
    LTDC_Clear(0XFFFFFFFF);         //清屏
    return;
}

// 清屏
void LTDC_Clear(uint32_t color)
{
	if(PIXELS_DIR){
		 LTDC_Fill(0,0,PIXELS_W-1,PIXELS_H-1,color);
	}else{
		 LTDC_Fill(0,0,PIXELS_H-1,PIXELS_W-1,color);
	}
   
}

//画点函数
void LTDC_Draw_Point(uint16_t x,uint16_t y,uint32_t color)
{
    //坐标系转换
    if(PIXELS_DIR)	//横屏
    {
        *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*y+x))=color;
    } else			//竖屏
    {
        *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*(PIXELS_H-x-1)+y))=color;
    }
}
//读点函数
uint32_t LTDC_Read_Point(uint16_t x,uint16_t y)
{
    //坐标系转换
    if(PIXELS_DIR)	//横屏
    {
        return *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*y+x));
    } else			//竖屏
    {
        return *(uint16_t*)((uint32_t)LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*(PIXELS_H-x-1)+y));
    }
}

//LTDC填充矩形,DMA2D填充
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//color:要填充的颜色
//有时候需要频繁的调用填充函数，所以为了速度，填充函数采用寄存器版本，
//不过下面有对应的库函数版本的代码。
void LTDC_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{
    uint32_t psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
    uint32_t timeout=0;
    uint16_t offline;
    uint32_t addr;

    //坐标系转换
    if(PIXELS_DIR)	//横屏
    {
        psx=sx;
        psy=sy;
        pex=ex;
        pey=ey;
    } else			//竖屏
    {
        psx=sy;
        psy=PIXELS_H-ex-1;
        pex=ey;
        pey=PIXELS_H-sx-1;
    }
    offline=PIXELS_W-(pex-psx+1);
    addr=(LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*psy+psx));

    __HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
    //DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
		
		
    DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
		// 设置 DMA2D 采用寄存器往存储器传输数据模式，即 DMA2D 将 OCOLR 寄存器设置颜色值填充到存储器里面。
    DMA2D->OPFCCR=LTDC_PIXEL_FORMAT_RGB565;	//设置颜色格式
		
    DMA2D->OOR=offline;				//设置行偏移

    DMA2D->OMAR=addr;				//输出存储器地址
    DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器
    DMA2D->OCOLR=color;						//设定输出颜色寄存器
		
    DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
    while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
    {

    }
    DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志
}

 




//矩形彩色填充函数
void LTDC_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
		uint32_t psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
    uint32_t timeout=0;
    uint16_t offline;
    uint32_t addr;

    //坐标系转换
    if(PIXELS_DIR)	//横屏
    {
        psx=sx;
        psy=sy;
        pex=ex;
        pey=ey;
    } else			//竖屏
    {
        psx=sy;
        psy=PIXELS_H-ex-1;
        pex=ey;
        pey=PIXELS_H-sx-1;
    }
		
    offline=PIXELS_W-(pex-psx+1);
    addr=(LCD_FRAME_BUF_ADDR+PIXELS_BYTE*(PIXELS_W*psy+psx));

	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	//DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
		
	DMA2D->CR=DMA2D_M2M;			//存储器到存储器模式

		
	DMA2D->FGMAR=(uint32_t)color;		//源地址
	DMA2D->OMAR=addr;				//输出存储器地址
		
	DMA2D->FGOR=0;					//前景层行偏移为0
	DMA2D->OOR=offline;				//设置行偏移 

	DMA2D->FGPFCCR=0X02;	//设置颜色格式
	DMA2D->OPFCCR  = LTDC_PIXEL_FORMAT_RGB565;
		
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器 
		
	DMA2D->CR|=DMA2D_CR_START;					//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)		//等待传输完成
	{

	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;				//清除传输完成标志  	
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
