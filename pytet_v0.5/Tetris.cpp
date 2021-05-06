#include "Tetris.h"
 int nBlockTypes=0 ;
  int nBlockDegrees=0 ;
   Matrix** setOfBlockObjects=0 ;
int iScreenDw=0;	
	void Tetris::init(int* setOfBlockArrays[],const int MAX_BLK_TYPES, const int  MAX_BLK_DEGREES) {
		nBlockTypes = MAX_BLK_TYPES;
		nBlockDegrees = MAX_BLK_DEGREES;
		setOfBlockObjects = new Matrix*[MAX_BLK_TYPES];
		 int arrayBlk_maxSize = 0;
		for (int i = 0; i <nBlockTypes;i++) {
			setOfBlockObjects[i] = new Matrix [MAX_BLK_DEGREES];
		       for(int j=0;j<nBlockDegrees;j++){	
			if (arrayBlk_maxSize <= sqrt(sizeof(setOfBlockArrays[MAX_BLK_TYPES*i+j])))
				arrayBlk_maxSize = sqrt(sizeof(setOfBlockArrays[MAX_BLK_TYPES*i+j]));
		       }
		}
			iScreenDw = arrayBlk_maxSize;

			for (int i = 0; i < nBlockTypes; i++)
				for (int j = 0; j < nBlockDegrees; j++)
				{
					setOfBlockObjects[i][j] = Matrix(setOfBlockArrays[nBlockTypes*i+j], 
						sqrt(sizeof(setOfBlockArrays[nBlockTypes*i+j])),
						sqrt(sizeof(setOfBlockArrays[nBlockTypes*i+j])));
				}
			
		}

	int* Tetris::createArrayScreen() {
		arrayScreenDx = iScreenDw * 2 + iScreenDx;
		arrayScreenDy = iScreenDy + iScreenDw;
		int* arrayScreen=0;
		arrayScreen = new int [arrayScreenDx*arrayScreenDy];
		for (int y = 0; y < iScreenDy; y++)
		{
			for  (int x = 0; x < iScreenDw; x++)
				arrayScreen[y*arrayScreenDx+x] = 1;
			for (int x = 0; x < iScreenDx; x++)
				arrayScreen[y * arrayScreenDx+x+iScreenDw] = 0;
			for (int x = 0; x < iScreenDw; x++)
				arrayScreen[y * arrayScreenDx+x + iScreenDw + iScreenDx] = 1;
		}
		for (int y = 0; y < iScreenDw; y++)
			for (int x = 0; x < arrayScreenDx; x++)
				arrayScreen[arrayScreenDx*(iScreenDy + y)+x] = 1;

		return arrayScreen;
	}

	Tetris::Tetris(int iScreenDy, int iScreenDx) {
		this->iScreenDy = iScreenDy;
		this->iScreenDx = iScreenDx;
		this->idxBlockDegree = 0;
		int* arrayScreen = createArrayScreen();
		 iScreen = Matrix(arrayScreen,arrayScreenDx, arrayScreenDy);
		 OScreen = Matrix(iScreen);
		justStarted = false;
		
	}

	TetrisState Tetris::accept(char key) {
		statetet = Running;
		//deleteFullLines();
		Matrix currBlk;
		Matrix tempBlk;
		if (key >= '0' && key <= '6') {
			if (justStarted == false);
			//deleteFullLines();
			iScreen = Matrix(OScreen);
			idxBlockType = key - '0';
			 currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
			top = 0;
			left = iScreenDw + iScreenDx / 2 - currBlk.get_dx() / 2;
			 tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
			tempBlk.add(&currBlk);
			justStarted = false;
			cout << "\n";

			if (tempBlk.anyGreaterThan(1))
				statetet = Finished;
			OScreen = Matrix(&iScreen);
			OScreen.paste(&tempBlk, top, left);
			return statetet;
		}
		else if (key == 'a')
			left -= 1;
		else if (key == 'd')
			left += 1;
		else if (key == 's')
			top += 1;
		else if (key == 'w')
		{
			idxBlockDegree = (idxBlockDegree + 1) % nBlockDegrees;
			currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
		}
		else if (key == ' ')
			while (!tempBlk.anyGreaterThan(1)) {
				top += 1;
				tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
				tempBlk.add(&currBlk);
			}
		else
			cout << "wrong Key!!" << endl;

		tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
		tempBlk.add(&currBlk);

		if (tempBlk.anyGreaterThan(1)) {
			if (key == 'a')
				left += 1;
			else if (key == 'd')
				left -= 1;
			else if (key == 's')
			{
				top -= 1;
				statetet = NewBlock;
			}
			else if (key == 'w') {
				idxBlockDegree = (idxBlockDegree - 1) % nBlockDegrees;
				currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
			}
			else if (key == ' ') {
				top -= 1;
				statetet = NewBlock;
			}

			tempBlk = iScreen.clip(top, left, top + currBlk.get_dy(), left + currBlk.get_dx());
			tempBlk.add(&currBlk);


		}
		OScreen = Matrix(iScreen);
		OScreen.paste(&tempBlk, top, left);

		return statetet;
	} //accept end







	
