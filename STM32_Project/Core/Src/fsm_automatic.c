/*
 * fsm_automatic.c
 *
 *  Created on: 21 thg 10, 2023
 *      Author: nvtie
 */
#include "fsm_automatic.h"

int sec1 = 0;
int sec2 = 0;
int index_led = 0;

void updateLEDtime(){

}

void fsm_automatic_run(){
	switch(status){
	case INIT:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		status = AUTO_RED;
		setTimer(red*1000, 0);
		setTimer(green*1000, 1);
		setTimer(1000, 2);
		setTimer(250, 3);
		sec1 = red;
		sec2 = green;
		updateClockBuffer(sec1, sec2);
		break;
	case AUTO_RED:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(timer_flag[1] == 1){
			status = AUTO_GREEN_YELLOW;
			sec2 = yellow;
			setTimer(yellow*1000, 1);
		}
		if(isButton1Pressed(0) == 1){
			status = MAN_RED;
			setTimer(250, 4);
		}
		break;
	case AUTO_GREEN_YELLOW:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);

		if(timer_flag[0] == 1){
			status = AUTO_GREEN;
			setTimer(green*1000, 0);
			sec1 = green;
			sec2 = red;
		}
		break;
	case AUTO_GREEN:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(timer_flag[0] == 1){
			status = AUTO_YELLOW;
			setTimer(yellow*1000, 0);
			sec1 = yellow;
		}
		break;
	case AUTO_YELLOW:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(timer_flag[0] == 1){
			status = AUTO_RED;
			setTimer(red*1000, 0);
			setTimer(green*1000, 1);
			sec1 = red;
			sec2 = green;
		}
		break;
	default:
		break;
	}
	if((status >= INIT) && (status <=AUTO_YELLOW)){
		if(timer_flag[2] == 1){
			updateClockBuffer(sec1, sec2);
			if(sec1 > 0) sec1--;
			if(sec2 > 0) sec2--;
			setTimer(1000, 2);
		}
	}
	if(timer_flag[3] == 1){
		update7SEG(index_led);
		index_led++;
		if(index_led >= MAX_LED) index_led = 0;
		setTimer(250, 3);
	}
}

