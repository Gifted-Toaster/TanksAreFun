#ifndef MAP_H
#define MAP_H

#include <string>

extern EntityManager manager;

class Map {
private:
	std::string textureId;
	// Scale for the texture size
	int scale;
	// Size for the tiles
	int tileSize;
public:
	// Initialize a map with a texture pack id , a scale and
	Map(std::string textureId, int scale, int tileSize);
	~Map();
	// Load the whole map by reading the source txt file
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void LoadMap(sol::table* filePath, int mapSizeX, int mapSizeY);
	// Add a tile to the map
	void AddTile(int sourceX, int sourceY, int x, int y);
};

#endif