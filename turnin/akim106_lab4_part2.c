/*	Author: akim106
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Cnt_States{Wait, Press_1, Increment, Press_2, Decrement, Reset} Cnt_State; //Enumerating States

unsigned char B1; //Button 1 PA0
unsigned char B2; //Button 2 PA1
unsigned char Output; //Saved value to update to PORTC

void TickFct_Cnt() {
    B1 = PINA & 0x01; //Getting input from PINA
    B2 = PINA & 0x02;

    switch(Cnt_State) { //State transitions
      case Wait: //Initial State: wait for input
        if (B1 && !B2) {
          Cnt_State = Press_1;
        } else if (!B1 && B2) {
          Cnt_State = Press_2;
        } else if (B1 && B2) {
          Cnt_State = Reset;
        } else {
          Cnt_State = Wait;
        }
        break;
      case Press_1: //B1 is held
        if (B1 && !B2) {
          Cnt_State = Press_1;
        } else if (B1 && B2) {
          Cnt_State = Reset;
        } else if (!B1 && !B2) {
          Cnt_State = Increment;
        } else {
          Cnt_State = Wait;
        }
        break;
      case Increment: //B1 is released
        Cnt_State = Wait;
        break;
      case Press_2: //B2 is held
        if (!B1 && B2) {
          Cnt_State = Press_2;
        } else if (B1 && B2) {
          Cnt_State = Reset;
        } else if (!B1 && !B2) {
          Cnt_State = Decrement;
        } else {
          Cnt_State = Wait;
        }
        break;
      case Decrement: //B2 is released
        Cnt_State = Wait;
        break;
      case Reset: //B1 & B2 is held
        if (B1 && B2) {
          Cnt_State = Reset;
        } else {
          Cnt_State = Wait;
        }

    }

    switch(Cnt_State) { //State actions
      case Wait:
        break;
      case Press_1:
        break;
      case Increment: //One B1 press increments by 1
        if (Output < 9) {
          ++Output;
        }
        break;
      case Press_2:
        break;
      case Decrement: //One B2 press decrements by 1
        if (Output > 0) {
          --Output;
        }
        break;
      case Reset: //Pressing B1 & B2 resets output to 0
        Output = 0x00;
        break; 
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00; //PORT A = inputs
    DDRC = 0xFF; PORTC = 0x00; //PORT C = outputs
    Cnt_State = Wait; //Setting initial state
    Output = 7;

    while (1) {
      TickFct_Cnt(); //Repeating state logic 
      PORTC = Output;//Updating PORTC output
    }
    return 1;
}
