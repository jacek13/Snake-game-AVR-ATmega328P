/*
 * gameLogic.h
 *
 * Created: 14.04.2022 19:53:50
 *  Author: Micha³ Jackowski
 */ 

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "structures.h"

void head_buffer(struct snake_element * pTail, int8_t * X_previous, int8_t * Y_previous);

void snake_add_to_the_beginning(struct snake_element ** pHead, struct snake_element ** pTail, int8_t X, int8_t Y);

void snake_delete(struct snake_element ** pHead);

void snake_add_at_the_end(struct snake_element ** pTail, int8_t X, int8_t Y);

void snake_update(struct snake_element ** pTail);

void generate_food(int8_t board_max_x, int8_t board_max_y,struct food * _food);

int8_t check_collision(struct snake_element* pHead, struct food _food, int8_t board_max_x, int8_t board_max_y);

void score_update(int8_t * counter);

int16_t change_speed(int16_t current_speed, int8_t increase);

void controller(GAME_LOGIC * direction, GAME_LOGIC * opposite_direction, GAME_LOGIC previous_direction, 
				struct snake_element ** pHead, int8_t * game_loop, int8_t * menu_loop, int8_t * pause, 
				int8_t * key_control, int8_t * speed);

void handle_break_time(int16_t _speed);

#endif /* GAMELOGIC_H_ */