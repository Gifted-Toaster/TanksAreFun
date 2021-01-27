#include "./Collision.h"

bool Collision::CheckRectangleCollision(const SDL_FRect& rectangleA, const SDL_FRect& rectangleB) {
	return (
		rectangleA.x + rectangleA.w >= rectangleB.x &&
		rectangleB.x + rectangleB.w >= rectangleA.x &&
		rectangleA.y + rectangleA.h >= rectangleB.y &&
		rectangleB.y + rectangleB.h >= rectangleA.y
		);
}