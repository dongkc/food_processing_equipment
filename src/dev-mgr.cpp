#include "dev-mgr.h"

extern "C" {
    #include "stm32f10x.h"
    #include "stm32f10x_iwdg.h"
    #include "stm32f10x_adc.h"
}

#define ADC1_DR_Address    ((u32)0x4001244C)

using namespace std;
using namespace stm32plus;

__IO uint32_t g_swb_delay;

namespace {


void ADC1_GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable DMA clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* Enable ADC1 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);

    /* Configure PC.01  as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // PC1,输入时不用设置速率
}

void ADC1_Mode_Config()
{
    DMA_InitTypeDef DMA_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    /* DMA channel1 configuration */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&g_swb_delay;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
     
  /* ADC1 configuration */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel11 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void ADC1_Init()
{
    ADC1_GPIO_Config();
    ADC1_Mode_Config();
}

void IWDG_Configuration()
{
     /*  写入0x5555,用于允许狗狗寄存器写入功能 */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    /*  狗狗时钟分频,40K/256=156HZ(6.4ms)*/
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    /*  喂狗时间 5s/6.4MS=781 .注意不能大于0xfff*/
    IWDG_SetReload(781);
    IWDG_ReloadCounter();
    IWDG_Enable();
} 

}

namespace Zebra {

static DevMgr dev_mgr;
DevMgr* const g_dev_mgr = &dev_mgr;

DevMgr::DevMgr()
    :pa(GPIOA),
     pb(GPIOB),
     pc(GPIOC)
{
    digital_input[0] = &pc[14];
    digital_input[1] = &pc[15];
    digital_input[2] = &pc[10];
    digital_input[3] = &pc[11];
    digital_input[4] = &pc[12];
    digital_input[5] = &pc[13];

    sw_a     = &pc[1];
    sw_b     = &pc[3];

    digital_output[0] = &pb[5];
    digital_output[1] = &pb[4];
    digital_output[2] = &pb[7];
    digital_output[3] = &pb[6];
    digital_output[4] = &pb[9];
    digital_output[5] = &pb[8];

    dip_a_0  = &pa[7];
    dip_a_1  = &pa[6];
    dip_a_2  = &pa[5];
    dip_a_3  = &pa[4];

    dip_b_0  = &pb[0];
    dip_b_1  = &pc[5];
    dip_b_2  = &pc[4];
    dip_b_3  = &pb[10];

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    for (uint8_t i = 0; i < 6; ++i) {
        digital_output[i]->reset();
        digital_output[i]->initialise(GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
    }
}

void DevMgr::init() {

    for (uint8_t i = 0; i < 6; ++i) {
        digital_input[i]->initialise(GPIO_Speed_50MHz, GPIO_Mode_IPU);
    }

    sw_a->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    sw_b->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);

    dip_a_0->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_a_1->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_a_2->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_a_3->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);

    dip_b_0->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_b_1->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_b_2->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);
    dip_b_3->initialise(GPIO_Speed_10MHz, GPIO_Mode_IPU);

    ADC1_Init();
    
    //IWDG_Configuration();
}

DevMgr::~DevMgr()
{
}

uint8_t DevMgr::readDipA()
{
    return (dip_a_3->read() << 3 |
            dip_a_2->read() << 2 |
            dip_a_1->read() << 1 |
            dip_a_0->read());
}

uint8_t DevMgr::readDipB()
{
    return (dip_b_3->read() << 3 |
            dip_b_2->read() << 2 |
            dip_b_1->read() << 1 |
            dip_b_0->read());
}

}  // namespace Zebra
