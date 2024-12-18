
#include "Keyboard.h"



void KeyboardKeyPressEvents_(SDL_Event* SDL_event, AllObjectsClass* allObjectsClass) {
	if (SDL_event->type == SDL_KEYDOWN) {
		switch (SDL_event->key.keysym.sym) {
		case SDLK_w:
			std::cout << "W" << std::endl;
			CheckCollisionOnNewPosition(allObjectsClass, &allObjectsClass->listPlayerObjectClass[0], 0, -1);
			break;
		case SDLK_s:
			std::cout << "S" << std::endl;
			CheckCollisionOnNewPosition(allObjectsClass, &allObjectsClass->listPlayerObjectClass[0], 0, 1);
			break;
		case SDLK_a:
			std::cout << "A" << std::endl;
			CheckCollisionOnNewPosition(allObjectsClass, &allObjectsClass->listPlayerObjectClass[0], -1, 0);
			break;
		case SDLK_d:
			std::cout << "D" << std::endl;
			CheckCollisionOnNewPosition(allObjectsClass, &allObjectsClass->listPlayerObjectClass[0], 1, 0);
			break;
		case SDLK_SPACE:
			std::cout << "SPACE" << std::endl;
			RestartGame(allObjectsClass);
			break;
		}
	}
}