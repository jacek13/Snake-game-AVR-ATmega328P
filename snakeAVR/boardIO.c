/*
 * boardIO.c
 *
 * Created: 14.04.2022 20:01:04
 *  Author: Micha³ Jackowski
 */ 

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#include "boardIO.h"
#include "structures.h"

void initRegisters()
{
	DDRD |= PIN_BUZZER;
	DDRD &= ~PIN_SWITCH_UP;
	PORTD |= PIN_SWITCH_UP;
	DDRD &= ~PIN_SWITCH_DOWN;
	PORTD |= PIN_SWITCH_DOWN;
	DDRD &= ~PIN_SWITCH_LEFT;
	PORTD |= PIN_SWITCH_LEFT;
	DDRD &= ~PIN_SWITCH_RIGHT;
	PORTD |= PIN_SWITCH_RIGHT;
	DDRD &= ~PIN_GAME_RESET;
	PORTD |= PIN_GAME_RESET;
}

int8_t read_key(int8_t _key)
{
	if(!(_key & PIND))
	{
		_delay_ms(20); // drgania na stykach
		if(!(_key & PIND))
			return 0;
	}
	return 1;
}

GAME_LOGIC read_from_inputs(GAME_LOGIC previous_direction)
{
	int8_t reset = read_key(PIN_GAME_RESET);
	int8_t up	 = read_key(PIN_SWITCH_UP);
	int8_t down	 = read_key(PIN_SWITCH_DOWN);
	int8_t left	 = read_key(PIN_SWITCH_LEFT);
	int8_t right = read_key(PIN_SWITCH_RIGHT);

	if(!reset && !up)
		return EVENT_SPEED_INCREASE;

	if(!reset && !down)
		return EVENT_SPEED_REDUCE;
	
	if(!reset)
		return EVENT_EXIT;
	
	if(!right)
		return DIRECTION_RIGHT;
	
	if(!left)
		return DIRECTION_LEFT;

	if(!down)
		return DIRECTION_DOWN;

	if(!up)
		return DIRECTION_UP;
	
	return previous_direction;
}

void generate_sound(int8_t _scored, int8_t _game_over)
{
	if(_scored)
	{
		BUZZER_ON;
		_delay_ms(50);
		BUZZER_OFF;
	}
	
	if(_game_over)
	{
		BUZZER_ON;
		_delay_ms(500);
		BUZZER_OFF;
	}
}