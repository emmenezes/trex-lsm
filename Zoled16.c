// Zoled
// Básico para desenvolvimento

// P4.1 = SDA e P4.2 = SCL

#include <msp430.h> 
#include "Defines.h"
#include "Globais.h"
#include "Gpio.h"
#include "I2c.h"
#include "Oled.h"
#include "Uart.h"
#include "Timer.h"
#include "Aleat.h"
#include "dino.h"


void vai(char x);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    clk_20mhz();            //<<<=== SMCLK = 20 MHz
    ta2_config();
    gpio_config();
    uart_config();
    usci_b1_config();
    rrand_inic();
    __enable_interrupt();
    espera_10ms(10);

    oled_buf_apaga();
    oled_buf_vai();

    // Tela de inicio
    // Espera botao

    int pulo = 0, ox = 5, oy = 25;
    int contador_pulo = 0;
    int velocidade[] = {0, -2, -2, -4, -8, -4, -2, -2};
    int pos_cacto = 125, ha_cacto = 1;


    while(TRUE){
        oled_buf_apaga();
        if (pulo && !contador_pulo) {
            contador_pulo = 7;
            pulo--;
        }
        if (contador_pulo){
            --contador_pulo;
        }
        if (!ha_cacto){
            ha_cacto = 1;
        }
        if (ha_cacto){
            pos_cacto -= 2;
            printCacto(cacto1, pos_cacto);
            if (pos_cacto == -9)
                ha_cacto--;
        }

        //printDino(dino1, ox, oy + velocidade[contador_pulo]);
        oled_linha(0,35,127,35,PX_ON);


        oled_buf_vai();
        espera_10ms(10);
    }

    return 0;
}
