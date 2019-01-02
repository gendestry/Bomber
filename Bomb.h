#pragma once
#include "Entity.h"
#include "Explosion.h"
#include <chrono>

class Bomb : public Entity {
private:
	int damage;
	int range;
	int duration = 1500;

	bool exp;
	std::chrono::steady_clock::time_point start;
public:
	Bomb(sf::Vector2f pos, int size, EntityType type, int range, int damage);

	void update() override;
	void setExplode() { exp = true; }
	inline const bool exploded() const { return exp; }
private:
	void addExplosion(sf::Vector2f pos);
	void explode();
	void explodeOneDir(sf::Vector2f pos);
};

