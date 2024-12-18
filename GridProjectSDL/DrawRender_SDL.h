#pragma once

#include <iostream>
#include "AllObjectsClass.h"
#include <SDL.h>
#include <SDL_ttf.h>


void Draw_AllObjectsOnList(SDL_Renderer* renderer, AllObjectsClass* allObjectsClass);
void Draw_GridBoundaries(SDL_Renderer* renderer, AllObjectsClass* allObjectsClass);
void Render_Text(SDL_Renderer* renderer, int x, int y, const char* text, const char* fontPath, int fontSize,
	SDL_Texture** texture, SDL_Rect* rect);
