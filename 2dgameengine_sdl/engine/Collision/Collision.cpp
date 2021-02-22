#include "./Collision.h"

bool Collision::CheckRectangleCollision(const SDL_FRect& rectangleA, const SDL_FRect& rectangleB) {
	return (
		rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y
		);
}

bool Collision::MouseCollision(const SDL_Rect& rectangle, int posX , int posY) {
	return (
		rectangle.x <= posX &&
		rectangle.x + rectangle.w >= posX &&
		rectangle.y <= posX &&
		rectangle.y + rectangle.h >= posY
		);
}