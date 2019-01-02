#include "Explosion.h"
#include "Level.h"

typedef std::chrono::high_resolution_clock Clock;

Explosion::Explosion(sf::Vector2f pos, int size, EntityType type) : Entity(pos, size, type), exp(false) {
	start = Clock::now();
}

void Explosion::update() {
	auto t2 = Clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start).count() > duration) {
		exp = true;
	}
}