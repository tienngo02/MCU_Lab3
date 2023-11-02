/*
 * fsm_manual.c
 *
 *  Created on: Oct 21, 2023
 *      Author: nvtie
 */

#include "fsm_manual.h"

int redMod = 1;
int yellowMod = 1;
int greenMod = 1;

void ledBalance(){
	if(red == (green + yellow)) return;
	else if(red < (green + yellow)){
		red = green + yellow;
	}
	else{
		green = red - yellow;
	}
}

void fsm_manual_run(){
	switch(status){
	case MAN_RED:
		updateClockBuffer(2, redMod);
		if(timer_flag[2] == 1){
			setTimer(250, 2);
			toggleLedRED();
		}
		if(isButtonPressed(0) == 1){
			status = MAN_YELLOW;
			setTimer(250, 2);
			clearAllLED();
		}
		if(isButtonPressed(1) == 1){
			redMod++;
			if(redMod > 99) redMod = 1;
		}
		if(isButtonPressed(2) == 1){
			red = redMod;
		}
		break;
	case MAN_YELLOW:
		updateClockBuffer(3, yellowMod);
		if(timer_flag[2] == 1){
			setTimer(250, 2);
			toggleLedYELLOW();
		}
		if(isButtonPressed(0) == 1){
			status = MAN_GREEN;
			setTimer(250, 2);
			clearAllLED();
		}
		if(isButtonPressed(1) == 1){
			yellowMod++;
			if(yellowMod > 99) yellowMod = 1;
		}
		if(isButtonPressed(2) == 1){
			yellow = yellowMod;
		}
		break;
	case MAN_GREEN:
		updateClockBuffer(4, greenMod);
		if(timer_flag[2] == 1){
			setTimer(250, 2);
			toggleLedGREEN();
		}
		if(isButtonPressed(0) == 1){
			ledBalance();
			status = INIT;
		}
		if(isButtonPressed(1) == 1){
			greenMod++;
			if(greenMod > 99) greenMod = 1;
		}
		if(isButtonPressed(2) == 1){
			green = greenMod;
		}
		break;
	default:
		break;
	}
}
