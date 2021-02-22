#pragma once

#include "Controller.h"
#include <SDL.h>
#include <map>
#include <string>
#include <vector>

extern Controller;

class Keyboard : public Controller
{
private:
	std::map<std::string, SDL_Keycode> list_of_instructions;
	// TODO gyorsbillentyuk
public:
	Keyboard() {
	}

	void SetUpInstructionList() {
		list_of_instructions.emplace("camera_up", SDLK_w);
		list_of_instructions.emplace("camera_right", SDLK_d);
		list_of_instructions.emplace("camera_left", SDLK_a);
		list_of_instructions.emplace("camera_down",SDLK_s);
		list_of_instructions.emplace("focus",SDLK_SPACE);
	}

	void Initialize(CONTROLLER_STATE state) override {
		this->state = state;
		SetUpInstructionList();
	}

	void Update() override {
		return;
	}
};

