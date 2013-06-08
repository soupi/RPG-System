#pragma once

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>

void LoadFont(sf::Font&, const char* filename);
void loadTexture(sf::Texture& texture, const std::string& filename);

// utility functions
float max(float a, float b);
unsigned max(unsigned a, unsigned b);
unsigned min(unsigned a, unsigned b);
unsigned round(float a);

sf::Vector2f operator*(int scalar, sf::Vector2f vec);
bool isZero(sf::Vector2f vec);
