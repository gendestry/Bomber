#pragma once
#include <vector>
#include "Entity.h"
#include "Bomb.h"

class Player : public Entity {
private:
	int maxBombs;
	int bombRange;
	int bombDamage;
	float speed;

	sf::Vector2f velocity;
public:
	Player(sf::Vector2f pos, int size, EntityType type);
	~Player();

	void update() override;
	void processInput(sf::Keyboard::Key k, bool pressed);
private:
	void placeBomb();
	bool collission();
};