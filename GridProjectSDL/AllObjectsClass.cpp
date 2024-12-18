#include "AllObjectsClass.h"




int PlayerObjectClass::getPosX() { return positionX_; }
int PlayerObjectClass::getPosY() { return positionY_; }
int PlayerObjectClass::getSizeX() { return sizeX_; }
int PlayerObjectClass::getSizeY() { return sizeY_; }
/*int* getPosXY() { int arr[2] = {}; arr[0] = getPosX(); arr[1] = getPosY(); return arr; }*/
void PlayerObjectClass::setPosX(int x) { positionX_ = x; }
void PlayerObjectClass::setPosY(int y) { positionY_ = y; }
void PlayerObjectClass::setPosXY(int x, int y) { positionX_ = x; positionY_ = y; }
ObjectType PlayerObjectClass::getObjectType() { return objectType_; }
void PlayerObjectClass::setObjectType(ObjectType objectType) { objectType_ = objectType; }
void PlayerObjectClass::setGridBlockSize(int gridBlockSize) { gridBlockSize_ = gridBlockSize; }
int PlayerObjectClass::getGridBlockSize() { return gridBlockSize_; }



//-------------------------------------------------------------------------------------------


void GameVariables::scoreIncrease(int i) {
	scoreInt_ += i;
	std::cout << "Score: " << scoreInt_ << std::endl;
}
int GameVariables::getScore() {
	return scoreInt_;
}
void GameVariables::setScore(int i) {
	scoreInt_ = i;
	std::cout << "Score: " << scoreInt_ << std::endl;
}
void GameVariables::getScoreInCharArray(char* charArray, size_t arraySize) {
	std::string stdString = std::to_string(scoreInt_);
	if (stdString.length() < arraySize) {
		strcpy_s(charArray, arraySize, stdString.c_str());
	}
	else {
		std::cout << "! Array too long" << std::endl;
	}
}
void GameVariables::setSelectedObject(PlayerObjectClass* selectedObject){
	selectedObject_ = selectedObject;
	std::cout << "Object selected." << std::endl;
}
void GameVariables::deSelectSelectedObject(){
	selectedObject_ = NULL;
}
PlayerObjectClass* GameVariables::getSelectedObject(){
	return selectedObject_;
}



//-------------------------------------------------------------------------------------------



