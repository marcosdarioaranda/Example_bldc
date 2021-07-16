/*
===============================================================================
 Name        : Example_bldc.c
 Author      : Ms. Ing. Marcos D. Aranda
 Version     : 1.0
 Copyright   : $(copyright)
 Description : Este ejemplo se utiliza un motor BLDC con la placa LPC1769
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <sapi_gpio.h>
#include <sapi_rit.h>
#include "retardos.h"
// TODO: insert other definitions and declarations here
uint32_t velocidad = 1300,i;

static void Activar_Motor(void);

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    	// TODO: insert code here
    	/*Inicializo el GPIO para control del pulso para el motor BLDC*/
    	gpioInit(0,27,GPIO_OUTPUT);

    	/*Envio la señal de activación*/
    	Activar_Motor();

    	/*Controlo el motor a una velocidad= 1300*/
    	Init_RITimer(20);

    	while(1){


    	}

        return 0;
    }

static void Activar_Motor(void){
   	for (i=1;i<=250;i++){
   		gpioWrite(0,27, ON);
   		delayMs(0, 1);
    	gpioWrite(0,27, OFF);
    	delayMs(0, 19);
    }
}

void RIT_IRQHandler(void){
   gpioWrite(0,27, ON);
   delayUs(0, velocidad);
   gpioWrite(0,27, OFF);
   Clear_RITimer();
}
