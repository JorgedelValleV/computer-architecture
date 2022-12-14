		#include "44b.h"
#include "gpio.h"

/* Port B interface implementation */

int portB_conf(int pin, enum port_mode mode)
{
	int ret = 0;
	if (pin < 0 || pin > 10)
		return -1; // indica error

	if (mode == SIGOUT)
		// COMPLETAR: poner en rPCONB el bit indicado por pin a 1 para que por
		// dicho pin en el puerto B salga la seÃ±al correspondiente del
		// controlador de memoria
		rPCONB = rPCONB | (1 << pin);
	else if (mode == OUTPUT)
		// COMPLETAR: poner en rPCONB el bit indicado por pin a 0 para que dicho
		// pin sea un pin de salida
		rPCONB = rPCONB & (~(1 << pin));
	else
		ret = -1; // indica error

	return ret;
}

int portB_write(int pin, enum digital val)
{
	if (pin < 0 || pin > 10)
		return -1; // indica error

	if (val < 0 || val > 1)
		return -1; // indica error

	if (val)
		// COMPLETAR: poner en rPDATB el bit indicado por pin a 1
		rPDATB = rPDATB | (1 << pin);
	else
		// COMPLETAR: poner en rPDATB el bit indicado por pin a 0
		rPDATB = rPDATB & (~(1 << pin));
	return 0;
}

/* Port G interface implementation */

int portG_conf(int pin, enum port_mode mode)
{
	int pos  = pin*2;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	switch (mode) {
		case INPUT:
			// COMPLETAR: poner en rPCONG 00 a partir de la posiciÃ³n pos para
			// configurar como pin de entrada el pin indicado por el parÃ¡metro pin
			rPCONG = rPCONG & (~(1 << pos));
			rPCONG = rPCONG & (~(1 << pos+1));
			break;
		case OUTPUT:
			// COMPLETAR: poner en rPCONG 01 a partir de la posiciÃ³n pos para
			// configurar como pin de salida el pin indicado por el parÃ¡metro pin
			rPCONG = rPCONG & (~(0 << pos));
			rPCONG = rPCONG | (~(1 << pos+1));
			break;
		case SIGOUT:
			// COMPLETAR: poner en rPCONG 10 a partir de la posiciÃ³n pos para
			// que salga la seÃ±al interna correspondiente por el pin indicado
			// por el parÃ¡metro pin
			rPCONG = rPCONG & (~(1 << pos));
			rPCONG = rPCONG & (~(0 << pos+1));
			break;
		case EINT:
			// COMPLETAR: poner en rPCONG 11 a partir de la posiciÃ³n pos para
			// habilitar la generaciÃ³n de interrupciones externas por el pin
			// indicado por el parÃ¡metro pin
			rPCONG = rPCONG & (~(0 << pos));
			rPCONG = rPCONG & (~(0 << pos+1));
			break;
		default:
			return -1;
	}

	return 0;
}

int portG_eint_trig(int pin, enum trigger trig)
{
	// A COMPLETAR EN LA SEGUNDA PARTE DE LA PRÃ�CTICA
	return 0;
}

int portG_write(int pin, enum digital val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (val < 0 || val > 1)
		return -1; // indica error

	if ((rPCONG & (0x3 << pos)) != (0x1 << pos))
		return -1; // indica error

	if (val)
		// COMPLETAR: poner en rPDATG el bit indicado por pin a 1
		rPDATG = rPDATG | (1 << pin);
	else
		// COMPLETAR: poner en rPDATG el bit indicado por pin a 0
		rPDATG = rPDATG & (~(0 << pin));
	return 0;
}

int portG_read(int pin, enum digital* val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (rPCONG & (0x3 << pos))
		return -1; // indica error

	if ((rPDATG & (1 << pin)) >> pin)/*COMPLETAR: true si estÃ¡ a 1 en rPDATG el pin indicado por el parÃ¡metro pin*/))
		*val = HIGH;
	else
		*val = LOW;

	return 0;
}

int portG_conf_pup(int pin, enum enable st)
{
	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (st != ENABLE && st != DISABLE)
		return -1; // indica error

	if (st == ENABLE)
		// COMPLETAR: poner el pin de rPUPG indicado por el parametro pin al valor adecuado,
		// para activar la resistencia de pull-up
		rPUPG = rPUPG & (~(0 << pin));
	else
		// COMPLETAR: poner el pin de rPUPG indicado por el parametro pin al valor adecuado,
		// para desactivar la resistencia de pull-up
		rPUPG = rPUPG | (1 << pin);
	return 0;
}

