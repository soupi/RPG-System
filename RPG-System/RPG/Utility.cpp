#include "Utility.h"
#include "Tile.h"

// load font from filename
void LoadFont(sf::Font& font, const char* filename)
{
	if (!font.loadFromFile(filename))
	{
		std::cerr << "unable to load from file";
		exit(EXIT_FAILURE);
	}
}
// load texture from filename
void loadTexture(sf::Texture& texture, const std::string& filename)
{
	texture.create(TILE_SIZE, TILE_SIZE);
	if (!texture.loadFromFile("Grass.png"))
	{
		std::cerr << "fail to load texture from: " << filename;
		exit(EXIT_FAILURE);
	}
	texture.setRepeated(true);
}