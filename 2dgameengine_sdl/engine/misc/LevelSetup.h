#pragma once

#include <sol.hpp>
#include "./Constans.h"

class Entity;
class EntityManager;
class AssetManager;
class Map;

// Contains a two methods for loading a level with all of its components
class LevelSetup
{
public:
	/*Contains : 
		- AssetLoading
		- MapLoading
		- EntityLoading
	*/
	static void LoadLevel(Levels levelNumber, Map* map);
	// Loading the presets for the level
	static void LoadPresets(Levels levelNumber);
};
