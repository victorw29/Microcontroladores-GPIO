// Função para inicializar o keypad

void inicializar_keypad() {
 for (uint i = 0; i < 8; i++) {
 gpio_init(1 + i);
 if (i < 4)
 gpio_set_dir(1 + i, GPIO_OUT);
 else
 gpio_set_dir(1 + i, GPIO_IN);
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
 gpio_put(1 + i, true); // Coloca as linhas em nível alto
 for (int j = 0; j < 4; j++) {
 if (gpio_get(5 + j)) { // Verifica se a coluna está em nível alto
 tecla = keypadKeys[i][j]; // A tecla pressionada
 }
 }
 gpio_put(1 + i, false); // Reseta as linhas
 }
 
 return tecla;
}