#pragma once
#include "Entity.h"
#include <chrono>

class Explosion : public Entity {
private:
	const int duration = 400;
	bool exp;
	std::chrono::steady_clock::time_point start;
public:
	Explosion(sf::Vector2f pos, int size, EntityType type);

	void Explosion::update();
	inline const bool exploded() const { return exp; }
};

