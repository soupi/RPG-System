#pragma once

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

void LoadFont(sf::Font&, const char* filename);
void loadTexture(sf::Texture& texture, const std::string& filename);

