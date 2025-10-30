#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F411xE/stm32f411xe.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

int main(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE5_0);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR5_1);
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
    
    while(1)
    {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
    }
}