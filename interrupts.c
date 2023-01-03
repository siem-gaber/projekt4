#include "header.h"

/********************************************************************************
ISR (PCINT0_vect): Avbrott för knapp 
********************************************************************************/
ISR (PCINT0_vect)
{
	disable_pin_change_interrupt(IO_PORTB);		//Inaktiverar PCI avbrott på knappens io-port för skydd mot kontaktstudsar.
	timer_enable_interrupt(&t0);				//Startar timerkrets för kontaktstudsskydd.
	
	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp1);		//Printar temperaturen vid knapptryck
		
		timer_reset_counter(&t1);				//Resetar tiden i timern som skriver ut temperaturen.
		
	}
	
	return;
}


/********************************************************************************
ISR (TIMER1_COMPA_vect): Avbrott för timern för utskrift av temperatur
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	timer_count(&t1);						//Räknar upp timern
	
	if (timer_elapsed(&t1))					//Kollar om timern löpt ut
	{
		tmp36_print_temperature(&temp1);	//Skriver ut temperaturen
	}
	
	return;
}

/********************************************************************************
ISR (TIMER0_OVF_vect): Avbrott för timern för kontaktstudsskydd
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	timer_count(&t0);							//Räknar upp timern
	
	if (timer_elapsed(&t0))						//Kollar om timern har löpt ut
	{
		enable_pin_change_interrupt(IO_PORTB);	//Återställer avbrott för knappen
		timer_disable_interrupt(&t0);			//Stänger av avbrotten för timern
	}
	
	return;
}