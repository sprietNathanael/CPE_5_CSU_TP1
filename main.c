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
#include <stdlib.h>
#include "init.h"

sbit LED = P1^6; // Led verte embarquée sur la carte
sbit TEMP = P1^7; // temp sensor
sbit DEBUG = P1^5; // debug

char res[5] = {0};

void fct_tempo(int duree_us);

void wait(int duree_ms)
{
	int i = 0;
	for(i; i < duree_ms; i++)
	{
		fct_tempo(1000);
	}
}

void rthConfig()
{
	
	P1MDOUT &= ~0x80;
}
	

void rthInit()
{
	DEBUG = 1;
	LED = 1;
	TEMP = 0;
	wait(10);
	TEMP = 1;
	
	fct_tempo(20);

	while(TEMP != 0)
	{
	}
	
	while(TEMP != 1)
	{
	}
	
	while(TEMP != 0)
	{
	}
}

void rthRead()
{
	int i = 0;
	int y = 0;
	char readValue = 0;
	for(i; i < 5; i ++)
	{
		for(y=0; y < 8; y++)
		{
			readValue = TEMP;
			while(TEMP != 1)
			{
			}
			fct_tempo(50);
			readValue = TEMP;
			res[i] = res[i] << 1;
			res[i] += readValue;
			while(TEMP != 0)
			{
			}
		}
		
	}
	
	DEBUG = 0;
	LED = 0;
}

// inline function to swap two numbers
void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// Iterative function to implement itoa() function in C
char* itoa(int value, char* buffer)
{
	// consider absolute value of number
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % 10;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / 10;
	}

	// if number is 0
	if (i == 0)
		buffer[i++] = '0';

	// If base is 10 and value is negative, the resulting string 
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < 0)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buffer, 0, i - 1);
}

void write_c(char c)
{
	while(TI0 != 1);
	TI0 = 0;
	SBUF0 = c;		
}

void write_s(char* s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		write_c(s[i]);
		i++;
	}
}

void emptyBuff(char* buff,int size)
{
	int i = 0;
	while(i < size)
	{
		buff[i] = '\0';
		i++;
	}
}

void sendValue(int value)
{
	char toSend[10];
	emptyBuff(toSend,10);
	itoa(value, toSend);
	write_s(toSend);
}

void sendRes()
{
	write_s("T:");
	sendValue(res[0]);
	write_s(" H:");
	sendValue(res[2]);
	write_s("\n");	
}

//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void main (void)
{
	P1MDOUT |= 0x60;
  Init_Device();
	rthConfig();
	DEBUG = 0;
	LED = 0;
	
  while (1)
  {
			emptyBuff(res,5);
			rthInit();
			rthRead();
			sendRes();
			wait(1000);
			//LED = 1;
			//SBUF0 = 'a';
			//wait(1000);
		  //LED = 0;
			//wait(500);
	}	 	 
}

 

 