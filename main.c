//------------------------------------------------------------------------------------
// Base_8051
//------------------------------------------------------------------------------------
//
// AUTH: DF
// DATE: 18-09-2017
// Target: C8051F020
//
// Tool chain: KEIL UV4
//
// Application de base qui configure seulement l'oscillateur et le watchdog
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "c8051f020.h" // SFR declarations
#include <intrins.h>  
#include <stdio.h>
#include "init.h"

void fct_tempo(int duree_us);


sbit LED = P1^6; // Led verte embarquée sur la carte



//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main (void)
{
	
  Init_Device();
  
  while (1)
  {
			LED = 1;
			SBUF0 = 'a';
			fct_tempo(32000);
			fct_tempo(32000);
			fct_tempo(32000);
			fct_tempo(32000);
		  LED = 0;
			fct_tempo(32000);
			fct_tempo(32000);
			fct_tempo(32000);
			fct_tempo(32000);
	}	 	 
}

 

 