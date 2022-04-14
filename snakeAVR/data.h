/*
 * data.h
 *
 * Created: 14.04.2022 19:31:22
 *  Author: Micha³ Jackowski
 */ 

#ifndef DATA_H_
#define DATA_H_

// numeric characters representation on 8x8 matrix (first character)
extern const int8_t charactersFirst[10][8];

// numeric characters representation on 8x8 matrix (second character)
extern const int8_t charactersSecond[10][8];

// Mask array (need for making character on display). Values from 128 to 1
extern int8_t charactersMask[8];

#endif /* DATA_H_ */