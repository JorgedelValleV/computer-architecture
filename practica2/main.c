#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "gpio.h"

struct RLstat {
	int moving;
	int speed;
	int iter;
	int direction;
	int position;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.iter = 0,
	.direction = 0,
	.position = 0,
};
int contadorPulsaciones = 0;
int reproduceHola = 0;
int contadorHola = 0;

int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuración para espera activa */

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h hay
	//que configurar los pines 6 y 7 del puerto G como pines de entrada y
	//activar las correspondientes resistencias de pull-up
	
	/*******************************************/
	portG_conf(6, INPUT);
	portG_conf(7, INPUT);
	portG_conf_pup(6, ENABLE);
	portG_conf_pup(7, ENABLE);

	led1_on();
	led2_on();

	Delay(0);
	return 0;
}

int loop(void)
{
	unsigned int buttons = read_button();

	if (buttons & BUT1) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que apagar ambos leds
		// También hay que comutar la dirección del movimiento del led rotante
		// representado por el campo direction de la variable RL
		led1_switch();
		//contadorPulsaciones++;
	}

	if (buttons & BUT2) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// Incrementar contador de pulsaciones. Si es par, conumtar led1. Si es impar, conmutar el led2.
		// También hay que comutar el estado de movimiento del led rotante
		// representado por el campo moving de la variable RL, y en caso de
		// ponerlo en marcha debemos reiniciar el campo iter al valor del campo
		// speed.
		contadorPulsaciones++;
		led2_switch();
		RL.direction = (RL.direction) ? 0 : 1;
		if(!RL.moving){
			RL.moving = 1;
			RL.iter = RL.speed;
		}

	}
	if(contadorPulsaciones <= 9){
		D8Led_digit(contadorPulsaciones);
	}
	else{
		reproduceHola = 1;
	}

	if(reproduceHola == 1){

		if(contadorHola == 0){
			D8Led_digit(16);
		}
		else if(contadorHola == 1){
			D8Led_digit(0);
		}
		else if(contadorHola == 2){
			D8Led_digit(17);
		}
		else if(contadorHola == 3){
			D8Led_digit(10);
		}
		else if(contadorHola == 4){
			D8Led_digit(18);
		}
		else if(contadorHola == 5){
			D8Led_digit(18);
		}
		contadorHola++;
		if(contadorHola == 6){
			reproduceHola = 0;
			contadorPulsaciones = 0;
			contadorHola = 0;
		}

	}

	if (RL.moving) {
		RL.iter--;
		if (RL.iter == 0) {
			// COMPLETAR: debemos hacer avanzar el led rotante una posición en
			// la dirección indicada por el campo direction de la variable RL.
			// La posición actual está representada en el campo position.
			// Recordar que queremos un movimiento circular, representado por
			// las 6 primeras posiciones en el array Segmentes del display de 8
			// segmentos, por lo que position debe estar siempre entre 0 y 5.
			RL.position = (RL.direction)? (RL.position + 1) % 6 : (RL.position + 5) % 6 ;
			RL.iter = RL.speed;
			D8Led_segment(RL.position);
		}
	}

	Delay(2000); // espera de 200ms para que el bucle se repita 5 veces por segundo
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
