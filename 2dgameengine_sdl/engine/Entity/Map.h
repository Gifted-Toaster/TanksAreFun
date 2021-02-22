#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
#include "./Entity/Component/ComponentInit.h"

//extern ColliderComponent coll;

class Map {
private:
	std::string textureId;
	// Scale for the texture size
	int scale;
	// Size for the tiles
	int tileSize;

	//std::pair<int, int> convert_value_into_source(int value);
public:
	// Initialize a map with a texture pack id , a scale and
	Map(std::string textureId, int scale, int tileSize);
	~Map();
	
	// Load the whole map by reading the source txt file
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void LoadMap(sol::table* filePath, int mapSizeX, int mapSizeY, std::map<int, TileColliderInit> colliderHolder);
	// Add a tile to the map
	void AddTile(int sourceX, int sourceY, int x, int y);
	void AddTileWithCollider(int sourceX, int sourceY, int x, int y, TileColliderInit init);
};

#endif