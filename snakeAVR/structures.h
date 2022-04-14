/*
 * structures.h
 *
 * Created: 14.04.2022 19:26:02
 *  Author: Micha³ Jackowski
 */ 

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define TRUE 1
#define FALSE 0

#define DELAY 1000

/** Snake structure (bidirectional list) */
typedef struct snake_element
{
	int8_t x;
	int8_t y;
	struct snake_element * previous_element;
	struct snake_element * next_element;
}_snake_element;

/** Food for the snake, snake likes to eat 2 bytes :D */
struct food
{
	int8_t x;
	int8_t y;
};

/** enumeration for program logic/events */
typedef enum
{
	DIRECTION_UP = 1,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	EVENT_EXIT,
	EVENT_PAUSE,
	EVENT_SPEED_INCREASE,
	EVENT_SPEED_REDUCE
} GAME_LOGIC;

#endif /* STRUCTURES_H_ */