#ifndef HEADER_H_
#define HEADER_H_

/* Inkluderingsdirektiv: */

#include "button.h"
#include "timer.h"
#include "tmp36.h"

/* Deklaration av globala objekt: */

extern struct button b1;    /* Tryckknappar. */
extern struct timer t0, t1; /* Timerkretsar. */
extern struct tmp36 temp1;  /*Temperatursensor. */

/********************************************************************************
* setup: Initierar systemet.
********************************************************************************/
void setup(void);

#endif /* HEADER_H_ */