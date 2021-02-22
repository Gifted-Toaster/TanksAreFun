#pragma once
#ifndef LOGDATA_H
#define LOGDATA_H

#include <vector>
#include <string>
#include <map>
// LOG data

typedef struct LogData {
public:

	unsigned int activeEntity;
	unsigned int inactiveEntity;
	unsigned int entity_with_collision;
	
	LogData() {
		activeEntity = 0;
		inactiveEntity = 0;
		entity_with_collision = 0;
	};
};

#endif LOGDATA_H
