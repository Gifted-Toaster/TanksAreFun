#pragma once

#include "./Player.h"

Player* Player::instance = 0;


Player* Player::LoadPlayer() {
	if (!instance) {
		instance = new Player();
	}
	return instance;
}
