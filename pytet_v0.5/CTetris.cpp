#include "CTetris.h"


Matrix** setOfCBlockObjects=0 ;
Matrix obj=0;

	 void CTetris::init(int* setOfBlockArrays[], int MAX_BLK_TYPES, int  MAX_BLK_DEGREES) {
		Tetris::init(setOfBlockArrays, MAX_BLK_TYPES, MAX_BLK_DEGREES);
		setOfCBlockObjects = new Matrix * [MAX_BLK_TYPES];
		for (int i=0;i<MAX_BLK_TYPES;i++)
			setOfCBlockObjects[i]= new Matrix[MAX_BLK_DEGREES];
		for (int i = 0; i <MAX_BLK_TYPES ; i++)
			for (int j = 0; j < MAX_BLK_DEGREES; j++) {
				obj = Matrix(setOfBlockArrays[MAX_BLK_TYPES*i+j],
					sqrt(sizeof(setOfBlockArrays[MAX_BLK_TYPES*i+j])),
					sqrt(sizeof(setOfBlockArrays[MAX_BLK_TYPES*i+j])));
				obj.mulc(i + 1);
				setOfCBlockObjects[i][j] = obj;
			}

	}
	 CTetris::CTetris(int iScreenDy, int iScreenDx):Tetris(iScreenDy,iScreenDx) {
		int* arrayCScreen = createArrayScreen();
		iCScreen = Matrix(arrayCScreen,arrayScreenDx,arrayScreenDy);
		OCScreen = Matrix(iCScreen);
	}

	TetrisState CTetris::accept(int key) {
			if(key>='0'&&key<='6')
				iCScreen = Matrix(OCScreen);
			statetet = Tetris::accept(key);
			Matrix currBlk = setOfCBlockObjects[idxBlockType][idxBlockDegree];
			Matrix tempBlk = iCScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
			tempBlk.add(&currBlk);

			OCScreen = Matrix(iCScreen);
			OCScreen.paste(&tempBlk, top, left);
			return statetet;

		
	
}