GridClass::GridClass(int rows, int cols, int blockSize) : rows_(rows), cols_(cols), gridBlockSize_(blockSize) {
	grid_.resize(rows, std::vector<int>(cols));
}
int GridClass::getBlockSize() {
	return gridBlockSize_;
}
int GridClass::getRows() {
	return rows_;
}
int GridClass::getCols() {
	return cols_;
}
//ObjectType getObjectType(int row, int col) {
//	
//	(PlayerObjectClass)[row][col]
//}
void GridClass::setValue(int row, int col, int value) {
	if (isWithinBounds(row, col)) {
		grid_[row][col] = value;
	}
}
int GridClass::getValue(int row, int col) {
	if (isWithinBounds(row, col)) {
		return grid_[row][col];
	}
	else {
		return 0;
	}
}
bool GridClass::isWithinBounds(int row, int col) {
	if (row >= positionX_ / gridBlockSize_ &&
		row < positionX_ / gridBlockSize_ + rows_ &&
		col >= positionY_ / gridBlockSize_ &&
		col < positionY_ / gridBlockSize_ + cols_) {
		std::cout << "Position ok (" << row << ", " << col << ")" << std::endl;
		return true;
	}
	else {
		std::cerr << "Position (" << row << ", " << col << ") out of bounds" << std::endl;
		return false;
	}
}
void GridClass::print() const {
	for (const auto& row : grid_) {
		for (const auto& element : row) {
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
}
void GridClass::setGlobalGridStartPositionIn_inPixels(int x, int y) {
	positionX_ = x;
	positionY_ = y;
}
int GridClass::getGlobalGridStartPositionX_inPixels() {
	return positionX_;
}
int GridClass::getGlobalGridStartPositionY_inPixels() {
	return positionY_;
}
int GridClass::getHorizontalSize_inPixels() {
	return getRows() * getBlockSize();
}
int GridClass::getVerticalSize_inPixels() {
	return getCols() * getBlockSize();
}
//int* getBottomLeftPoint() {
//	int* arr = new int[2];
//	arr[0] = getVerticalSizeInPixels() + getGlobalGridStartPositionY();
//	arr[1] = getHorizontalSizeInPixels() + getGlobalGridStartPositionX();
//	return arr;
//}
std::array<int, 2> GridClass::getTopRightPoint() {
	std::array<int, 2> arr = {
		getHorizontalSize_inPixels() + getGlobalGridStartPositionX_inPixels(),
		getGlobalGridStartPositionY_inPixels(),
	};
	return arr;
}
std::array<int, 2> GridClass::getTopLeftPoint() {
	std::array<int, 2> arr = {
		getGlobalGridStartPositionX_inPixels(),
		getGlobalGridStartPositionY_inPixels(),
	};
	return arr;
}
std::array<int, 2> GridClass::getBottomLeftPoint() {
	std::array<int, 2> arr = {
		getGlobalGridStartPositionX_inPixels(),
		getVerticalSize_inPixels() + getGlobalGridStartPositionY_inPixels()
	};
	return arr;
}
std::array<int, 2> GridClass::getBottomRightPoint() {
	std::array<int, 2> arr = {
		getHorizontalSize_inPixels() + getGlobalGridStartPositionX_inPixels(),
		getVerticalSize_inPixels() + getGlobalGridStartPositionY_inPixels()
	};
	return arr;
}


//-------------------------------------------------------------------------------------------
ObjectType AllObjectsClass::getObjectTypeAt(int x, int y) {
	for (int i = 0; i < listPlayerObjectClass.size(); ++i) {
		if (listPlayerObjectClass[i].getPosX() == x &&
			listPlayerObjectClass[i].getPosY() == y) {
			return listPlayerObjectClass[i].getObjectType();
		}
	}
	return ObjectType::Empty;				/// ??
}
PlayerObjectClass* AllObjectsClass::getObjectAt(int x, int y) {
	for (int i = 0; i < listPlayerObjectClass.size(); ++i) {
		if (listPlayerObjectClass[i].getPosX() == x &&
			listPlayerObjectClass[i].getPosY() == y) {
			return &listPlayerObjectClass[i];
		}
	}
}
int AllObjectsClass::getObjectListIndexNumberAt(int x, int y, ObjectType objectType) {
	for (int i = 0; i < listPlayerObjectClass.size(); ++i) {
		if (listPlayerObjectClass[i].getPosX() == x &&
			listPlayerObjectClass[i].getPosY() == y) {
			if (listPlayerObjectClass[i].getObjectType() == objectType) {
				return i;
			}
		}
	}
	return -1;
}
bool AllObjectsClass::isPositionFree(int x, int y) {
	for (int i = 0; i - listPlayerObjectClass.size(); ++i) {
		if (listPlayerObjectClass[i].getPosX() == x &&
			listPlayerObjectClass[i].getPosY() == y) {
			return false;
		}
	}
	return true;
}
bool AllObjectsClass::tryMovePushedObjectAtTo(int x, int y, int newX, int newY) {
	for (int i = 0; i - listPlayerObjectClass.size(); ++i) {
		if (listPlayerObjectClass[i].getPosX() == x &&
			listPlayerObjectClass[i].getPosY() == y) {
			if (gridClass.isWithinBounds(newX, newY)) {
				if (getObjectTypeAt(newX, newY) == ObjectType::Empty) {
					return true;
				}
				if (getObjectTypeAt(newX, newY) == ObjectType::MovableObjectDestinationTarget) {
					return true;
				}
				else {
					std::cout << "Position (" << newX << ", " << newY << ") not empty" << std::endl;
					return false;
				}
			}
			else {
				//std::cout << listPlayerObjectClass[i].getObjectType() << std::endl;
				return false;
			}
		}
	}
	return false;
}
void AllObjectsClass::deleteObjectAt(int x, int y, ObjectType objectType) {
	int objectNumber = getObjectListIndexNumberAt(x, y, objectType);
	listPlayerObjectClass.erase(listPlayerObjectClass.begin() + objectNumber);
	std::cout << "Deleted index: " << objectNumber << " Type: " << objectType << std::endl;
}
void AllObjectsClass::setGridBlockSizeToAllObjects(int blockSize) {
	//playerObjectClass.setGridBlockSize(blockSize);
	for (int i = 0; i < listPlayerObjectClass.size(); ++i) {
		listPlayerObjectClass[i].setGridBlockSize(blockSize);
	}
}