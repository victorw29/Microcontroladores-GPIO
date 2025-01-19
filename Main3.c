#include <stdio.h>
#include "pico/stdlib"

/* Função para tocar uma nota por um determinado tempo (em milissegundos) */
void tocar_nota(int frequencia, int duracao_ms) {
    int tempo = 1000000 / frequencia; // cálculo de tempo para cada ciclo
    for (int i = 0; i < (duracao_ms * 1000) / tempo; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(tempo / 2);
        gpio_put(BUZZER, 0);
        sleep_us(tempo / 2);
    }
}

int main() {
    stdio_init_all();
    
    // Inicializa LEDs e Buzzer
    iniciar_leds();
    inicializar_buzzer();
    
    // Inicializa o teclado
    inicializar_keypad();

    // Loop para ler as teclas pressionadas
    while (true) {
        char keyPressed = obter_tecla();
        printf("Tecla pressionada: %c\n", keyPressed);

        if (keyPressed >= '1' && keyPressed <= '8') {
            tocar_musica(keyPressed); // Toca a nota associada à tecla
        } else if (keyPressed == '#' || keyPressed == '*') {
            acionar_todos_leds(); // Liga todos os LEDs
        } else if (keyPressed == 'A') {
            acionar_led(LED_RED); // Liga LED vermelho
        } else if (keyPressed == 'B') {
            acionar_led(LED_GREEN); // Liga LED verde
        } else if (keyPressed == 'C') {
            acionar_led(LED_BLUE); // Liga LED azul
        } else if (keyPressed == 'X') {
            desligar_todos_leds(); // Desliga todos os LEDs
            desligar_buzzer(); // Desliga o buzzer
        }

        sleep_ms(250); // Delay para evitar leitura contínua
    }

    return 0;
}
