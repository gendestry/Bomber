#pragma once
#include <SFML/Graphics.hpp>

enum class TileType {
	AIR,
	WALL
};

class Tile {
protected:
	sf::Vector2f position;
	sf::Vector2f texPos;
	int size;
	TileType type;
public:
	Tile(sf::Vector2f pos, sf::Vector2f texpos, int size, TileType type);

	inline const sf::Vector2f getPosition() const { return position; }
	inline const sf::IntRect getTextureRect () const { return sf::IntRect((int)texPos.x * size, (int)texPos.y * size, size, size); }
	inline const TileType getType() const { return type; }
};