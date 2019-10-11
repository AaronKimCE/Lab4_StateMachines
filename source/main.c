/*	Author: akim106
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Door_States{Locked, Press_1, Release_1, Press_2, Unlocked} Door_State; //Enumerating States

unsigned char A0; //Button 1 X
unsigned char A1; //Button 2 Y
unsigned char A2; //Button 3 #
unsigned char A7; //Button 4 Lock

void TickFct_Door() {
    A0 = PINA & 0x01;
    A1 = PINA & 0x02;
    A2 = PINA & 0x04;
    A7 = PINA & 0x80;

    switch(Door_State) { //State transitions
      case Locked:
        if (!A0 && !A1 && A2) {
          Door_State = Press_1;
        } else {
          Door_State = Locked;
        }
        break;
      case Press_1: //First Correct input
        if (!A0 && !A1 && A2) {
          Door_State = Press_1;
        } else if (!(A0 || A1 || A2)) {
          Door_State = Release_1;
        } else {
          Door_State = Locked;
        }
        break;
      case Release_1: //Waiting on button to be released without other input
        if (!A0 && !A1 && !A2) {
          Door_State = Release_1;
        } else if (!A0 && A1 && !A2) {
          Door_State = Press_2;
        } else {
          Door_State = Locked;
        }
        break;
      case Press_2://Second Correct input and releasing without wrong input
        if (!A0 && A1 && !A2) {
          Door_State = Press_2;
        } else if (!(A0 || A1 || A2)) {
          Door_State = Unlocked;
        } else {
          Door_State = Locked;
        }
        break;
      case Unlocked: //Lock button locks door again
        if (A7) {
          Door_State = Locked;
        } else {
          Door_State = Unlocked;
        }
        break;     
      
      default:
        Door_State = Locked;
        break;
    }

    switch(Door_State) { //State actions
      case Locked:
        PORTB = 0x00; //Door locked
        break;
      case Press_1:
        break;
      case Release_1:
        break;
      case Press_2:
        break;
      case Unlocked:
        PORTB = 0x01; //Door unlocked
        break;   
    }
}

int main(void) {
    DDRA = 0x00; PORTA = 0x00; //PORT A = inputs
    DDRB = 0xFF; PORTB = 0x00; //PORT B = outputs
    Door_State = Locked; //Setting initial state

    while (1) {
      TickFct_Door(); //Repeating state logic 
    }
    return 1;
}
