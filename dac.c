#include <xc.h>
#include <stdint.h>

// Configurações do clock
#pragma config FOSC = INTOSCIO_EC
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = OFF
#pragma config FCMEN = OFF

// Definir as portas de saída
#define DAC_CS RC2
#define LED RC0

// Variável para armazenar o valor digital a ser enviado ao DAC
uint8_t dacValue = 0;

// Função para enviar o valor digital ao DAC
void sendToDAC(uint8_t value) {
  DAC_CS = 0; // Selecionar o DAC
  SPI1_Write(value); // Enviar o valor para o DAC
  DAC_CS = 1; // Deselecionar o DAC
}

void main(void) {
  // Configurar o clock interno para 8 MHz
  OSCCON = 0b01110010;

  // Configurar o modo de operação do DAC
  SSP1CON1 = 0b00100000;

  // Configurar as portas de saída
  TRISC2 = 0; // CS do DAC
  TRISC0 = 0; // LED

  // Loop principal
  while (1) {
    sendToDAC(dacValue); // Enviar o valor digital ao DAC
    LED = dacValue & 0x01; // Atualizar o brilho do LED
    dacValue = (dacValue + 1) % 256; // Incrementar o valor digital
    __delay_ms(10); // Pausar por 10 ms
  }
}
