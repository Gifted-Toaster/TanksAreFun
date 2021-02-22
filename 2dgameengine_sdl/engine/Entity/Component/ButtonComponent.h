#pragma once
#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#include "./Entity/Component/Component.h"
#include "./Managers/AssetManager.h"
#include "./Game.h"
#include <SDL.h>
#include <SDL_ttf.h>

class ButtonComponent : public Component {

	// It has a rectangle with drawn border
	// It has a text in it
	// It will be marked for highlight target from entitymanager
private:
	SDL_Rect position; // x + y + w + h
	SDL_Surface* surf; // text + color
	SDL_Texture* texture; // renderer + surf

public:
	bool highlight;
	ButtonType type;

	ButtonComponent(int posX , int posY, int w , int h , std::string text , SDL_Color col , std::string fontFam , ButtonType type) {
		position.x = posX;
		position.y = posY;
		position.w = w;
		position.h = h;
		this->type = type;
		surf = TTF_RenderText_Solid(Game::asset_manager->GetFont(fontFam), text.c_str(), col);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surf);

	}

	SDL_Rect GetPosition() { return position; }

	void Render() {
		FontManager::Draw(texture, position);
		if (highlight) {
			SDL_RenderDrawRect(Game::renderer, &position);
		}
	}

	//void Select() {
	//	switch (this->type) {
	//	case START:
	//		Game::ProcessNextLevel(Game,1);
	//	}
	//}
};

#endif
