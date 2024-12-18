
#include "DrawRender_SDL.h"



void Draw_AllObjectsOnList(SDL_Renderer* renderer, AllObjectsClass* allObjectsClass) {
	for (int i = allObjectsClass->listPlayerObjectClass.size() - 1; i >= 0; --i) {// Reverse loop so player is always rendered on top
		if (allObjectsClass->listPlayerObjectClass[i].getObjectType() == ObjectType::Player) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	// R,G,B,A
			SDL_Rect rect = {
				allObjectsClass->listPlayerObjectClass[i].getPosX() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getPosY() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getSizeX() ,
				allObjectsClass->listPlayerObjectClass[i].getSizeY() };
			SDL_RenderFillRect(renderer, &rect);
		}
		if (allObjectsClass->listPlayerObjectClass[i].getObjectType() == ObjectType::FixedObject) {
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// R,G,B,A
			SDL_Rect rect = {
				allObjectsClass->listPlayerObjectClass[i].getPosX() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getPosY() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getSizeX() ,
				allObjectsClass->listPlayerObjectClass[i].getSizeY() };
			SDL_RenderFillRect(renderer, &rect);
		}
		if (allObjectsClass->listPlayerObjectClass[i].getObjectType() == ObjectType::Enemy) {
			SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);	// R,G,B,A
			SDL_Rect rect = {
				allObjectsClass->listPlayerObjectClass[i].getPosX() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getPosY() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getSizeX() ,
				allObjectsClass->listPlayerObjectClass[i].getSizeY() };
			SDL_RenderFillRect(renderer, &rect);
		}
		if (allObjectsClass->listPlayerObjectClass[i].getObjectType() == ObjectType::MovableObject) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);	// R,G,B,A
			SDL_Rect rect = {
				allObjectsClass->listPlayerObjectClass[i].getPosX() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getPosY() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getSizeX() ,
				allObjectsClass->listPlayerObjectClass[i].getSizeY() };
			SDL_RenderFillRect(renderer, &rect);
		}
		if (allObjectsClass->listPlayerObjectClass[i].getObjectType() == ObjectType::MovableObjectDestinationTarget) {
			SDL_SetRenderDrawColor(renderer, 70, 200, 200, 255);	// R,G,B,A
			SDL_Rect rect = {
				allObjectsClass->listPlayerObjectClass[i].getPosX() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getPosY() * allObjectsClass->gridClass.getBlockSize(),
				allObjectsClass->listPlayerObjectClass[i].getSizeX() ,
				allObjectsClass->listPlayerObjectClass[i].getSizeY() };
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
void Draw_GridBoundaries(SDL_Renderer* renderer, AllObjectsClass* allObjectsClass)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int verticalPixels = allObjectsClass->gridClass.getVerticalSize_inPixels();
	int horizontalPixels = allObjectsClass->gridClass.getHorizontalSize_inPixels();
	SDL_RenderDrawLine(renderer,
		allObjectsClass->gridClass.getTopLeftPoint()[0],
		allObjectsClass->gridClass.getTopLeftPoint()[1],
		allObjectsClass->gridClass.getBottomLeftPoint()[0],
		allObjectsClass->gridClass.getBottomLeftPoint()[1]);
	SDL_RenderDrawLine(renderer,
		allObjectsClass->gridClass.getBottomLeftPoint()[0],
		allObjectsClass->gridClass.getBottomLeftPoint()[1],
		allObjectsClass->gridClass.getBottomRightPoint()[0],
		allObjectsClass->gridClass.getBottomRightPoint()[1]);
	SDL_RenderDrawLine(renderer,
		allObjectsClass->gridClass.getBottomRightPoint()[0],
		allObjectsClass->gridClass.getBottomRightPoint()[1],
		allObjectsClass->gridClass.getTopRightPoint()[0],
		allObjectsClass->gridClass.getTopRightPoint()[1]);
	SDL_RenderDrawLine(renderer,
		allObjectsClass->gridClass.getTopRightPoint()[0],
		allObjectsClass->gridClass.getTopRightPoint()[1],
		allObjectsClass->gridClass.getTopLeftPoint()[0],
		allObjectsClass->gridClass.getTopLeftPoint()[1]);
}
/// <summary>
/// 
/// </summary>
/// <param name="text">Pass like this 1) char textMessage[20] = "text"; or 2) "text"</param>
/// <param name="texture">Predefine: SDL_Texture* texture1 = {};</param>
/// <param name="rect">Predefine: SDL_Rect rect1 = {};</param>
void Render_Text(SDL_Renderer* renderer, int x, int y, const char* text, const char* fontPath, int fontSize,
	SDL_Texture** texture, SDL_Rect* rect) {
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
	if (font == NULL) {
		fprintf(stderr, "error: font not found\n");
		exit(EXIT_FAILURE);
	}
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	int text_width = surface->w;
	int text_height = surface->h;
	SDL_FreeSurface(surface);
	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}