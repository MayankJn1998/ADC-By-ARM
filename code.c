#include "stm32F4xx_HAL.h"

//Defining prototypes
void config(void);
void ADC_config(void);
void sysTickConfig(void);
void delay(int ms);

//Defining global variables
ADC_HandleTypeDef HandlerDef;
uint32_t convertedVal;

int main(){
	HAL_Init();
	config();
	ADC_config();
	sysTickConfig();
	
	while(1){
		HAL_ADC_Start(&HandlerDef);
		if(HAL_ADC_PollForConversion(&HandlerDef,5) == HAL_OK){
				convertedVal = HAL_ADC_GetValue(&HandlerDef);
		}
		HAL_ADC_Stop(&HandlerDef);
		delay(100);
	}
}
//Configuring I/O pins
void config(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef def;
	def.Mode = GPIO_MODE_ANALOG;
	def.Pin = GPIO_PIN_0;
	def.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&def);
}
//Configuring ADC
void ADC_config(){
	__HAL_RCC_ADC1_CLK_ENABLE();
	HandlerDef.Instance = ADC1;
	HandlerDef.Init.Resolution = ADC_RESOLUTION_8B;
	HandlerDef.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HandlerDef.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	HAL_ADC_Init(&HandlerDef);
	
	ADC_ChannelConfTypeDef cDef;
	cDef.Rank = 1;
	cDef.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	cDef.Channel = ADC_CHANNEL_0;
	HAL_ADC_ConfigChannel(&HandlerDef,&cDef);
	
}

void sysTickConfig(){
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	
	HAL_NVIC_SetPriority(SysTick_IRQn,0,0);
	HAL_NVIC_EnableIRQ(SysTick_IRQn);
	
}
void delay(int ms){
	for(int i=0;i<4000*ms;++i){
		;
	}
}

void systickHandler(){
	HAL_IncTick();
}
