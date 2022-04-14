/*
 * display.h
 *
 * Created: 14.04.2022 19:36:08
 *  Author: Micha³ Jackowski
 */ 

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "ws2812_config.h"
#include "light_ws2812.h"
#include "structures.h"

#define NUM_OF_LEDS       64

extern struct cRGB leds[NUM_OF_LEDS];

void draw_scene(struct snake_element * pHead, struct food _food, int8_t board_max_x, int8_t board_max_y);

void draw_score(int8_t score);

#endif /* DISPLAY_H_ */