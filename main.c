#include "stm32f10x.h"
#include "delay.h"



void PWM_Init(void){

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);

	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

	TIM_OCStructInit(&TIM_OCInitStruct);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;;
	TIM_OCInitStruct.TIM_Pulse = 50;

	TIM_OC2Init(TIM4, &TIM_OCInitStruct);
	TIM_Cmd(TIM4,ENABLE);
}

void PWM_SetCompare1(uint16_t compare){
	TIM_SetCompare2(TIM4, compare);
}


 int main(void)
 {	

	uint16_t i;
	delay_init();
	PWM_Init();

		while(1)
	{
		for(i = 0; i < 100; i ++){
			PWM_SetCompare1(i);
			delay_ms(10);
		}
		for(i = 0; i < 100; i ++){
			PWM_SetCompare1(100 - i);
			delay_ms(10);
		}
		
	}
 }
