#pragma once

#include <iostream>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include "DrawRender_SDL.h"
#include "Keyboard.h"
#include "AllObjectsClass.h"
#include "Mouse.h"


void SelectPickedMouseObject(AllObjectsClass* allObjectsClass, int x, int y);
int getRandomNumber(int min, int max);
void MoveObject(PlayerObjectClass* playerObjectClass, int newX, int newY);
void RestartGame(AllObjectsClass* allObjectsClass);
void CreateNewObject(AllObjectsClass* allObjectsClass, ObjectType objectType);
void CreateNewObject(AllObjectsClass* allObjectsClass, ObjectType objectType, int x, int y);
void NewGame(SDL_Renderer* renderer, SDL_Window* window);
int GameInit();



