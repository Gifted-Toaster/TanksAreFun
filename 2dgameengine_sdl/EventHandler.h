#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include <SDL.h>
#include "Constans.h"


/* The event handler decides what controller which corresponding action is calling based on the SDL event type and the controllers state

 - STATES :
	-INACTIVE
	-MENU
	-IN_GAME
 - EVENT TYPE:
	- MOUSE ( LEFT, RIGHT CLICK..)
	- KEYBOARD ( set_of_instuctions )

*/
class EventHandler {
public:

	// After we got our mouse state this function calls gets what mouse button was used then calls its action
	static const void GetAction_Mouse(SDL_Event& user_input, CONTROLLER_STATE state ) {
		if (state == IN_GAME) {
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				SDL_Log("Mouse Button 1 (left) is pressed.");
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				SDL_Log("Mouse Button 3 (right) is pressed.");
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
				SDL_Log("Mouse Button 2 (middle) is pressed.");
			}
		}
		if (state == MENU) {
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				SDL_Log("Mouse Button 1 (left) is pressed.");
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				SDL_Log("Mouse Button 3 (right) is pressed.");
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
				SDL_Log("Mouse Button 2 (middle) is pressed.");
			}
		}
	}

	// First this function check what state our mouse in , then calls GetMouseAction()
	static const void HandleUserInput_Mouse(SDL_Event& user_input, CONTROLLER_STATE state) 
	{
		if (state == INACTIVE)
			return;
		else
			GetAction_Keyboard(user_input, state);
	}

	// Same as mouse but with the keyboard
	static const void GetAction_Keyboard( SDL_Event& user_input, CONTROLLER_STATE state )
	{
		if (state == IN_GAME) {
			switch (user_input.key.keysym.sym) {
				case SDLK_s:
					Game::MoveCamera(UP);
					break;
				case SDLK_w:
					Game::MoveCamera(DOWN);
					break;
				case SDLK_a:
					Game::MoveCamera(LEFT);
					break;
				case SDLK_d:
					Game::MoveCamera(RIGHT);
					break;
				case SDLK_SPACE:
					break;
			}
		}
		else if (state == MENU) {
			switch (user_input.key.keysym.sym) {
				case SDLK_SPACE:
					Game::Select();
					break;
				case SDLK_w:
					Game::StepUp();
					break;
				case SDLK_d:
					Game::StepDown();
					break;
			}
		}

	}

	// Same as mouse but with the keyboard
	static const void HandleUserInput_Keyboard(SDL_Event& user_input, CONTROLLER_STATE state)
	{
		if (state == INACTIVE)
			return;
		else
			GetAction_Keyboard(user_input, state);
	}

	// Check whether we have any user input queued
	static const bool isThereUserInput(SDL_Event* user_input_que) {
		return SDL_PollEvent(user_input_que);
	}

	EventHandler() {}

};

