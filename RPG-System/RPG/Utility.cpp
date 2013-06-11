#include "Utility.h"
#include "Tile.h"
#include <cmath>

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
	if (!texture.loadFromFile(filename))
	{
		std::cerr << "fail to load texture from: " << filename;
		exit(EXIT_FAILURE);
	}
	texture.setRepeated(true);
}

// ----- min/max functions ------------
float max(float a, float b)
{
        if (a > b)
                return a;
        return b;
}
unsigned max(unsigned a, unsigned b)
{
        if (a > b)
                return a;
        return b;
}
unsigned min(unsigned a, unsigned b)
{
        if (max(a,b) == a)
                return b;
        return a;
}
// ---------------------------------
// round a up or don't (whichever is closeset)
unsigned round(float a)
{
        if (a-unsigned(a) > 0.5)
                return unsigned(a) +1;

        return unsigned(a);
}


sf::Vector2f operator*(int scalar, sf::Vector2f vec)
{
	return sf::Vector2f(scalar*vec.x, scalar*vec.y);
}
sf::Vector2f operator*(const sf::Vector2f u, const sf::Vector2f v)
{
	return sf::Vector2f(u.x * v.x, u.y * v.y);
}

bool isZero(sf::Vector2f vec)
{
	return (vec.x == 0.f && vec.y == 0.f) ? true : false;
}


float distance(sf::Vector2f& u, sf::Vector2f& v)
{
	return sqrt(pow(u.x + v.y, 2) + pow(u.y + v.y, 2));
}