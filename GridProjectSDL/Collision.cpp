
#include "Collision.h"


void PlayerObject_touched_EnemyObject(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::Enemy) << std::endl;
	RestartGame(allObjectsClass);
}
void PlayerObject_touched_FixedObject(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::FixedObject) << std::endl;
}
void PlayerObject_touched_MovableObject(PlayerObjectClass* currentObject, PlayerObjectClass* movedObject, int x, int y, AllObjectsClass* allObjectsClass) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::MovableObject) << std::endl;
	// Run Collision detection check on movable object:
	bool isPositionOccupied = CheckCollisionOnNewPosition(allObjectsClass, movedObject, x, y);
	if (isPositionOccupied == true) {
		std::cout << "Can't move" << std::endl;
	}
	if (isPositionOccupied == false) {
		//MoveObject(movedObject, movedObject->getPosX() + x, movedObject->getPosY() + y);// move pushed object
		MoveObject(currentObject, currentObject->getPosX() + x, currentObject->getPosY() + y);// move palyer
	}
}
void PlayerObject_touched_Empty(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass, int x, int y) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::Empty) << std::endl;
	MoveObject(currentObject, currentObject->getPosX() + x, currentObject->getPosY() + y);
}
void MovableObject_touched_Empty(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass, int x, int y) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::Empty) << std::endl;
	MoveObject(currentObject, currentObject->getPosX() + x, currentObject->getPosY() + y);
}
void PlayerObject_touched_MovableObjectDestinationTarget(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass, int x, int y) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::MovableObjectDestinationTarget) << std::endl;
	MoveObject(currentObject, currentObject->getPosX() + x, currentObject->getPosY() + y);
}
void MovableObject_touched_MovableObjectDestinationTarget(PlayerObjectClass* currentObject, AllObjectsClass* allObjectsClass, int x, int y) {
	std::cout << "Hit: " << TO_STRING_TYPE(ObjectType::MovableObjectDestinationTarget) << std::endl;
	MoveObject(currentObject, currentObject->getPosX() + x, currentObject->getPosY() + y);
	allObjectsClass->gameVariables.scoreIncrease(1);
}
/// <summary>
///  Checks if new position is occupied. If occupied returns true, if free return false.
/// </summary>
bool CheckCollisionOnNewPosition(AllObjectsClass* allObjectsClass, PlayerObjectClass* currentObject, int x, int y) {
	int newX = currentObject->getPosX() + x;
	int newY = currentObject->getPosY() + y;
	ObjectType touchedObjectType = allObjectsClass->getObjectTypeAt(newX, newY);
	if (allObjectsClass->gridClass.isWithinBounds(newX, newY) == false) {
		return true;
	}
	if (currentObject->getObjectType() == ObjectType::Player) {	///////////////////////////// CHECK FOR PLAYER 
		if (touchedObjectType == ObjectType::Enemy) {
			PlayerObject_touched_EnemyObject(currentObject, allObjectsClass);
			return true;
		}
		if (touchedObjectType == ObjectType::FixedObject) {
			PlayerObject_touched_FixedObject(currentObject, allObjectsClass);
			return true;
		}
		if (touchedObjectType == ObjectType::MovableObject) {
			PlayerObject_touched_MovableObject(currentObject, allObjectsClass->getObjectAt(newX, newY), x, y, allObjectsClass);
			return true;
		}
		if (touchedObjectType == ObjectType::Empty) {
			PlayerObject_touched_Empty(currentObject, allObjectsClass, x, y);
			return true;
		}
		if (touchedObjectType == ObjectType::MovableObjectDestinationTarget) {
			PlayerObject_touched_MovableObjectDestinationTarget(currentObject, allObjectsClass, x, y);
			return false;
		}
	}
	if (currentObject->getObjectType() == ObjectType::MovableObject) { ////////////// CHECK FOR MOVABLE OBJECT 
		if (touchedObjectType == ObjectType::Empty) {
			MovableObject_touched_Empty(currentObject, allObjectsClass, x, y);
			return false;
		}
		if (touchedObjectType == ObjectType::Enemy) {
			return true;
		}
		if (touchedObjectType == ObjectType::FixedObject) {
			return true;
		}
		if (touchedObjectType == ObjectType::MovableObject) {
			return true;
		}
		if (touchedObjectType == ObjectType::MovableObjectDestinationTarget) {
			MovableObject_touched_MovableObjectDestinationTarget(currentObject, allObjectsClass, x, y);
			return false;
		}
	}
	return true;									// Returns true for undefined objects -> No move will be made
}