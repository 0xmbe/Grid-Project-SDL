
#include "GameManagement.h"



void SelectPickedMouseObject(AllObjectsClass* allObjectsClass, int x, int y) {
	auto blockSize = allObjectsClass->gridClass.getBlockSize();
	int h1 = x / blockSize;
	int v1 = y / blockSize;
	if (allObjectsClass->isPositionFree(h1, v1)) {
		std::cout << "Clicked on empty space" << std::endl;
		allObjectsClass->gameVariables.deSelectSelectedObject();
	}
	else {
		PlayerObjectClass* pickedObject = allObjectsClass->getObjectAt(h1, v1);
		std::cout << "Clicked on: " << pickedObject->getObjectType() << std::endl;
		allObjectsClass->gameVariables.setSelectedObject(pickedObject);
	}
}
int getRandomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}
void MoveObject(PlayerObjectClass* playerObjectClass, int newX, int newY) {
	playerObjectClass->setPosX(newX);
	playerObjectClass->setPosY(newY);
	std::cout << "Moved to: (" << newX << "," << newY << ")" << std::endl;
}
void RestartGame(AllObjectsClass* allObjectsClass) {
	std::cout << "Game over" << std::endl;
	allObjectsClass->gameVariables.isRunning = false;
	allObjectsClass->gameVariables.setScore(0);
}
void CreateNewObject(AllObjectsClass* allObjectsClass, ObjectType objectType) {
	PlayerObjectClass object = {};
	while (true) {
		int randX = getRandomNumber(allObjectsClass->gridClass.getGlobalGridStartPositionX_inPixels() / allObjectsClass->gridClass.getBlockSize(), allObjectsClass->gridClass.getCols() - 1);	// -1 so it doesnt go outside the bounds
		int randY = getRandomNumber(allObjectsClass->gridClass.getGlobalGridStartPositionY_inPixels() / allObjectsClass->gridClass.getBlockSize(), allObjectsClass->gridClass.getRows() - 1);
		if (allObjectsClass->isPositionFree(randX, randY)) {
			object.setPosXY(randX, randY);
			object.setObjectType(objectType);
			allObjectsClass->listPlayerObjectClass.push_back(object);
			break;
		}
	}
}
void CreateNewObject(AllObjectsClass* allObjectsClass, ObjectType objectType, int x, int y) {
	PlayerObjectClass object = {};
	if (allObjectsClass->isPositionFree(x, y)) {
		object.setPosXY(x, y);
		object.setObjectType(objectType);
		allObjectsClass->listPlayerObjectClass.push_back(object);
	}
	else {
		std::cout << "Position is already occupied!" << std::endl;
	}
}
void NewGame(SDL_Renderer* renderer, SDL_Window* window)
{
	std::cout << "New Game" << std::endl;		// Startup, Player Init:
	AllObjectsClass allObjectsClass(8, 8, 20);	// Grid size, Block size
	allObjectsClass.gridClass.setGlobalGridStartPositionIn_inPixels(20, 20);

	// Random generate create Objects:
	CreateNewObject(&allObjectsClass, ObjectType::Player);
	CreateNewObject(&allObjectsClass, ObjectType::FixedObject, 4, 4);
	CreateNewObject(&allObjectsClass, ObjectType::FixedObject);
	CreateNewObject(&allObjectsClass, ObjectType::Enemy);
	CreateNewObject(&allObjectsClass, ObjectType::MovableObject);
	CreateNewObject(&allObjectsClass, ObjectType::MovableObject);
	CreateNewObject(&allObjectsClass, ObjectType::MovableObject);
	CreateNewObject(&allObjectsClass, ObjectType::MovableObjectDestinationTarget);
	CreateNewObject(&allObjectsClass, ObjectType::MovableObjectDestinationTarget);



	//char score_text[7] = "SCORE:";
	SDL_Texture* score_texture = {};
	SDL_Rect score_rect = {};
	Render_Text(renderer, 20, 0, allObjectsClass.gameVariables.score_text, allObjectsClass.gameVariables.fontPath, 20, &score_texture, &score_rect);

	//char scorePoints_text[4] = "000";
	int score_int = allObjectsClass.gameVariables.getScore();
	//score_int = 55;
	//std::string score_strings = std::to_string(score_int);
	//const char* score_charArr_text = score_strings.c_str();
	//char* char_array = reinterpret_cast<char*>(&score_int);
	SDL_Texture* scorePoints_texture = {};
	SDL_Rect scorePoints_rect = {};
	//Render_Text(renderer, score_rect.x + score_rect.w + 5, 0, score_charArr_text, allObjectsClass.gameVariables.fontPath, 20, &scorePoints_texture, &scorePoints_rect);


	// Game loop
	SDL_Event SDL_event;
	while (allObjectsClass.gameVariables.isRunning) {
		while (SDL_PollEvent(&SDL_event)) {						// KEAYBOARD AND MOUSE EVENTS
			/*if (SDL_event.type == SDL_QUIT) {
				allObjectsClass.isRunning = true;
			}*/
			KeyboardKeyPressEvents_(&SDL_event, &allObjectsClass);
			MouseKeyPressEvents(&SDL_event, &allObjectsClass);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);				// Black background
		SDL_RenderClear(renderer);									// Clear the screen

		SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);	// Text 

		//auto aa = allObjectsClass.gameVariables.getScore();
		char score_charArr_text[4] = {};
		//allObjectsClass.gameVariables.getScoreInCharArray(charArray);
		allObjectsClass.gameVariables.getScoreInCharArray(score_charArr_text, sizeof(score_charArr_text));
		//score_charArr_text = Convert_int_to_charArray(aa);
		Render_Text(renderer, score_rect.x + score_rect.w + 5, 0, score_charArr_text, allObjectsClass.gameVariables.fontPath, 20, &scorePoints_texture, &scorePoints_rect);
		//delete[] score_charArr_text;
		SDL_RenderCopy(renderer, scorePoints_texture, NULL, &scorePoints_rect);	// Text 






		Draw_GridBoundaries(renderer, &allObjectsClass);			// Draw frame boundaries
		Draw_AllObjectsOnList(renderer, &allObjectsClass);			// Draw all objects

		SDL_RenderPresent(renderer);								// Present the rendered scene
		SDL_Delay(1000 / 60);										// Limit to 60 fps.
	}
	allObjectsClass.gameVariables.isRunning = true;								// Automatically restart game
	SDL_DestroyTexture(score_texture);

	/*SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();*/
	//return 0;
}
int GameInit() {
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "tit", "mess", NULL);
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	// Create a window																					// gridSize*cellSize
	SDL_Window* window = SDL_CreateWindow("My SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	// Create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	/////////////////////////////////////////////////////
	while (true) {
		NewGame(renderer, window);		// Game loop
	}
	/////////////////////////////////////////////////////
	//SDL_DestroyTexture(texture1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}