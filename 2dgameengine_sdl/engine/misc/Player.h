#pragma once

class Player
{
private:
	static Player* instance;
	Player() {};

public:
	static Player* LoadPlayer();

	void Update() {
		return;
		//cursor->Update();
		//keyboard->Update();
	}
	
};
