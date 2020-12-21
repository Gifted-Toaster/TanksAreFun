#include <fstream>
#include "./Game.h";
#include "./EntityManager.h";
#include "./TileComponent.h";
#include "./Map.h";

// Mapsize Y and X is the length and width of the datas inside the * .map file
// You must hardcode the *.map file as double digit numbers with ',' inbetween them
// SourceRect X and Y is a reference for the position of the texture in the texture pack which passed with the constructor and stored in textureId

extern EntityManager manager;

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	// Sets the Game's mapsize

	std::fstream mapFile;
	mapFile.open(filePath);
	
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			char ch;
			// gets the first digit
			mapFile.get(ch);
			// converts to int
			int sourceRectY = atoi(&ch) * tileSize;
			// gets the second digit
			mapFile.get(ch);
			// same as above
			int sourceRectX = atoi(&ch) * tileSize;
			AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
			// skips the ',' between the numbers
			mapFile.ignore();		
		}
	}
	mapFile.close();
}

void Map::LoadMap(sol::table* fileData, int width, int height)
{
	//  Loading everything into this table
	int width_index = 0;
	int height_index = 0;

	fileData->for_each([&](sol::object const& key, sol::object const& value) {
		int a = 0, b = 0;
		int current_key = key.as<int>(), current_value = value.as<int>();
		// If our iterator's key is reached width that means we have to start addressing another row
		// So if we subtract the current row index+1 times the width and we get 1 that means we have completed a row so we have to address a new one  // 11-((0+1)*10) - 21-((1+1))*10)
		if (current_key - (height_index+1)*width == 1) {
			height_index++;
		}

		// These two digits will says the starting pixel of our texture at its picture array so we have to split the input into two digits
		int sourceRectY = current_value / 10;
		int sourceRectX = current_value % 10;

		// our current col index will be the iterator-1 minus the row counter times 10
		width_index = (current_key - 1)-(height_index * 10);
		/* Add tile takes 4 params:
			- coords for the textures starting place in their pallette
			- coords for where their rectangle will start on the screen
		*/
		AddTile(sourceRectX, sourceRectY, width_index * (scale * tileSize), height_index * (scale * tileSize));
	});

}

void Map::AddTile(int sourceX, int sourceY, int x, int y) {
		// Calls with the entity constructor format
		Entity& newTile(manager.AddEntity("Tile" , TILEMAP_LAYER));
		// Gives our tile a tilecomponent which draws the texture on it
		newTile.AddComponent<TileComponent>(sourceX, sourceY, x, y, tileSize, scale, textureId);
}

Map::Map(std::string textureId, int scale, int tileSize) {
	this->textureId = textureId;
	this->scale = scale;
	this->tileSize = tileSize;
}