/*
 * main.c
 *
 * Created: 13.04.2022 19:04:11
 * Author : Micha³ Jackowski
 * Board info:
 *
 * RGB matrix 8x8 WS2811
 * Pin PB0 to DataIn
 * Pin 5V to VCC
 * PIN GND to GND
 *
 * rest I/O
 * Pin PD3 microswitch	-> input UP button		(internal pull-up resistor)
 * Pin PD6 microswitch	-> input DOWN button	(internal pull-up resistor)
 * Pin PD5 microswitch	-> input LEFT button	(internal pull-up resistor)
 * Pin PD4 microswitch	-> input RIGHT button	(internal pull-up resistor)
 * Pin PD2 microswitch	-> input RESET button	(internal pull-up resistor)
 * Pin PD7 buzzer -> digital output
 */ 

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#include "ws2812_config.h"
#include "light_ws2812.h"
#include "structures.h"
#include "data.h"
#include "display.h"
#include "gameLogic.h"
#include "boardIO.h"

void inline clear_screen()
{
	for(int8_t i = 0; i < NUM_OF_LEDS; i++)
		leds[i].r = leds[i].g = leds[i].b = 0;
	_delay_ms(10);
	ws2812_sendarray((uint8_t*)leds, NUM_OF_LEDS * 3);
}

main(void)
{
	initRegisters();

	while(TRUE)
	{
		int8_t menu_loop = TRUE;
		int8_t game_loop = TRUE;
		int8_t stop = FALSE;
		int8_t opposite_key = FALSE;
		int8_t x, y, x_previous, y_previous, collision_state, score;
		int16_t speed;

		struct snake_element * head = NULL;
		struct snake_element * tail = NULL;

		GAME_LOGIC previous_direction;
		GAME_LOGIC direction_copy;
		GAME_LOGIC opposite_direction;

		struct food snake_food;

		while(menu_loop)
		{
			score = 1;
			speed = 75;
			game_loop = TRUE;
			stop = FALSE;
			previous_direction = DIRECTION_UP;
			direction_copy = previous_direction;
			opposite_direction = DIRECTION_DOWN;

			x = 8;  // board border in X axis
			y = 8;  // board border in Y axis

			snake_add_to_the_beginning(&head,&tail, x / 2, y / 2);
			generate_food(x, y, &snake_food);
			draw_scene(head, snake_food, x, y);
			 
			while(game_loop)
			{
				direction_copy = previous_direction;
				previous_direction = read_from_inputs(previous_direction);

				head_buffer(tail, &x_previous, &y_previous);
				snake_update(&tail);
				controller(	&previous_direction, &opposite_direction, direction_copy, &head, &game_loop, &menu_loop, &stop,
							&opposite_key,&speed);

				if(opposite_key)
				{
					opposite_key = FALSE;
					controller( &previous_direction, &opposite_direction, direction_copy, &head, &game_loop, &menu_loop, &stop,
								&opposite_key, &speed);
				}
				 
				collision_state = check_collision(head, snake_food, x, y);
				draw_scene(head, snake_food, x, y);
				
				if(collision_state == 2)
				{
					generate_food(x, y, &snake_food);
					snake_add_at_the_end(&tail, x_previous, y_previous);
					score_update(&score);
					generate_sound(TRUE, FALSE);
				}
				else if(collision_state == 3)
				{
					game_loop = FALSE;
					snake_delete(&head);
				}
				handle_break_time(speed);
			}
			
			if(game_loop || menu_loop)
			{
				generate_sound(FALSE,TRUE);
				draw_score(score);
			}

			if(head)
				snake_delete(&head);
		}
	}
}