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
#define B1 (PINA & 0x01)
#define B2 (PINA & 0x02)
#define Output PORTC

enum Cnt_States { Wait, B1_Held, B2_Held, Increment, Decrement, Reset } Cnt_State; //Enumerating States

void TickFct_Cnt() { //Transitions between states
    switch(Cnt_State) {
      case Wait: //LED1 is on
        if ((B1 == 0x01) && (B2 == 0x00)) {
          Cnt_State = B1_Held;
          break;
        } else if ((B1 == 0x00) && (B2 == 0x02)) {
          Cnt_State = B2_Held;
          break;
        } else if ((B1 == 0x01) && (B2 == 0x02)) {
          Cnt_State = Reset;
          break;
        } else {
          Cnt_State = Wait;
          break;
        }

      case B1_Held: 
        if ((B1 == 0x01) && (B2 == 0x00)) {
          Cnt_State = B1_Held;
          break;
        } else if ((B1 == 0x01) && (B2 == 0x02)) {
          Cnt_State = Reset;
          break;
        } else {
          Cnt_State = Increment;
          break;
        }

      case B2_Held:
        if ((B1 == 0x00) && (B2 == 0x02)) {
          Cnt_State = B2_Held;
          break;
        } else if ((B1 == 0x01) && (B2 == 0x02)) {
          Cnt_State = Reset;
          break;
        } else {
          Cnt_State = Decrement;
          break;
        }

      case Increment:
        Cnt_State = Wait;
        break;

      case Decrement:
        Cnt_State = Wait;
        break;

      case Reset:
        if (B1 && B2) {
          Cnt_State = Reset;
          break;
        } else {
          Cnt_State = Wait;
          break;
        }

       
      default:
        Cnt_State = Wait;
        break;
    }

    switch (Cnt_State) { //State actions
      case Wait: //Do nothing on wait
        Output = Output;
        break;

      case B1_Held: //Button is not released yet
        Output = Output;
        break;

      case B2_Held: //LED 2 is on after button release
        Output = Output;
        break;

      case Increment: //Button is not released
        if (Output < 9) {
          Output = ++Output;
        }
        break;
      
      case Decrement: //Button is not released
        Output = --Output;
        break;

      case Reset: //Button is not released
        Output = Output & 0x00;
        break;

      default:
        break; 
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00; //PORT A = inputs
    DDRC = 0xFF; PORTC = 0x07; //PORT C = outputs
    Cnt_State = Wait; //Setting initial state

    while (1) {
      TickFct_Cnt(); //Repeating state logic      
    }
    return 1;
}
