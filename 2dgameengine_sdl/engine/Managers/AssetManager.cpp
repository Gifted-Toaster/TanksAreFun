#include "AssetManager.h"

AssetManager::AssetManager( EntityManager* manager) : manager(manager) {}

bool AssetManager::HasNoAssets()
{
	return textures.empty() && fonts.empty();
}

void AssetManager::DeleteData() { // Free memory on the heap
	for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		SDL_DestroyTexture(it->second); // Free up texture pointers
	}
	textures.clear();
	for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
	{
		TTF_CloseFont(it->second); // Free up font pointers
	}
	fonts.clear();
}

void AssetManager::ClearData() {
	textures.clear();
	fonts.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId)
{
	return fonts[fontId];
}
