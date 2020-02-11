
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

char str[50];

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruc;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //PA2 Tx Pini olarak ayarladýk.

	GPIO_InitStruc.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruc.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruc.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruc.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruc);
}

void USART_Config()
{
	USART_InitTypeDef USART_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	USART_InitStruct.USART_BaudRate = 9600;		// kac saniye de bir veri gonderilecegini ayarladik.
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;		 //1 bilgisi geldiginde haberlesme duracak.
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // gonderilecek veri 8 bit

	USART_Init(USART2,&USART_InitStruct);
	USART_Cmd(USART2,ENABLE);
}

void USART_Puts(USART_TypeDef* USARTx , volatile char *s)
{
	while(*s)
	{
		while(!(USARTx -> SR & 0x00000040));

		USART_SendData(USARTx , *s);
		*s++;
	}
}

int main(void)
{
  while (1)
  {
	  sprintf(str,"Hello Word\n");
	  USART_Puts(USART2,str);
	  delay(1680000);

  }
}



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
