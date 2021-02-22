#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "./Managers/FontManager.h"
#include "./Managers/EntityManager.h"
#include "./Managers/AssetManager.h"
#include "./Game.h"

#pragma once
class TextLabelComponent : public Component {
private:
	SDL_Rect position;
	std::string text;
	std::string fontFamily;
	SDL_Color color;
	SDL_Texture* texture;
	bool dinamic;

public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
		this->position.x = x;
		this->position.y = y;
		this->text = text;
		this->fontFamily = fontFamily;
		this->color = color;
		dinamic = false;
		SetLabelText(text, fontFamily);
	}
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color , bool dinamic) {
		this->position.x = x;
		this->position.y = y;
		this->text = text;
		this->fontFamily = fontFamily;
		this->color = color;
		this->dinamic = dinamic;
		SetLabelText(text, fontFamily);
	}

	void SetLabelText(std::string text , std::string fontFamily) {
		SDL_Surface* surface = TTF_RenderText_Blended(Game::asset_manager->GetFont(fontFamily), text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture, NULL , NULL , &position.w , &position.h);
	}

	//void SetDinamicText(std::string text, std::string fontFamily) {
	//	SDL_Surface* surface = TTF_RenderText_Solid(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
	//	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);		
	//	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	//	SDL_FreeSurface(surface);
	//}
	void Update(float deltaTime) override {
		if (dinamic) {
			text = "asd";
			SetLabelText(text, fontFamily);
		}
	}

	void Render() override {
		FontManager::Draw(texture, position);
		if (dinamic)
		{
			SDL_DestroyTexture(texture);
		}
			
	}
};

#endif
