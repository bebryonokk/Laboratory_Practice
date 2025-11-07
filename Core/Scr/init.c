#include "../Inc/init.h"

/*диод, активируемый дефайнами PA4
диод, активируемый ручным вводом PВ0
диоды, активируемый макромами PС1 и PС0
кнопка PС13
*/

void Init_of_myself_macroses(void)
{
    RCC_AHB1EN |= RCC_GPIOAEN_EN;
    RCC_GPIOA_MODER |= RCC_GPIOA_P4_OUT;
    RCC_GPIOA_OTYPER |= RCC_GPIOA_OTYPER_P4_PP;
    RCC_GPIOA_OSPEED |= RCC_GPIOA_OSPEED_P4_MED;
    RCC_GPIOA_PUPDR |= RCC_GPIOA_PUPDR_P4_RST;
    RCC_GPIOA_BSRR |= P4_LOW;
}

void Init_of_hand_writing(void)
{
    *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x2UL;     // включение шины B
    *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x1UL;     // режим работы B0 на выход
    *(uint32_t *)(0x40020400UL + 0x04UL) |= 0x0UL;     // двухтактный выход
    *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x1UL;     // скорость средняя
    *(uint32_t *)(0x40020400UL + 0x0CUL) |= 0x0UL;     // выключение стяжек/подтяжек
    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL; // выключение диода перед началом
}

void Init_with_macroses(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                                    // включение шины C
    GPIOC->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0;               // режим работы C0 и C1 на выход
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE13);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT0 + GPIO_OTYPER_OT1);           // двухтактный выход
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0 + GPIO_OSPEEDER_OSPEEDR1_0; // скорость средняя
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1);        // выключение стяжек/подтяжек
    GPIOC->BSRR |= GPIO_BSRR_BR0 | GPIO_BSRR_BR1;                          // выключение диода перед началом
}