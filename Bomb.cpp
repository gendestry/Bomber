#include "Bomb.h"
#include "Level.h"
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;

Bomb::Bomb(sf::Vector2f pos, int size, EntityType type, int range, int damage) : Entity(pos, size, type), range(range), damage(damage), exp(false) {
	start = Clock::now();
}

void Bomb::update() {
	auto t2 = Clock::now();

	if (exp || std::chrono::duration_cast<std::chrono::milliseconds>(t2 - start).count() > duration) {
		explode();
	}
}

void Bomb::explode() { // finds only one entity (findAt returns only 1)
	exp = true;
	addExplosion(position);

	bool takenDamage = false;
	int& dmg = damage;

	auto process = [&takenDamage, dmg](Entity* e){
		if (e != nullptr) {
			if (e->getType() == EntityType::BOMB) {
				Bomb* b = (Bomb*)e;
				b->setExplode();
			}
			if (e->getType() == EntityType::PLAYER) {
				if (!takenDamage) {
					e->takeDamage(dmg);
					takenDamage = true;
				}
			}
		}
	};



	const std::vector<Entity*>& entities = level->getEntities();

	// right side
	int temp = range;
	while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;
		if (level->getWidth() < position.x + offset || level->findTile(position.x + offset, position.y).getType() == TileType::WALL)
			break;
		
		Entity* e = level->findEntity(position.x + offset, position.y);
		process(e);

		addExplosion({ position.x + offset, position.y });
		temp--;
	}

	// left side
	temp = range;
	while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;
		if (position.x - offset < 0 || level->findTile(position.x - offset, position.y).getType() == TileType::WALL)
			break;

		Entity* e = level->findEntity(position.x - offset, position.y);
		process(e);

		addExplosion({ position.x - offset, position.y });
		temp--;
	}

	// bottom side
	temp = range;
	while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;
		if (level->getHeight() < position.y + offset || level->findTile(position.x, position.y + offset).getType() == TileType::WALL)
			break;
		
		Entity* e = level->findEntity(position.x, position.y + offset);
		process(e);

		addExplosion({ position.x, position.y + offset });
		temp--;
	}

	// top side
	temp = range;
	while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;
		if (position.y - offset < 0 || level->findTile(position.x, position.y - offset).getType() == TileType::WALL)
			break;
		
		Entity* e = level->findEntity(position.x, position.y - offset);
		process(e);
		
		addExplosion({ position.x, position.y - offset });
		temp--;
	}
}

void Bomb::explodeOneDir(sf::Vector2f pos) {
	/*
	(-1, 0) - levo:  pos.x - offset < 0
	( 1, 0) - desno: pos.x + offset > level->getWidth()
	( 0,-1) - gor:   pos.y - offset < 0
	( 0, 1) - dol:   pos.y + offset > level->getHeight()
	*/
	
	const std::vector<Entity*>& entities = level->getEntities();
	int temp = range;
	int start = 0;

	while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;

		Entity* e = level->findEntity(pos.x, pos.y);

		temp--;
	}
	/*while (temp > 0) {
		int offset = (range - temp + 1) * tilesize;
		if (level->getWidth() < pos.x || level->findTile(pos.x, pos.y).getType() == TileType::WALL)
			break;

		Entity* e = level->findEntity(pos.x, pos.y);
		if (e != nullptr) {
			if (e->getType() == EntityType::BOMB) {
				Bomb* b = (Bomb*)e;
				b->setExplode();
			}

		}
		addExplosion({ pos.x, pos.y });
		//std::cout << "Right: " << position.x + offset << ", " << position.y << "\n";	// spawn fire and damage stuff
		temp--;
	}*/
}

void Bomb::addExplosion(sf::Vector2f pos) {
	Explosion* exp = new Explosion(pos, tilesize, EntityType::EXPLOSION);
	level->addEntity(exp);
}