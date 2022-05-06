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

#define FECHADA 0       // SW fechada
#define ABERTA  1       // SW aberta
#define DBC     1000    // Debounce
#define PULA    2
#define ATRASA  3
#define ACELERA 4

volatile int somaX[8], somaY[8];
volatile int mediaX=0, mediaY=0;
volatile float X, Y;
volatile int movimento = FALSE;     // indica qual movimento o dino deve fazer

volatile char matriz[340];

// FUN��ES
// configura��es
void adc_config(void);
void io_ADC_config(void);
void timers_config(void);

// outras
int sw_mon(void);

void vai(char x);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    clk_20mhz();            //<<<=== SMCLK = 20 MHz
    ta2_config();
    gpio_config();
    uart_config();
    usci_b1_config();
    rrand_inic();

    adc_config();
    io_ADC_config();
    timers_config();

    __enable_interrupt();
    espera_10ms(10);

    oled_buf_apaga();
    oled_wr_cmdo(vet_cmdo1,27);
    oled_wr_cmdo(vet_cmdo2,4);
    oled_buf_vai();
    espera_10ms(10);

    // Tela de inicio
    // Espera botao

    int ox = 10, oy = 35;
    int contador_pulo = 0;
    int velocidade[] = {0,-2,-4,-6,-8,-10,-12,-14,-15,-16,-17,-18,-19,-19,-20,-20,-20,-20,-19,-19,-18,-17,-16,-15,-14,-12,-10,-8,-6,-4,-2};
    unsigned int pos_cacto = 125, ha_cacto = 1, ocupado;



    while(TRUE){
        oled_buf_apaga();
        if (movimento == 2 && !contador_pulo) {
            contador_pulo = 31;
        }
        if (contador_pulo){
            --contador_pulo;
        }

        if (!ha_cacto){
            ha_cacto = 1;
            pos_cacto = 125;
        }
        if (ha_cacto){
            pos_cacto -= 2;
            ocupado = printCacto(cacto1, pos_cacto);
            if (pos_cacto <= 1){
                ha_cacto--;
                apagaCacto(cacto1, pos_cacto);
            }
        }

        if (printDino(dino1, ox, oy + velocidade[contador_pulo], ocupado)){
            while(TRUE);
        }
        oled_linha(0,45,127,45,PX_ON);


        oled_buf_vai();
        espera_10ms(3);
    }

    return 0;
}

//_________________________________________________________________________________
void adc_config(void){
    ADC12CTL0 &= ~ADC12ENC;             // Desabilitar para configurar

    ADC12CTL0 = ADC12ON;                // Ligar ADC
    ADC12CTL1 = ADC12CONSEQ_3       |   // Modo sequ�ncia de canais repetidos
                ADC12SHS_1          |   // Selecionar TA0.1
                ADC12CSTARTADD_0    |   // Resultado a partir de ADC12MEM0
                ADC12SSEL_3;            // ADC12CLK = SMCLK
    // 12 bits -> Por default no ADC12CTL2

    // Convers�o alternada
    ADC12MCTL0 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL1 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL2 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL3 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)

    ADC12MCTL4 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL5 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL6 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL7 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)

    ADC12MCTL8 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL9 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL10 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL11 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)

    ADC12MCTL12 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A1 (P6.1)
    ADC12MCTL13 = ADC12INCH_2 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL14 = ADC12INCH_1 | ADC12SREF_0;  //Entrada A2 (P6.2)
    ADC12MCTL15 = ADC12INCH_2 | ADC12SREF_0 | ADC12EOS; //Entrada A2 (P6.2) -> �ltima

    ADC12CTL0 |= ADC12ENC;      // Habilitar ADC12
    ADC12IE |= ADC12IE15;       // Habilitar interrup��o

    P6SEL |= BIT4 | BIT3 | BIT2 | BIT1; // Desligar o digital dos canais
}
//_________________________________________________________________________________
//INTERRUP��O DO ADC
// #pragma vector = 54
#pragma vector = ADC12_VECTOR
__interrupt void adc_int(void){

    volatile int i=0;

    somaX[0] = ADC12MEM0;
    somaX[1] = ADC12MEM2;
    somaX[2] = ADC12MEM4;
    somaX[3] = ADC12MEM6;

    somaX[4] = ADC12MEM8;
    somaX[5] = ADC12MEM10;
    somaX[6] = ADC12MEM12;
    somaX[7] = ADC12MEM14;

    somaY[0] = ADC12MEM1;
    somaY[1] = ADC12MEM3;
    somaY[2] = ADC12MEM5;
    somaY[3] = ADC12MEM7;

    somaY[4] = ADC12MEM9;
    somaY[5] = ADC12MEM11;
    somaY[6] = ADC12MEM13;
    somaY[7] = ADC12MEM15;

    mediaX = mediaY = 0;

    for(i=0; i<8; i++){
        mediaX+=somaX[i];
    }
    i=0;
    for(i=0; i<8; i++){
        mediaY+=somaY[i];
    }
    mediaX = mediaX/8;
    mediaY = mediaY/8;

    X = (3.3*mediaX)/4095.0;
    Y = (3.3*mediaY)/4095.0;

    if(X <=0.5 )   movimento = ATRASA;
    else if(X >= 2.5)    movimento = ACELERA;
    else if(Y <=0.5)    movimento = PULA;
    else movimento = 0;

}
//_________________________________________________________________________________
void io_ADC_config(void){
    // Eixos do joystick
    P6SEL |= BIT1;  // Eixo X P6.1
    P6SEL |= BIT2;  // Eixo Y P6.2

    P6DIR &= ~BIT5;     // SWITCH JOYSTICK P6.5
    P6REN |= BIT5;      // PULLUP
    P6OUT |= BIT5;      // SA�DA
}
//_________________________________________________________________________________
void timers_config(void){
    //TA0.1 para o ADC;
    TA0CTL = TASSEL_1 | MC_1  ;             // ACLK e modo UP

    TA0CCTL1 = OUTMOD_6;                    // Out = modo 6
    TA0CCR0 = 512;                          // ACLK 64Hz
    TA0CCR1 = 256;                          // Carga 50%

}

int sw_mon(void){
    static int psw=ABERTA;          // Guardar passado de SW
    if((P6IN&BIT5) == 0){           // Qual estado atual de SW?
         if( psw == ABERTA){        // Qual o passado de SW?
             psw = FECHADA;
             return TRUE;
         }
    }
    else {
        if(psw == FECHADA){     // Qual o passado de SW?
            psw = ABERTA;
            return FALSE;
        }
    }
    return FALSE;
}



