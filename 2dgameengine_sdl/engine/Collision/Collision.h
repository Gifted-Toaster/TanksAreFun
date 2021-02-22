#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

class Collision {
public:
	static bool CheckRectangleCollision(const SDL_FRect& rectangleA, const SDL_FRect& rectangleB);
	static bool MouseCollision(const SDL_Rect& rectangle, int posX, int posY);
};

#endif