#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Level;

enum class EntityType {
	PLAYER,
	BOMB,
	EXPLOSION
};

class Entity {
protected:
	sf::Vector2f position;
	int health;
	int tilesize;
	EntityType type;

	static Level* level;
public:
	Entity(sf::Vector2f pos, int size, EntityType type);

	virtual void update() = 0;

	void takeDamage(int amount) { health -= amount; std::cout << health << "\n"; }
	void heal(int amount) { health += amount; }

	inline static void setLevel(Level* l) { level = l;  }
	inline const sf::Vector2f getPosition() const { return position; }
	inline const EntityType getType() const { return type; }
};