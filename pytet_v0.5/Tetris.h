#pragma once
#include "Matrix.h"
#include <cmath>
extern int nBlockTypes ;
 extern int nBlockDegrees ;
extern  Matrix** setOfBlockObjects ;
enum TetrisState { Running, NewBlock, Finished };
extern int iScreenDw ;
class Tetris {
	
public:
int iScreenDy = 0;
int iScreenDx = 0;
static void init(int* setOfCBlockArrays[], const int MAX_BLK_TYPES, const int  MAX_BLK_DEGREES);
	        
			        int idxBlockType = 0;
				        int idxBlockDegree = 0;
					        int arrayScreenDx = 0;
						        int arrayScreenDy = 0;
							        bool justStarted ;
								        Matrix iScreen;
									        Matrix OScreen;
										        TetrisState statetet;
											        int top = 0;
												      	int left = 0;
	 Tetris(int iScreenDy, int iScreenDx);
	int* createArrayScreen();
	TetrisState accept(char key);

};
