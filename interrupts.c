#include "header.h"

/********************************************************************************
ISR (PCINT0_vect): Avbrott f�r knapp 
********************************************************************************/
ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);		//Inaktiverar PCI avbrott p� knappens io-port f�r skydd mot kontaktstudsar.
	timer_enable_interrupt(&t0);				//Startar timerkrets f�r kontaktstudsskydd.
	
	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp1);		//Printar temperaturen vid knapptryck
		
		timer_reset_counter(&t1);				//Resetar tiden i timern som skriver ut temperaturen.
		
	}
	
	return;
}


/********************************************************************************
ISR (TIMER1_COMPA_vect): Avbrott f�r timern f�r utskrift av temperatur
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	timer_count(&t1);						//R�knar upp timern
	
	if (timer_elapsed(&t1))					//Kollar om timern l�pt ut
	{
		tmp36_print_temperature(&temp1);	//Skriver ut temperaturen
	}
	
	return;
}

/********************************************************************************
ISR (TIMER0_OVF_vect): Avbrott f�r timern f�r kontaktstudsskydd
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&t0);							//R�knar upp timern
	
	if (timer_elapsed(&t0))						//Kollar om timern har l�pt ut
	{
		enable_pin_change_interrupt(IO_PORTB);	//�terst�ller avbrott f�r knappen
		timer_disable_interrupt(&t0);			//St�nger av avbrotten f�r timern
	}
	
	return;
}