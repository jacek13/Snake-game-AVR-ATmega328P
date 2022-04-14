/*
 * boardIO.h
 *
 * Created: 14.04.2022 20:01:20
 *  Author: Micha³ Jackowski
 */ 

#ifndef BOARDIO_H_
#define BOARDIO_H_

#include "structures.h"

#define PIN_BUZZER			(1 << PD7)
#define PIN_SWITCH_LEFT		(1 << PD5)
#define PIN_SWITCH_RIGHT	(1 << PD4)
#define PIN_SWITCH_UP		(1 << PD3)
#define PIN_SWITCH_DOWN		(1 << PD6)
#define PIN_GAME_RESET		(1 << PD2)
#define PIN_DATA_IN_DISPLAY (1 << PB0)

#define BUZZER_ON PORTD	 |= PIN_BUZZER
#define BUZZER_OFF PORTD &= ~PIN_BUZZER
#define BUZZER_TOG PORTD ^= PIN_BUZZER

void initRegisters();

GAME_LOGIC read_from_inputs(GAME_LOGIC previous_direction);

void generate_sound(int8_t _scored, int8_t _game_over);

#endif /* BOARDIO_H_ */