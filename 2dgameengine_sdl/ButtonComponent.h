#pragma once
#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#include "./Component.h"
#include "./AssetManager.h"
#include "./Game.h"
#include <SDL.h>
#include <SDL_ttf.h>

class ButtonComponent : public Component {

	// It has a rectangle with drawn border
	// It has a text in it
	// It will be marked for highlight target from entitymanager
private:
	SDL_Rect button; // x + y + w + h
	SDL_Surface* surf; // text + color
	SDL_Texture* texture; // renderer + surf

public:
	bool highlight;
	ButtonType type;

	ButtonComponent(int posX , int posY, int w , int h , std::string text , SDL_Color col , std::string fontFam , ButtonType type) {
		button.x = posX;
		button.y = posY;
		button.w = w;
		button.h = h;
		this->type = type;
		surf = TTF_RenderText_Solid(Game::assetManager->GetFont(fontFam), text.c_str(), col);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surf);

	}

	void Render() {
		FontManager::Draw(texture, button);
		if (highlight) {
			SDL_RenderDrawRect(Game::renderer, &button);
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
