#pragma once
#include <string>
#define color_normal	"\033[37m"
#define color_red		"\033[31m"
#define color_green		"\033[32m"
#define color_yellow	"\033[33m"
#define color_blue		"\033[34m"
#define color_purple	"\033[35m"
#define color_cyan		"\033[36m"
#define color_pink		"\033[95m"
#define b_color_black	"\033[1m"
#include "Tetris.h"
extern Matrix** setOfCBlockObjects ;
extern Matrix obj;
class CTetris : public Tetris {
	public:
		static void init(int* setOfCBlockArrays[], int MAX_BLK_TYPES, int  MAX_BLK_DEGREES);		
	
		        Matrix iCScreen;
			        Matrix OCScreen;
	CTetris(int iScreenDy, int iScreenDx);
	TetrisState accept(int key);
};
