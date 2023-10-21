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

}

void fsm_manual_run(){
	switch(status){
	case MAN_RED:
		updateClockBuffer(2, redMod);
		if(timer_flag[4] == 1){
			setTimer(250, 4);
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
		}
		if(isButton1Pressed(0) == 1){
			status = MAN_YELLOW;
			setTimer(250, 4);
		}
		if(isButton1Pressed(1) == 1){
			redMod++;
			if(redMod > 99) redMod = 1;
		}
		if(isButton1Pressed(2) == 1){
			red = redMod;
		}
		break;
	case MAN_YELLOW:
		updateClockBuffer(3, yellowMod);
		if(timer_flag[4] == 1){
			setTimer(250, 4);
			HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
			HAL_GPIO_TogglePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin);
		}
		if(isButton1Pressed(0) == 1){
			status = MAN_GREEN;
			setTimer(250, 4);
		}
		if(isButton1Pressed(1) == 1){
			yellowMod++;
			if(yellowMod > 99) yellowMod = 1;
		}
		if(isButton1Pressed(2) == 1){
			yellow = yellowMod;
		}
		break;
	case MAN_GREEN:
		updateClockBuffer(4, greenMod);
		if(timer_flag[4] == 1){
			setTimer(250, 4);
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
			HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
		}
		if(isButton1Pressed(0) == 1){
			ledBalance();
			status = INIT;
		}
		if(isButton1Pressed(1) == 1){
			greenMod++;
			if(greenMod > 99) greenMod = 1;
		}
		if(isButton1Pressed(2) == 1){
			green = greenMod;
		}
		break;
	default:
		break;
	}
}
