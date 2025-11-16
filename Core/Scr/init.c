#include "../Inc/init.h"

/*диод, активируемый дефайнами PA4
диод, активируемый ручным вводом PВ0
диоды, активируемый макромами PС1 и PС0
кнопка PС13
*/

void Init_of_myself_macroses(void)
{
    // Обращение через дерективы и собственноручно написанные макросы
    SET_BIT(RCC_AHB1EN, RCC_GPIOAEN_EN);                // включение тактирования шины GPIOA
    SET_BIT(RCC_GPIOA_MODER, RCC_GPIOA_P4_OUT);         // настройка режима работы порта A4 на вывод сигнала
    SET_BIT(RCC_GPIOA_OTYPER, RCC_GPIOA_OTYPER_P4_PP);  // настройка типа выхода порта A4 на режим Output Push-Pull
    SET_BIT(RCC_GPIOA_OSPEED, RCC_GPIOA_OSPEED_P4_MED); // настройка скорости работы порта A4 на среднюю
    SET_BIT(RCC_GPIOA_PUPDR, RCC_GPIOA_PUPDR_P4_RST);   // настройка подтяжек/стяжек пина A4 на режим работы No Pull-Up, Pull-Down
    SET_BIT(RCC_GPIOA_BSRR, P4_LOW);                    // задаем нулевой сигнал на порте перед началом работы
}

void Init_of_hand_writing(void)
{
    // Прямое обращение к памяти
    *(uint32_t *)(0x40023800UL + 0x30UL) |= 0x2UL;     // включение тактирования шины GPIOB
    *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x1UL;     // настройка режима работы порта B0 на вывод сигнала
    *(uint32_t *)(0x40020400UL + 0x04UL) |= 0x0UL;     // настройка типа выхода порта B0 на режим Output Push-Pull
    *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x1UL;     // настройка скорости работы порта B0 на среднюю
    *(uint32_t *)(0x40020400UL + 0x0CUL) |= 0x0UL;     // настраиваем подтяжки/стяжки пина B0 на режим No Pull-Up, Pull-Down
    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x10000UL; // подаем нулевой сигнал на порт B0 перед началом работы
}

void Init_with_macroses(void)
{
    // Использование библиотеки CMSIS
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                     // включение тактирования шины GPIOB
    GPIOC->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0; // настройка режима работы порта B0 на вывод сигнала
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE13);
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT0 + GPIO_OTYPER_OT1);           // двухтактный выход
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0 + GPIO_OSPEEDER_OSPEEDR1_0; // скорость средняя
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1);        // выключение стяжек/подтяжек
    GPIOC->BSRR |= GPIO_BSRR_BR0 | GPIO_BSRR_BR1;                          // выключение диода перед началом
}

uint32_t but_hold_counter(void)
{
    uint32_t counter = 0;
    while(READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) == RESET)
        {
            counter++;  
        }
        return counter;
}

void Mode_and_diode_num(uint32_t counter)
{
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
}