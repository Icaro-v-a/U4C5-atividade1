#include <stdio.h>
#include "pico/stdlib.h"

// definindo os LEDs
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

// PROTÓTIPOS DE FUNÇÕES
void ligar_semaforo(void);

void led_init()
{
    // configuração inicial dos LEDs

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_put(LED_YELLOW, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);
}

int main()
{
    stdio_init_all();
    led_init();
    while(true){
        ligar_semaforo();
    }
    
}

void ligar_semaforo(void)
{
    gpio_put(LED_RED, 1);
    sleep_ms(3000);
    gpio_put(LED_RED, 0);

    gpio_put(LED_YELLOW, 1);
    sleep_ms(3000);
    gpio_put(LED_YELLOW, 0);

    gpio_put(LED_GREEN, 1);
    sleep_ms(3000);
    gpio_put(LED_GREEN, 0);
}