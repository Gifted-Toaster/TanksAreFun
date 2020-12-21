#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL_ttf.h>
#include "./TextureManager.h"
#include "./FontManager.h"
#include "./EntityManager.h"

// Storing an entities textures
class AssetManager {

// Base class and its methods
private:
	EntityManager* manager;
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();

// Storage for textures
private:
	std::map<std::string, SDL_Texture*> textures;
public:
	void AddTexture(std::string texureId, const char* filePath);
	SDL_Texture* GetTexture(std::string textureId);

// Storage for fonts
private:
	std::map<std::string, TTF_Font*> fonts;
public:
	void AddFont(std::string fontId, const char* filePath , int fontSize);
	TTF_Font* GetFont(std::string fontId);
};

#endif

