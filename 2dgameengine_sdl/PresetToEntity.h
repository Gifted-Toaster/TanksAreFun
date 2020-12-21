#pragma once
#ifndef PRESETTOENTITY_H
#define PRESETTOENTITY_H

#include "./Constans.h"
#include <vector>
#include <string>

class PresetToEntity {
	template <typename T>
	static const T& Convert(ComponentType type, std::vector<std::string> data) {
		switch (type) {
		case TRANSFORM:
			return T;
			break;
		case TILE:
			break;
		case TEXTLABEL:
			break;
		case SPRITE:
			break;
		case KEYBOARD:
			break;
		case COLLIDER:
			break;
		case default:
		}

		return T;
	}
};


#endif
