/*	Author: akim106
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define button PINA & 0x01
#define LED PORTB

enum LED_States { LED_1, Held_1, LED_2, Held_2 } LED_State;

void TickFct_LED() {
    switch(LED_State) {
      case LED_1:
        if (!button) {
          LED_State = LED_1;
          break;
        } else if (button) {
          LED_State = Held_1;
          break;
        } else {
          LED_State = LED_1;
          break;
        }
      
      case Held_1:
        if (!button) {
          LED_State = LED_2;
          break;
        } else if (button) {
          LED_State = Held_1;
          break;
        } else {
          LED_State = Held_1;
          break;
        }

      case LED_2:
        if (!button) {
          LED_State = LED_2;
          break;
        } else if (button) {
          LED_State = Held_2;
          break;
        } else {
          LED_State = LED_2;
          break;
        }

      case Held_2:
        if (!button) {
          LED_State = LED_1;
          break;
        } else if (button) {
          LED_State = Held_2;
          break;
        } else {
          LED_State = Held_2;
          break;
        }

      default:
        LED_State = LED_1;
        break;
    }

    switch (LED_State) {
      case LED_1:
        LED = (LED & 0x00) | 0x01;
        break;

      case Held_1:
        LED = (LED & 0x00) | 0x01;
        break;

      case LED_2:
        LED = (LED & 0x00) | 0x02;
        break;

      case Held_2:
        LED = (LED & 0x00) | 0x02;
        break;
      
      default:
        break; 
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00; //PORT A = inputs
    DDRB = 0xFF; PORTB = 0x00; //PORT C = outputs
    LED_State = LED_1;

    while (1) {
      TickFct_LED();      
    }
    return 1;
}
