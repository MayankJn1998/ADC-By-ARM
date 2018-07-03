#include "stm32F4xx_HAL.h"

//Defining prototypes
void config();
void ADC_config();
void sysTickConfig();
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
void config(){
}

void ADC_config(){
}

void sysTickConfig(){
}
void delay(int ms){
}
