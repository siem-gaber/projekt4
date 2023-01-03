#include "header.h"

/* Definition av globala objekt: */
struct button b1;    /* Tryckknappar. */
struct timer t0, t1; /* Timerkretsar. */
struct tmp36 temp1;

/********************************************************************************
* setup: Initieringar av knapp med avbrott, Två timerkretsar med avbrott och 
		 temperaturmätaren
********************************************************************************/
void setup(void)
{
	

	button_init(&b1, 13);
	button_enable_interrupt(&b1);
	timer_init(&t0, TIMER_SEL_0, 300);
	timer_init(&t1, TIMER_SEL_1, 60000);
	tmp36_init(&temp1, A2);
	timer_enable_interrupt(&t1);

	return;
}