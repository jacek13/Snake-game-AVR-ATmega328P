/*
 * gameLogic.c
 *
 * Created: 14.04.2022 19:54:12
 *  Author: Micha³ Jackowski
 */ 

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#include "gameLogic.h"

void head_buffer(struct snake_element * pTail, int8_t * X_previous, int8_t * Y_previous)
{
	*X_previous = pTail->x;
	*Y_previous = pTail->y;
}

void snake_add_to_the_beginning(struct snake_element ** pHead, struct snake_element ** pTail, int8_t X, int8_t Y)
{
	if(!*pHead)
	{
		*pTail = *pHead = (struct snake_element *) calloc(1, sizeof(struct snake_element));
		(*pHead)->x = X;
		(*pHead)->y = Y;
		(*pHead)->next_element = (*pHead)->previous_element = NULL;
	}
	else
	{
		struct snake_element * pNew = (struct snake_element *) calloc(1, sizeof(struct snake_element));
		pNew->previous_element = NULL;
		pNew->next_element = *pHead;
		pNew->next_element->previous_element = pNew;
		*pHead = pNew;
	}
}

void snake_delete(struct snake_element ** pHead)
{
	while(*pHead)
	{
		struct snake_element * pNew = *pHead;
		pNew = pNew->next_element;
		free(*pHead);
		*pHead = pNew;
	}
}

void snake_add_at_the_end(struct snake_element ** pTail, int8_t X, int8_t Y)
{
	struct snake_element * pNew = (struct snake_element *) calloc(1, sizeof(struct snake_element));
	pNew->next_element = NULL;
	pNew->previous_element = *pTail;
	pNew->x = X;
	pNew->y = Y;
	(*pTail)->next_element = pNew;
	*pTail = pNew;
}

void snake_update(struct snake_element ** pTail)
{
	struct snake_element * pNew = *pTail;
	struct snake_element * successor_from_back = *pTail;
	successor_from_back = successor_from_back->previous_element;
	while(successor_from_back)
	{
		pNew->x = successor_from_back->x;
		pNew->y = successor_from_back->y;
		pNew = pNew->previous_element;
		successor_from_back = successor_from_back->previous_element;
	}
}

void generate_food(int8_t board_max_x, int8_t board_max_y,struct food * _food)
{
	_food->x = random() % board_max_x;
	_food->y = random() % board_max_y;
}

int8_t check_collision(struct snake_element* pHead, struct food _food, int8_t board_max_x, int8_t board_max_y)
{
	if(pHead->x == _food.x && pHead->y == _food.y)
		return 2; // dodaj element do weza
	else
	{
		struct snake_element * pNew = pHead;
		pNew = pNew->next_element;

		while(pNew)
		{
			if(pHead->x == pNew->x && pHead->y == pNew->y)
				return 3; // koniec gry waz wjechal w samego siebie
			pNew = pNew->next_element;
		}
		return 0;
	}
}

void score_update(int8_t * counter)
{
	(*counter)++;
}

int16_t change_speed(int16_t current_speed, int8_t increase)
{
	int16_t r = current_speed;
	if(current_speed >= 100 && current_speed <= 650)
	{
		if(increase)
			r -= 25;
		else
			r += 25;
	}
	else
		r = 75;
	return r;
}

void controller(GAME_LOGIC * direction, GAME_LOGIC * opposite_direction, GAME_LOGIC previous_direction, struct snake_element ** pHead, int8_t * game_loop, int8_t * menu_loop, int8_t * pause, int8_t * key_control, int8_t * speed)
{
	if(*direction == *opposite_direction)
	{
		*direction = previous_direction;
		*key_control = TRUE;
	}
	else if(*direction == DIRECTION_UP)
	{
		(*pHead)->y--;
		*opposite_direction = DIRECTION_DOWN;
		if((*pHead)->y == -1)
			(*pHead)->y = 7;
	}
	else if(*direction == DIRECTION_DOWN)
	{
		(*pHead)->y++;
		*opposite_direction = DIRECTION_UP;
		if((*pHead)->y == 8)
			(*pHead)->y = 0;
	}
	else if(*direction == DIRECTION_LEFT)
	{
		(*pHead)->x--;
		*opposite_direction = DIRECTION_RIGHT;
		if((*pHead)->x == -1)
			(*pHead)->x = 7;
	}
	else if(*direction == DIRECTION_RIGHT)
	{
		(*pHead)->x++;
		*opposite_direction = DIRECTION_LEFT;
		if((*pHead)->x == 8)
			(*pHead)->x = 0;
	}
	else if(*direction == EVENT_EXIT)
	{
		*game_loop = FALSE;
		*menu_loop = FALSE;
	}
	else if(*direction == EVENT_SPEED_INCREASE)
	{
		*direction = previous_direction;
		*key_control = TRUE;
		*speed = change_speed(*speed,TRUE);
	}
	else if(*direction == EVENT_SPEED_REDUCE)
	{
		*direction = previous_direction;
		*key_control = TRUE;
		*speed = change_speed(*speed,FALSE);
	}
}

void handle_break_time(int16_t _speed)
{
	while(_speed > 0)
	{
		_speed -= 25;
		_delay_ms(25);
	}
}