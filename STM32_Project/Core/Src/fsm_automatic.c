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


void fsm_automatic_run(){
	switch(status){
	case INIT:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		status = RED1_GREEN2;
		setTimer(1000, 0);
		setTimer(250, 1);
		sec1 = red;
		sec2 = green;
		break;
	case RED1_GREEN2:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(sec2 <= 0){
			status = RED1_YELLOW2;
			sec2 = yellow;
		}
		if(isButton1Pressed(0) == 1){
			status = MAN_RED;
			setTimer(250, 2);
		}
		break;
	case RED1_YELLOW2:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, RESET);

		if(sec2 <= 0){
			status = GREEN1_RED2;
			sec1 = green;
			sec2 = red;
		}
		break;
	case GREEN1_RED2:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, SET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(sec1 <= 0){
			status = YELLOW1_RED2;
			sec1 = yellow;
		}
		break;
	case YELLOW1_RED2:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, RESET);

		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, SET);

		if(sec1 <= 0){
			status = RED1_GREEN2;
			sec1 = red;
			sec2 = green;
		}
		break;
	default:
		break;
	}

	if((status >= INIT) && (status <=YELLOW1_RED2)){
		updateClockBuffer(sec1, sec2);
		if(timer_flag[0] == 1){
			setTimer(1000, 0);
			if(sec1 > 0) sec1--;
			if(sec2 > 0) sec2--;
		}
	}

	if(timer_flag[1] == 1){
		setTimer(250, 1);
		update7SEG(index_led);
		index_led++;
		if(index_led >= MAX_LED) index_led = 0;
	}
}

