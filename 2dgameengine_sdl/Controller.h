#pragma once


static enum CONTROLLER_STATE { MENU, IN_GAME, INACTIVE };

class Controller {
	public:
		CONTROLLER_STATE state;
		Controller() { state = INACTIVE; };
		virtual void Update() {};
		virtual void Initialize(CONTROLLER_STATE state) {};
};