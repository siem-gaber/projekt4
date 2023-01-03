#include "button.h"



/********************************************************************************
* button_clear: Nollställer tryckknapp samt motsvarande pin.
*
*               - self: Pekare till tryckknappen som ska nollställas.
********************************************************************************/
void button_clear(struct button* self)
{
	button_disable_interrupt(self);
	(*self->pullup) &= ~(1 << self->pin);

	self->pin = 0;
	self->pullup = 0;
	self->input = 0;
	self->pcmsk = 0;
	self->pcint = 0;
	return;
}

/********************************************************************************
* button_enable_interrupt: Aktiverar PCI-avbrott på angiven tryckknapp så att
*                          event på tryckknappens pin medför avbrott, både på
*                          stigande och fallande flank. Kontroll av flank måste
*                          skötas av användaren, förslagsvis via avläsning i
*                          motsvarande avbrottsrutin.
*
*                        
********************************************************************************/
void button_enable_interrupt(struct button* self)
{
	asm("SEI");
	PCICR |= (1 << self->pcint);
	*(self->pcmsk) |= (1 << self->pin);
	return;
}

/********************************************************************************
* button_init: Initierar ny tryckknapp på angiven pin.
*
*              - self: Pekare till tryckknappen som ska initieras.
*              - pin : Tryckknappens pin-nummer på Arduino Uno, exempelvis 13.
*                   
********************************************************************************/
void button_init(struct button* self,
const uint8_t pin)
{
	if (pin >= 0 && pin <= 7)
	{
		self->pin = pin;
		self->pullup = &PORTD;
		self->input = &PIND;
		self->pcmsk = &PCMSK2;
		self->pcint = PCINT2;
	}
	else if (pin >= 8 && pin <= 13)
	{
		self->pin = pin - 8;
		self->pullup = &PORTB;
		self->input = &PINB;
		self->pcmsk = &PCMSK0;
		self->pcint = PCINT0;
	}
	else if (pin >= 14 && pin <= 19)
	{
		self->pin = pin - 14;
		self->pullup = &PORTC;
		self->input = &PINC;
		self->pcmsk = &PCMSK1;
		self->pcint = PCINT1;
	}

	(*self->pullup) |= (1 << self->pin);
	return;
}