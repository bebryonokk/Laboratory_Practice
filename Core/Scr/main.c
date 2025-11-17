#include "../Inc/init.h"

uint8_t but_check = 0;
uint8_t pusher = 0;
uint8_t first_led = 0;
uint8_t second_led = 0;
uint8_t third_led = 0;
uint8_t fourth_led = 0;

int main(void)
{
    GPIO_INIT();
    while (1)
    {
        if ((READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) == RESET) && (pusher == 0))
        {
            pusher = time_skeeper();
        }
        if ((READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) != RESET) && (pusher == 1))
        {
            but_check = diode_mode(pusher, but_check);
            pusher = 0;
        }
        main_process(but_check);
        if (but_check == 1)
        {
            first_led = 1;
            second_led = 0;
            third_led = 0;
            fourth_led = 0;
        }
        if (but_check == 2)
        {
            first_led = 0;
            second_led = 1;
            third_led = 0;
            fourth_led = 0;
        }
        if (but_check == 3)
        {
            first_led = 0;
            second_led = 0;
            third_led = 1;
            fourth_led = 0;
        }
        if (but_check == 4)
        {
            first_led = 0;
            second_led = 0;
            third_led = 0;
            fourth_led = 1;
        }
        if (but_check == 5)
        {
            first_led = 1;
            second_led = 1;
            third_led = 1;
            fourth_led = 1;
        }
        else
        {
            first_led = 0;
            second_led = 0;
            third_led = 0;
            fourth_led = 0;
        }
    }
}   
