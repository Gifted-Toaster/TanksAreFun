#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "Constans.h"
#include "Entity.h"
#include "Game.h"
#include "LogData.h"
#include <iostream>


class LogWindow
{
private:
	std::map<std::string , std::pair<std::string, int>> dat;
	TTF_Font* Sans = TTF_OpenFont("../assets/fonts/charriot.ttf", 12); //this opens a font style and sets a size
	SDL_Color White = { 255, 255, 255 };

public:
	LogWindow(int width, int height);
	LogWindow() {};
	SDL_Window* window;
	SDL_Renderer* renderer;
	int numberOfActiveLogs() const;
	void WriteLog(int position, std::pair<std::string, int> current);
	void RenderLog();
	void UpdateLog(std::string type , std::string title, int value);
	void Destroy();
};

#endif

