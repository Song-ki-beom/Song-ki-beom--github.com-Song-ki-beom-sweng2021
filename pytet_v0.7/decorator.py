from game import *
from matrix import *
from tetris import *
import copy
##################################################
### ColorDecorator for Tetris Class
##################################################

class ColorDecorator(Game):
    nCBlockTypes = 0
    nCBlockDegrees = 0
    setOfCBlockObjects = 0
    iCScreenDw = 0
    
    def initCBlocks(self, setOfBlockObjects):
        nCBlockTypes  = len(setOfBlockObjects)
        nCBlockDegrees = len(setOfBlockObjects[0])
        self.setOfCBlockObjects = copy.deepcopy(setOfBlockObjects)
        self.setOfCBlockObjects = copy.deepcopy(setOfBlockObjects)
        self.count=1
        self.justStarted = False
        for i in range (nCBlockTypes):
            for j in range (nCBlockDegrees):
                self.setOfCBlockObjects[i][j].mulc(self.count)
            self.count = self.count +1
        return
		
    def __init__(self, game):
        self.game = game
        self.initCBlocks(game.setOfBlockObjects)
        arrayScreen = game.createArrayScreen()
        self.iCScreen = Matrix(arrayScreen)
        self.oCScreen = Matrix(self.iCScreen)
        return
	
    def accept(self, key):
        self.state  =self.game.accept(key)
        self.currCBlk = self.setOfCBlockObjects[self.game.idxBlockType][self.game.idxBlockDegree]
        if key >= '0' and key <= '6':                
            self.iCScreen = Matrix(self.oCScreen)
        tempCBlk = self.iCScreen.clip(self.game.top, self.game.left, self.game.top+self.game.currBlk.get_dy(), self.game.left+self.game.currBlk.get_dx())
        tempCBlk = self.currCBlk + tempCBlk
        self.oCScreen = Matrix(self.iCScreen)
        self.oCScreen.paste(tempCBlk, self.game.top, self.game.left)
        if self.state == TetrisState.NewBlock:
            self.deleteFullLines()
        return self.state
	
    def getScreen(self):
        return self.oCScreen

    def deleteFullLines(self):
        nDeleted = 0
        nScanned = self.currCBlk.get_dy()
        if self.game.top + self.currCBlk.get_dy() - 1 >= self.game.iScreenDy:
            nScanned -= ( self.game.top + self.currCBlk.get_dy() - self.game.iScreenDy)

        zero = Matrix([[0 for x in range(0, (self.game.iScreenDx - 2 * self.game.iScreenDw))]])
        for y in range(nScanned - 1, -1, -1):
            cy = self.game.top + y + nDeleted
            line = self.game.oScreen.clip(cy, 0, cy + 1, self.oCScreen.get_dx())
            if line.sum() == self.game.oScreen.get_dx():
                temp = self.game.oScreen.clip(0, 0, cy, self.game.oScreen.get_dx())
                self.game.oScreen.paste(temp, 1, 0)
                self.game.oScreen.paste(zero, 0, self.game.iScreenDw)
                temp = self.oCScreen.clip(0, 0, cy, self.oCScreen.get_dx())
                self.oCScreen.paste(temp, 1, 0)
                self.oCScreen.paste(zero, 0, self.game.iScreenDw)
                nDeleted += 1

        return nScanned


