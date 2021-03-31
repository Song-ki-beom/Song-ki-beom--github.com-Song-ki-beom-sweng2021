from tetris import *
import color_print
import copy
from enum import Enum


class BlockColor(Enum):
    red = 1
    green = 2
    yellow = 3
    blue = 4
    purple = 5
    cyan = 6
    pink = 7

class Ctetris(Tetris):


    def __init__(self, iScreenDy, iScreenDx):
        super().__init__(iScreenDy, iScreenDx)
        arrayScreenColor = self.createArrayScreen()
        self.iScreenColor = Matrix(arrayScreenColor)
        self.oScreenColor = Matrix(self.iScreenColor)
        

    def accept( self,key):
        self.state = TetrisState.NewBlock
        super().accept( key)
        self.currentBlkColor = copy.deepcopy(self.currBlk.get_array())
        for i in range(self.currBlk.get_dy()):
            for j in range(self.currBlk.get_dx()):
                if (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 1):
                       self.currentBlkColor[i][j] = 1
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 2):
                       self.currentBlkColor[i][j] = 2
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 3):
                       self.currentBlkColor[i][j] = 3
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 4):
                       self.currentBlkColor[i][j] = 4
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 5):
                       self.currentBlkColor[i][j] = 5
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 6):
                       self.currentBlkColor[i][j] = 6
                elif (self.currentBlkColor[i][j] ==1 and self.idxBlockType+1 == 7):
                       self.currentBlkColor[i][j] = 7
        self.currentBlkColor = Matrix(self.currentBlkColor)
        self.tempBlkColor = self.iScreenColor.clip(self.top, self.left, self.top + self.currentBlkColor.get_dy(),
                                         self.left + self.currentBlkColor.get_dx())
        self.tempBlkColor = self.tempBlkColor + self.currentBlkColor
        self.oScreenColor = Matrix(self.iScreenColor)
        self.oScreenColor.paste(self.tempBlkColor, self.top, self.left)

        if (self.state == TetrisState.NewBlock):
            self.iScreenColor = Matrix(self.oScreenColor)
        return self.state

    def deleteFullLines(self):
        super().deleteFullLines()  
        self.tempScreen = copy.deepcopy(self.oScreen.get_array())
        for y in range (self.oScreen.get_dy()- Tetris.iScreenDw):
            isFilled = True
            for x in range (Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
                if (self.tempScreen[y][x] == 0):
                    isFilled = False
            
            if (isFilled ==True):
                for i in range (y, 0,-1):
                    for j in range ( Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
                        self.tempScreen[i][j]=copy.deepcopy(self.tempScreen[i-1])
                for j in range (Tetris.iScreenDw, self.oScreen.get_dx()-Tetris.iScreenDw):
                    self.tempScreen[0][j] = 0
        self.iScreen = Matrix(self.tempScreen)
        self.oScreen = Matrix(self.iScreen)
        
        
        return None
        
     
