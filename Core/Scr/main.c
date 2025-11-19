#include "../Inc/init.h"
#include "../Inc/interrupt.h"

uint16_t TickCounter = 0;
uint16_t ButtonTicks = 0;
bool LedState = false;

int main(void)
{
    GPIO_INIT();
    RCC_INIT();
    IQR_INIT();
    SYSTIMER_INIT();

    while (1)
    {
        if (LedState)
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS1);
        else
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR1);
    }
}
