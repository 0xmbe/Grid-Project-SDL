#pragma once

#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
#include <array>
#include <string>
#include <vector>

#define TO_STRING_VARIABLE(Variable) (void(Variable),#Variable)
#define TO_STRING_FUNCTION(Function) (void(&Function),#Function)
#define TO_STRING_CLASSNAME(ClassName,Method) (void(&ClassName::Method),#Method)
#define TO_STRING_TYPE(Type) (void(sizeof(Type)),#Type)

enum ObjectType {
	Empty,
	Player,
	FixedObject,
	MovableObject,
	Enemy,
	MovableObjectDestinationTarget
};

class PlayerObjectClass {
public:
	int getPosX();
	int getPosY();
	int getSizeX();
	int getSizeY();
	/*int* getPosXY() { int arr[2] = {}; arr[0] = getPosX(); arr[1] = getPosY(); return arr; }*/
	void setPosX(int x);
	void setPosY(int y);
	void setPosXY(int x, int y);
	ObjectType getObjectType();
	void setObjectType(ObjectType objectType);
	void setGridBlockSize(int gridBlockSize);
	int getGridBlockSize();

private:
	ObjectType objectType_;
	int positionX_;
	int positionY_;
	int sizeX_ = 20;
	int sizeY_ = 20;
	int gridBlockSize_;


};
class GameVariables {
public:
	void scoreIncrease(int i);
	int getScore();
	void setScore(int i);
	void getScoreInCharArray(char* charArray, size_t arraySize);
	void setSelectedObject(PlayerObjectClass* selectedObject);
	void deSelectSelectedObject();
	PlayerObjectClass* getSelectedObject();

	bool isRunning = true;
	const char* fontPath = "C:/Windows/Fonts/consola.ttf";
	char score_text[7] = "SCORE:";
private:
	int scoreInt_;
	char* scoreCharArray_;
	//intptr_t selectedObject_;
	PlayerObjectClass* selectedObject_;

};
class GridClass {
public:
	GridClass(int rows, int cols, int blockSize) ;
	int getBlockSize();
	int getRows();
	int getCols();
	//ObjectType getObjectType(int row, int col) {
	//	
	//	(PlayerObjectClass)[row][col]
	//}
	void setValue(int row, int col, int value);
	int getValue(int row, int col);
	bool isWithinBounds(int row, int col);
	void print() const;
	void setGlobalGridStartPositionIn_inPixels(int x, int y);
	int getGlobalGridStartPositionX_inPixels();
	int getGlobalGridStartPositionY_inPixels();
	int getHorizontalSize_inPixels();
	int getVerticalSize_inPixels();
	//int* getBottomLeftPoint() {
	//	int* arr = new int[2];
	//	arr[0] = getVerticalSizeInPixels() + getGlobalGridStartPositionY();
	//	arr[1] = getHorizontalSizeInPixels() + getGlobalGridStartPositionX();
	//	return arr;
	//}
	std::array<int, 2> getTopRightPoint();
	std::array<int, 2> getTopLeftPoint();
	std::array<int, 2> getBottomLeftPoint();
	std::array<int, 2> getBottomRightPoint();
	//int getMatrixValueAt(int x, int y) {
	//	GridClass::matrix_01[x][y];
	//	return matrix_01[x][y];
	//}
private:
	int positionX_, positionY_;
	int rows_, cols_;
	int gridBlockSize_;
	std::vector<std::vector<int>> grid_;
	//int matrix_01[4][5];


};
class AllObjectsClass {
public:
	/*----------------------Constructor---------------------- */
	AllObjectsClass(int gridRows, int gridCols, int blockSize) : gridClass(gridRows, gridCols, blockSize) {
		//setAllObjectsToEmpty(gridRows, gridCols);
		setGridBlockSizeToAllObjects(blockSize);
	}
	/*----------------------Member objects---------------------- */
	GridClass gridClass;
	std::vector<PlayerObjectClass> listPlayerObjectClass;
	GameVariables gameVariables;
	//MatrixCollectionClass matrixCollectionClass;



	ObjectType getObjectTypeAt(int x, int y);
	PlayerObjectClass* getObjectAt(int x, int y);
	int getObjectListIndexNumberAt(int x, int y, ObjectType objectType);
	bool isPositionFree(int x, int y);
	bool tryMovePushedObjectAtTo(int x, int y, int newX, int newY);
	void deleteObjectAt(int x, int y, ObjectType objectType);

private:
	void setGridBlockSizeToAllObjects(int blockSize);

	/*void setAllObjectsToEmpty(int gridRows, int gridCols) {
		for (int row = 0; row < gridRows; ++row) {
			for (int col = 0; col < gridCols; ++col) {
				gridClass.setValue(row, col, ObjectType::Empty);
			}
		}
	}*/
};