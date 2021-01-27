#pragma once

#include "Controller.h"
#include <SDL.h>

//using namespace CONTROLLER;

extern Controller;

class Mouse : public Controller
{
private:
    SDL_Cursor* cursor;
    int posX;
    int posY;
public:

    int getPosX() { return posX; }
    int getPosY() { return posY; }

    Mouse() { }

    void Initialize(CONTROLLER_STATE state) override // Our mouse has two state if its active , it can be in the menu or in game
    {
        this->state = state;
        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        SDL_SetCursor(cursor);
        SDL_GetMouseState(&posX, &posY);
    }

    void Update() override {
        SDL_GetMouseState(&posX, &posY);
    }

};

