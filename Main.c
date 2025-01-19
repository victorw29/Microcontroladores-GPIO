#include <stdio.h>
#include "pico/stdlib.h"

// Pinos
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUZZER 21

// Frequências das notas (em Hertz)
#define NOTE_C 261
#define NOTE_D 294
#define NOTE_E 329
#define NOTE_F 349
#define NOTE_G 392
#define NOTE_A 440
#define NOTE_B 466
#define NOTE_C_HIGH 523

/* Inicializa os pinos dos LEDs */
void iniciar_leds(void) {
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, false);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, false);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, false);
}

/* Liga todos os LEDs */
void acionar_todos_leds(void) {
    gpio_put(LED_RED, true);
    gpio_put(LED_GREEN, true);
    gpio_put(LED_BLUE, true);
}

/* Desliga todos os LEDs */
void desligar_todos_leds(void) {
    gpio_put(LED_RED, false);
    gpio_put(LED_GREEN, false);
    gpio_put(LED_BLUE, false);
}

/* Liga um LED específico */
void acionar_led(int led) {
    gpio_put(led, true);
}

/* Desliga um LED específico */
void desligar_led(int led) {
    gpio_put(led, false);
}

/* Inicializa o buzzer */
void inicializar_buzzer() {
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, false); // Garantir que o buzzer está desligado
}

/* Desliga o buzzer */
void desligar_buzzer() {
    gpio_put(BUZZER, 0); // Define o estado do buzzer como desligado
}

/* Função para tocar uma nota por um determinado tempo (em milissegundos) */
void tocar_nota(int frequencia, int duracao_ms) {
    int tempo = 1000000 / frequencia;  // cálculo de tempo para cada ciclo
    for (int i = 0; i < (duracao_ms * 1000) / tempo; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(tempo / 2);
        gpio_put(BUZZER, 0);
        sleep_us(tempo / 2);
    }
}

/* Função para tocar uma música com base na tecla pressionada */
void tocar_musica(char tecla) {
    switch (tecla) {
        case '1':  // Tecla '1' toca a nota C
            tocar_nota(NOTE_C, 500);
            break;
        case '2':  // Tecla '2' toca a nota D
            tocar_nota(NOTE_D, 500);
            break;
        case '3':  // Tecla '3' toca a nota E
            tocar_nota(NOTE_E, 500);
            break;
        case '4':  // Tecla '4' toca a nota F
            tocar_nota(NOTE_F, 500);
            break;
        case '5':  // Tecla '5' toca a nota G
            tocar_nota(NOTE_G, 500);
            break;
        case '6':  // Tecla '6' toca a nota A
            tocar_nota(NOTE_A, 500);
            break;
        case '7':  // Tecla '7' toca a nota B
            tocar_nota(NOTE_B, 500);
            break;
        case '8':  // Tecla '8' toca a nota C alta
            tocar_nota(NOTE_C_HIGH, 500);
            break;
        default:
            break;
    }
}

// Função para inicializar o keypad
void inicializar_keypad() {
    for (uint i = 0; i < 8; i++) {
        gpio_init(1 + i);
        if (i < 4)
            gpio_set_dir(1 + i, GPIO_OUT);  //Inicializa as portas 1 a 4 como saida
        else
            gpio_set_dir(1 + i, GPIO_IN);   //Inicializa as portas 5 a 8 como entrada
    }
}

// Função para obter a tecla pressionada do keypad
char obter_tecla() {
    char tecla = 'X';
    char keypadKeys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    for (int i = 0; i < 4; i++) {
        gpio_put(1 + i, true);  // Coloca as linhas em nível alto
        for (int j = 0; j < 4; j++) {
            if (gpio_get(5 + j)) {  // Verifica se a coluna está em nível alto
                tecla = keypadKeys[i][j];  // A tecla pressionada
            }
        }
        gpio_put(1 + i, false);  // Reseta as linhas
    }
    
    return tecla;
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

