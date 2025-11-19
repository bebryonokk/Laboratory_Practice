#include "../Inc/interrupt.h"

extern uint16_t TickCounter;
extern uint16_t ButtonTicks;
extern bool LedState;

void SysTick_Handler(void)
{
    TickCounter++;
    //ButtonTicks++;
}

void EXTI3_IRQHandler(void)
{
    ButtonTicks++;

    if(ButtonTicks >= 2)
    {
        LedState = !LedState;
        ButtonTicks = 0;
    }
    SET_BIT(EXTI->PR, EXTI_PR_PR3);
}