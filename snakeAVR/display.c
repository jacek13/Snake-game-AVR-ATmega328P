/*
 * display.c
 *
 * Created: 14.04.2022 19:37:36
 *  Author: Micha³ Jackowski
 */ 

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdlib.h>
#include "display.h"
#include "structures.h"
#include "data.h"

struct cRGB leds[NUM_OF_LEDS];

inline uint16_t XY(int8_t x, int8_t y)
{
	return (y * 8) + x;
}

void inline clear_screen()
{
	for(int8_t i = 0; i < NUM_OF_LEDS; i++)
		leds[i].r = leds[i].g = leds[i].b = 0;
	_delay_ms(10);
	ws2812_sendarray((uint8_t*)leds, NUM_OF_LEDS * 3);
}

void draw_scene(struct snake_element * pHead, struct food _food, int8_t board_max_x, int8_t board_max_y)
{
	
	int8_t tmp_display[8] = {0,0,0,0,0,0,0,0};
	int8_t map[8][8] = {{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0}
						};

	struct snake_element * pNew = pHead;

	while(pNew)
	{
		map[pNew->x][pNew->y] = 1;
		pNew = pNew->next_element;
	}
	map[_food.x][_food.y] = 1;

	for(size_t i = 0; i < 8; i++)
	{
		for(size_t j = 0; j < 8; j++)
		{
			leds[XY(7 - i, 7 - j)].r = leds[XY(7 - i, 7 - j)].g = leds[XY(7 - i, 7 - j)].b = 0;
			if(map[i][j])
				if(i == _food.x && j == _food.y)
				{
					leds[XY(7 - i, 7 - j)].r = 1;
					leds[XY(7 - i, 7 - j)].g = leds[XY(7 - i, 7 - j)].b = 0;
				}
				else if(pHead->x == i && pHead->y ==j)
				{
					leds[XY(7 - i, 7 - j)].g = 3;
					leds[XY(7 - i, 7 - j)].r = leds[XY(7 - i, 7 - j)].b = 0;
				}
				else
				{
					leds[XY(7 - i, 7 - j)].g = 1;
					leds[XY(7 - i, 7 - j)].r = leds[XY(7 - i, 7 - j)].b = 0;
				}
		}
	}
	ws2812_setleds(leds, NUM_OF_LEDS * 3);
	_delay_ms(75);
}

void draw_score(int8_t score)
{
	int8_t leftChar = 0, rightChar = 0;
	int8_t rest = 0;
	
	if(score >= 10)
	{
		rest = score % 10;
		rightChar = rest;
		leftChar = ((score - rest) / 10);
	}
	else
		rightChar = score;
	
	clear_screen();
	int8_t tmp_display[8] = {0,0,0,0,0,0,0,0};
	
	for(size_t i = 0; i < 8; i++)
		tmp_display[i] = charactersFirst[leftChar][i] | charactersSecond[rightChar][i];
	
	for(size_t i = 0; i < 8; i++)
		for(size_t j = 0; j < 8; j++)
		{
			if(tmp_display[i] & charactersMask[j])
			{
				leds[XY(7 - j, 7 - i)].r = leds[XY(7 - j, 7 - i)].g = 0;
				leds[XY(7 - j, 7 - i)].b = 1;
			}
		}
	_delay_ms(10);
	ws2812_sendarray((uint8_t*)leds, NUM_OF_LEDS * 3);
	_delay_ms(3000);
}