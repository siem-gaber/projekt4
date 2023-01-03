#include "serial.h"

/********************************************************************************
* serial_init: Initierar seriell transmission, där vi skickar en bit i taget
*              med angiven baud rate (bithastighet) mätt i kilobits per sekund
*              (kbps). Ett vagnreturstecken \r skickas så att första utskriften
*              hamnar längst till vänster.
*

********************************************************************************/
void serial_init(const uint16_t baud_rate_kbps)
{
	static bool serial_initialized = false;
	if (serial_initialized) return;

	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	UBRR0 = (uint16_t)(F_CPU / (16.0 * baud_rate_kbps) - 1 + 0.5);
	UDR0 = '\r';

	serial_initialized = true;
	return;
}

/********************************************************************************
* serial_print_char: Skickar angivet tecken till ansluten seriell terminal.
*
*                  
********************************************************************************/
void serial_print_char(const char c)
{
	while ((UCSR0A & (1 << UDRE0)) == 0);
	UDR0 = c;
	return;
}

/********************************************************************************
* serial_print_string: Skickar angivet textstycke till ansluten seriell terminal.

*                      - s: Textstycket som ska skickas.
********************************************************************************/
void serial_print_string(const char* s)
{
	for (uint16_t i = 0; s[i]; ++i)
	{
		serial_print_char(s[i]);

		if (s[i] == '\n')
		{
			serial_print_char('\r');
		}
	}
	return;
}

/********************************************************************************
* serial_print_integer: Skriver angivet signerat heltal till ansluten seriell

*                       - number: Talet som ska skrivas.
********************************************************************************/
void serial_print_integer(const int32_t number)
{
	char s[20] = { '\0' };
	sprintf(s, "%ld", number);
	serial_print_string(s);
	return;
}

/********************************************************************************
* serial_print_unsigned: Skriver angivet osignerat heltal till ansluten seriell
*                        terminal. I praktiken omvandlas heltalet till text
*                        via funktionen sprintf från stdio.h och skickas.
*
********************************************************************************/
void serial_print_unsigned(const uint32_t number)
{
	char s[20] = { '\0' };
	sprintf(s, "%lu", number);
	serial_print_string(s);
	return;
}

/********************************************************************************
* serial_print_double: Skriver angivet flyttal till ansluten seriell terminal.
*

********************************************************************************/
void serial_print_double(const double number)
{
	char s[20] = { '\0' };
	const int32_t integer = (int32_t)number;
	int32_t decimal;

	if (integer >= 0)
	{
		decimal = (int32_t)((number - integer) * 100 + 0.5);
	}
	else
	{
		decimal = (int32_t)((integer - number) * 100 + 0.5);
	}

	sprintf(s, "%ld.%ld", integer, decimal);
	serial_print_string(s);
	return;
}