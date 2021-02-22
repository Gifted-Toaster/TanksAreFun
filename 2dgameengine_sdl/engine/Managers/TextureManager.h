#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "./Game.h";

// Using sdl to load a texture -> Asset manager stores them
class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_FRect destinationRectangle, SDL_RendererFlip flip);
};

#endif // !

