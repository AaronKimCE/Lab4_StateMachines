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

enum LED_States { LED_1, Held_1, LED_2, Held_2 } LED_State; //Enumerating States

void TickFct_LED() { //Transitions between states
    switch(LED_State) {
      case LED_1: //LED1 is on
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
      
      case Held_1: //First button press
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
        if (!button) { //LED 2 is on
          LED_State = LED_2;
          break;
        } else if (button) {
          LED_State = Held_2;
          break;
        } else {
          LED_State = LED_2;
          break;
        }

      case Held_2: //Button press again
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

    switch (LED_State) { //State actions
      case LED_1: //LED 1 is on initially
        LED = (LED & 0x00) | 0x01;
        break;

      case Held_1: //Button is not released yet
        LED = (LED & 0x00) | 0x01;
        break;

      case LED_2: //LED 2 is on after button release
        LED = (LED & 0x00) | 0x02;
        break;

      case Held_2: //Button is not released
        LED = (LED & 0x00) | 0x02;
        break;
      
      default:
        break; 
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00; //PORT A = inputs
    DDRB = 0xFF; PORTB = 0x00; //PORT C = outputs
    LED_State = LED_1; //Setting initial state

    while (1) {
      TickFct_LED(); //Repeating state logic      
    }
    return 1;
}
