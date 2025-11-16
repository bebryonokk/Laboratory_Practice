#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F411xE/stm32f411xe.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"
#include <math.h>
#include "../Inc/init.h"
int main(void)
{
    uint32_t counter = 0;
    Init_of_myself_macroses();
    Init_of_hand_writing();
    Init_with_macroses();
    int but_check = 0;
    int herz = 1;
    while (1)
    {
        while(READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) == RESET)
        {
            counter++;  
        }
        if(counter < 10000)
        {
            counter = 0;
        }
        if (counter > 10000 && counter < 300000)
        {
            but_check++;
            counter = 0;
        }
        else if(counter > 10000)
        {
            herz++;
            counter = 0;
        }
        if (but_check > 5)
        {
            but_check = 0;
        }
        if(herz > 3)
        {
            herz = 1;
        }
        uint64_t delay = pow(herz, 3) * 25000;
        switch (but_check)
        {
        case 0:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            break;
        case 1:
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            for(uint32_t i = 0; i < delay; i++)
            {
                RCC_GPIOA_BSRR |= P4_HIGH;
            }
            for(uint32_t i = 0; i < delay; i++)
            {
                RCC_GPIOA_BSRR |= P4_LOW;
            }
            break;
        case 2:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
              for(uint32_t i = 0; i < delay; i++)
            {
                *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            }
            for(uint32_t i = 0; i < delay; i++)
            {
                *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            }
            break;
        case 3:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BS1;
              for(uint32_t i = 0; i < delay; i++)
            {
                GPIOC->BSRR |= GPIO_BSRR_BS1;
            }
            for(uint32_t i = 0; i < delay; i++)
            {
                GPIOC->BSRR |= GPIO_BSRR_BR1;
            }
            break;
            break;
        case 4:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BS0 + GPIO_BSRR_BR1;
              for(uint32_t i = 0; i < delay; i++)
            {
                GPIOC->BSRR |= GPIO_BSRR_BS0;
            }
            for(uint32_t i = 0; i < delay; i++)
            {
                GPIOC->BSRR |= GPIO_BSRR_BR0;
            }
            break;
        case 5:
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            RCC_GPIOA_BSRR |= P4_HIGH;
            GPIOC->BSRR |= GPIO_BSRR_BS0 + GPIO_BSRR_BS1;
              for(uint32_t i = 0; i < delay; i++)
            {
                *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            RCC_GPIOA_BSRR |= P4_HIGH;
            GPIOC->BSRR |= GPIO_BSRR_BS0 + GPIO_BSRR_BS1;
            }
            for(uint32_t i = 0; i < delay; i++)
            {
                RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            }
            break;
        }
    }
}