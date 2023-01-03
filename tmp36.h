/********************************************************************************
* tmp36.h: Innehåller drivrutiner för temperatursensor TMP36, som används för
*          mätning samt utskrift av rumstemperaturen. Den analoga insignalen
*          från TMP36 AD-omvandlas till en digital motsvarighet, som används
*          för att beräkna aktuell temperatur. Utskrift sker till en seriell
*          terminal via USART.
********************************************************************************/
#ifndef TMP36_H_
#define TMP36_H_

#include "adc.h"
#include "serial.h"

/********************************************************************************
* tmp36: Strukt för implementering av temperatursensor TMP36, som används för
*        mätning samt utskrift av rumstemperaturen. Vid avläsning AD-omvandlas
*        den analoga insignalen till en digital motsvarighet. Utefter detta
*        värde beräknas den analoga inspänningen Uin via nedanstående formel:
*
*      
********************************************************************************/
struct tmp36
{
	struct adc input; /* AD-omvandlare, omvandlar analog insignal från TMP36. */
};

/********************************************************************************
* tmp36_init: Initierar pin ansluten till temperatursensor TMP36 för mätning
*             samt utskrift av rumstemperaturen. Seriell överföring initieras
*             också med en baud rate (överföringshastighet) på 9600 kbps.
*
********************************************************************************/
static inline void tmp36_init(struct tmp36* self,
const uint8_t pin)
{
	adc_init(&self->input, pin);
	serial_init(9600);
	return;
}

/********************************************************************************
* tmp36_get_temperature: Returnerar aktuell rumstemperatur via avläsning av
*                        angiven temperatursensor TMP36.
*
********************************************************************************/
static inline double tmp36_get_temperature(const struct tmp36* self)
{
	const double voltage = adc_read(&self->input) / 1023.0 * 5;
	return 100 * voltage - 50;
}

/********************************************************************************
* tmp36_print_temperature: Skriver ut aktuell rumstemperatur avläst av
*                          temperatursensor TMP36.
*
********************************************************************************/
static inline void tmp36_print_temperature(const struct tmp36* self)
{
	serial_print_string("Temperature: ");
	serial_print_double(tmp36_get_temperature(self));
	serial_print_string(" degrees Celcius!\n");
	return;
}

#endif /* TMP36_H_ */