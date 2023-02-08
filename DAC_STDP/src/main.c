
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//DAC channel1 with DAC_OUT1 (PA4) as output
//DAC channel2 with DAC_OUT2 (PA5) as output


void GPIO_Config(void);
void DAC1_Config(void);
void delay(uint32_t);


int main(void)
{
	GPIO_Config();
	DAC1_Config();

  while (1)
  {
	  // creating triangle waveform

	 int D_Value = 1;
	 while(D_Value < 4000) {
		 DAC_SetChannel1Data(DAC_Align_12b_R, D_Value);
		 delay(21000);											// wait 1ms
		 D_Value+=100;
	 }

	 while(D_Value > 1) {
		 DAC_SetChannel1Data(DAC_Align_12b_R, D_Value);
		 delay(21000);											// wait 1ms
		 D_Value-=100;
	 }

  }
}


void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO.GPIO_Mode = GPIO_Mode_AN;
	GPIO.GPIO_Pin = GPIO_Pin_4;
	GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO);
}


void DAC1_Config(void)
{
	DAC_InitTypeDef dac = {0};

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	dac.DAC_WaveGeneration = DAC_WaveGeneration_None;
	dac.DAC_Trigger = DAC_Trigger_None;
	dac.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

	DAC_Init(DAC_Channel_1, &dac);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}


void delay(uint32_t time)
{
	while(time--);
}



/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
