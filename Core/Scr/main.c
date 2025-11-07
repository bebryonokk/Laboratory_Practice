#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F411xE/stm32f411xe.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

// #include "init.c"
#include "../Inc/init.h"
int main(void)
{
    Init_of_myself_macroses();
    Init_of_hand_writing();
    Init_with_macroses();
    int but_check = 0;
    int pusher = 1;
    int all_light = 0;
    while (1)
    {
        if((((GPIOC->IDR) & GPIO_IDR_ID13) == 0) && (pusher == 1))
        {
            pusher = 0;
        }
        if ((((GPIOC->IDR) & GPIO_IDR_ID13) != 0) && (pusher == 0))
        {
            but_check++;
            all_light++;
            pusher = 1;
            int smth = 0;
            for(int i = 0; i < 100000; i++)
            {smth++;}
        }
        if (but_check > 4)
        {
            but_check = 0;
        }
        switch (but_check)
        {
        case 0:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            break;
        case 1:
            RCC_GPIOA_BSRR |= P4_HIGH;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            break;
        case 2:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BR1;
            break;
        case 3:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BR0 + GPIO_BSRR_BS1;
            break;
            break;
        case 4:
            RCC_GPIOA_BSRR |= P4_LOW;
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL;
            GPIOC->BSRR |= GPIO_BSRR_BS0 + GPIO_BSRR_BR1;
            break;
        }
        if (all_light == 5)
        {
            *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x1UL;
            RCC_GPIOA_BSRR |= P4_HIGH;
            GPIOC->BSRR |= GPIO_BSRR_BS0 + GPIO_BSRR_BS1;
        }
        if (all_light > 5)
        {
            all_light = 0;
        }
    }
}
