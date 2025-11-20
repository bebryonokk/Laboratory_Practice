#include "../Inc/init.h"

uint16_t freq[3][3] = {{2500, 769, 500}, {1667, 265, 455}, {1250, 526, 400}};
bool led1_shine = false;
uint16_t TickCounter = 0;
uint16_t PrevDelay = 0;
bool led1 = false;
bool led2 = false;
bool led3 = false;
bool led4 = false;
bool led5 = false;
bool led6 = false;

void GPIO_INIT(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN); // включение тактирования шины GPIOC
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0);                         // настройка режима работы порта C0 и С1 на вывод сигнала
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE4_0);
    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE0_0);
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE3 | GPIO_MODER_MODE2); // явная настройка порта С13 на прием сигнала
    CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1);  // настройка типа выхода портов С0 и С1 на режим Output Push-Pull
    CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT4);
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT0);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0 | GPIO_OSPEEDER_OSPEEDR1_0); // настройка скорости работы портов С0 и С1 на среднюю
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0 | GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR4_0);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0);
    CLEAR_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1); // настраиваем подтяжки/стяжки пинов С0 и С1
    CLEAR_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR4);
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPDR0);
    SET_BIT(GPIOC->PUPDR, GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0);
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR0 | GPIO_BSRR_BR1); // выключение диода перед началом
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0 | GPIO_BSRR_BR1 | GPIO_BSRR_BR4);
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);

    SET_BIT(GPIOC->MODER, GPIO_MODER_MODE9_1);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED9);
    MODIFY_REG(GPIOC->AFR[1], GPIO_AFRH_AFSEL9, 0X00UL);
}

void RCC_INIT(void)
{
    /*Предварительная очистка регистров RCC */
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL); // Очистка битов HSITRIM и установка 1000 0000
    CLEAR_REG(RCC->CFGR);                        // Очистка регистра CFGR
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET)
        ;                             // Проверка очистки регистра CR
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON); // Очистка бита PLLON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET)
        ;                                            // Проверка очистки бита PLLON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON); // Очистка битов HSEON, CSSON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET)
        ;                              // Проверка очистки битов HSEON, CSSON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); // Очистка бита HSEBYP в регистре CR

    /*Настройка главного регистра RCC */
    SET_BIT(RCC->CR, RCC_CR_HSION); // Запускаем HSI
    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET)
        ; // Ждём пока он запустится

    /*Настройка регистра PLLCFGR*/
    CLEAR_REG(RCC->PLLCFGR);                                        // Очищаем регистр PLLCFGR
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI);                  // Источник тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_3);                      // Деление источника тактирования на 8
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5); // Настрока умножения на 96
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                    // Делитель для выхода PLL(PLLCLK) на 2
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_2);                      // Делитель для USB на 4

    /*Настройка регистра CFGR*/
    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                         // Источник системного тактирования -> выход PLL
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                    // Делитель AHB1 -> 0
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);                     // Делитель APB1 -> 2 (48 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV1);                     // Делитель APB2 -> 1 (96 МГц)
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                         // Выход MCO2 -> Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1); // Делитель для MCO2 -> 4

    /*Настрйока частоты FLASH-памяти*/
    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_3WS);

    /*Включение блока PLL*/
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET)
        ;
}

void IQR_INIT(void)
{
    /*Включение тактирование периферии SYSCFG*/
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    /*Обозначение снятие внешеного сигнала с линии PC3*/
    MODIFY_REG(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI3_Msk, SYSCFG_EXTICR1_EXTI3_PC);
    MODIFY_REG(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI2_Msk, SYSCFG_EXTICR1_EXTI2_PC);

    /*Настройка регистров EXTI*/
    SET_BIT(EXTI->IMR, EXTI_IMR_IM3 | EXTI_IMR_IM2);    // Включение маскирование
    CLEAR_BIT(EXTI->EMR, EXTI_EMR_EM3 | EXTI_EMR_EM2);  // Отключение генерации события
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR3 | EXTI_RTSR_TR2); // Настройка отслеживания по спаду (кнопка была отпущена)
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR3 | EXTI_FTSR_TR2); // Настройка отслеживания по фронту (кнопка была нажата)

    /*Настройка регистров NVIC*/
    NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); // Выбор приоретета прерывания
    NVIC_EnableIRQ(EXTI3_IRQn);                                                          // Разрешение прерывания
    NVIC_SetPriority(EXTI2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(EXTI2_IRQn);
}

void SYSTIMER_INIT(void)
{
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk,
               95999 << SysTick_LOAD_RELOAD_Pos);
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk,
               95999 << SysTick_VAL_CURRENT_Pos);
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}

void working_mode(uint8_t num, uint8_t LED_OPTION[2][6])
{
    uint8_t smth;
    if (num == 0)
        smth = 1;
    else
        smth = num;

    uint16_t shine = LED_OPTION[1][num];
    uint16_t mode = LED_OPTION[0][num];
    uint16_t CurrentFreq = freq[LED_OPTION[1][num]][LED_OPTION[0][num]];
    switch (num)
    {
    case 0:
        led1 = !led1;
        GPIOA->BSRR |= GPIO_BSRR_BS_0;
        Delay(CurrentFreq);
        led1 = !led1;
        GPIOA->BSRR |= GPIO_BSRR_BR_0;
        Delay(CurrentFreq);
        break;
    case 1:
        led2 = !led2;
        GPIOA->BSRR |= GPIO_BSRR_BR_0;
        GPIOA->BSRR |= GPIO_BSRR_BS_1;
        Delay(CurrentFreq);
        led2 = !led2;
        GPIOA->BSRR |= GPIO_BSRR_BR_1;
        Delay(CurrentFreq);
        break;
    case 2:
        led3 = !led3;
        GPIOA->BSRR |= GPIO_BSRR_BR_1;
        GPIOA->BSRR |= GPIO_BSRR_BS_4;
        Delay(CurrentFreq);
        led3 = !led3;
        GPIOA->BSRR |= GPIO_BSRR_BR_4;
        Delay(CurrentFreq);
        break;
    case 3:
        led4 = !led4;
        GPIOA->BSRR |= GPIO_BSRR_BR_4;
        GPIOB->BSRR |= GPIO_BSRR_BS_0;
        Delay(CurrentFreq);
        led4 = !led4;
        GPIOB->BSRR |= GPIO_BSRR_BR_0;
        Delay(CurrentFreq);
        break;
    case 4:
        led5 = !led5;
        GPIOB->BSRR |= GPIO_BSRR_BR_0;
        GPIOC->BSRR |= GPIO_BSRR_BS_1;
        Delay(CurrentFreq);
        led5 = !led5;
        GPIOC->BSRR |= GPIO_BSRR_BR_1;
        Delay(CurrentFreq);
        break;
    case 5:
        led6 = !led6;
        GPIOC->BSRR |= GPIO_BSRR_BR_1;
        GPIOC->BSRR |= GPIO_BSRR_BS_0;
        Delay(CurrentFreq);
        led6 = !led6;
        GPIOC->BSRR |= GPIO_BSRR_BR_0;
        Delay(CurrentFreq);
        break;
    default:
        GPIOC->BSRR |= GPIO_BSRR_BR_0;
        break;
    }
}

// uint16_t freq[3][3] = {{2500, 769, 500}, {1667, 265, 455}, {1250, 526, 400}};
// bool led1_shine = false;
// uint16_t TickCounter = 0;
