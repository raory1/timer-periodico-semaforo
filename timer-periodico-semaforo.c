#include <stdio.h>
#include "pico/stdlib.h"

const uint PIN_LEDS[3] = {11, 12, 13};
#define DELAY_MS 3000

uint8_t controlador = 0;

bool atualizar_semaforo(struct repeating_timer *t)
{
    //Desliga todos os LEDs
    for (int i = 0; i < 3; i++)
    {
        gpio_put(PIN_LEDS[i], 0);
    }

    gpio_put(PIN_LEDS[controlador], 1); // Acende o LED correspondente ao estado atual
    controlador = (controlador + 1)%3; //  Avança para o próximo estado

    return true;
}

int main()
{
    stdio_init_all();
    // Inicialização e configuração dos LEDs
    for (int i = 0; i < 3; i++)
    {
        gpio_init(PIN_LEDS[i]);
        gpio_set_dir(PIN_LEDS[i], GPIO_OUT);
    }
    struct repeating_timer timer;
    add_repeating_timer_ms(-DELAY_MS, atualizar_semaforo, NULL, &timer);

    //  Loop principal
    while (true)
    {
        printf("Semaforo operando normalmente. [ESTADO ATUAL: %d]\n", controlador);
        sleep_ms(1000);
    }
}
