#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO correspondentes aos LEDs do semáforo
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

// Variável global para armazenar o estado atual do semáforo
volatile int estado = 0;

// Protótipos das funções
bool semaforo_callback(struct repeating_timer *t);
void led_init(void);

// Função para inicializar os LEDs
void led_init()
{
    // Inicializa o LED vermelho, define como saída e o desliga inicialmente
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    // Inicializa o LED amarelo, define como saída e o desliga inicialmente
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_put(LED_YELLOW, 0);

    // Inicializa o LED verde, define como saída e o desliga inicialmente
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);
}

// Callback que será chamado periodicamente pelo temporizador para alternar o estado do semáforo
bool semaforo_callback(struct repeating_timer *t)
{
    // Desliga todos os LEDs antes de ativar o próximo estado
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_GREEN, 0);

    // Alterna entre os estados do semáforo
    if (estado == 0)
    {
        gpio_put(LED_RED, 1); // Liga o LED vermelho
        estado = 1;           // Próximo estado será o amarelo
    }
    else if (estado == 1)
    {
        gpio_put(LED_YELLOW, 1); // Liga o LED amarelo
        estado = 2;              // Próximo estado será o verde
    }
    else
    {
        gpio_put(LED_GREEN, 1); // Liga o LED verde
        estado = 0;             // Próximo estado será o vermelho
    }

    return true; // Retorna true para manter a repetição do temporizador
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial
    led_init();       // Configura os LEDs

    // Liga o LED vermelho inicialmente ao iniciar o sistema
    gpio_put(LED_RED, 1);
    estado = 1; // Define o próximo estado como o amarelo

    struct repeating_timer timer_semaforo;

    // Configura um temporizador que chama a função semaforo_callback a cada 3 segundos
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer_semaforo);

    // Variável para controle do tempo da impressão serial
    uint64_t tempo_anterior = time_us_64();

    while (true)
    {
        uint64_t tempo_atual = time_us_64();

        // Verifica se passou 1 segundo (1.000.000 microssegundos) desde a última impressão
        if ((tempo_atual - tempo_anterior) >= 1000000)
        {
            printf("Semáforo operando...\n"); // Mensagem para monitoramento
            tempo_anterior = tempo_atual; // Atualiza o tempo de referência
        }

        tight_loop_contents(); // Mantém o loop eficiente sem consumir CPU desnecessária
    }
}
