#include "Player.h"
#include "Level.h"
#include <iostream>

Player::Player(sf::Vector2f pos, int size, EntityType type) : Entity(pos, size, type), velocity({0,0}) {
	maxBombs = 2;
	bombRange = 3;
	bombDamage = 1;

	health = 3;

	speed = 0.4f;
	// https://jonathanwhiting.com/tutorial/collision/
}

Player::~Player() {}

void Player::update() {
	auto oldpos = position;

	position.x += velocity.x;
	if (collission()) position.x = oldpos.x;

	position.y += velocity.y;
	if (collission()) position.y = oldpos.y;
}

bool Player::collission() {
	static float margin = 5.0f;
	const std::vector<Tile>& tiles = level->getTiles();

	auto& pos = position;
	
	for (int i = 0; i < tiles.size(); i++) {
		if (tiles[i].getType() == TileType::AIR) continue;
		auto& tpos = tiles[i].getPosition();

		if (pos.x + tilesize - margin > tpos.x && pos.x + margin < tpos.x + tilesize &&
			pos.y + tilesize - margin > tpos.y && pos.y + margin < tpos.y + tilesize) {
			return true;
		}
	}
	return false;
}

void Player::processInput(sf::Keyboard::Key k, bool pressed) {
	static bool canPlace = true;

	switch (k) {
		case sf::Keyboard::A:
			velocity.x = pressed ? -speed : 0.f;
			break;
		case sf::Keyboard::D:
			velocity.x = pressed ? speed : 0.f;
			break;
		case sf::Keyboard::W:
			velocity.y = pressed ? -speed : 0.f;
			break;
		case sf::Keyboard::S:
			velocity.y = pressed ? speed : 0.f;
			break;
		case sf::Keyboard::Space:
			if (canPlace && pressed) {
				placeBomb();
				canPlace = false;
			}
			if (!pressed) 
				canPlace = true;
			break;
		default:
			break;
	}
}

void Player::placeBomb() {
	int numBombs = level->entityCount(EntityType::BOMB);
	if (numBombs >= maxBombs) return;

	float x = (int)position.x - ((int)position.x % tilesize);
	float y = (int)position.y - ((int)position.y % tilesize);

	if ((int)position.x % tilesize > tilesize / 2) { x += tilesize; }
	if ((int)position.y % tilesize > tilesize / 2) { y += tilesize; }

	bool exists = false;
	bool shouldExplode = false;
	const std::vector<Entity*>& entities = level->getEntities();
	for (int i = 0; i < entities.size(); i++)
		if (entities[i]->getPosition().x == x && entities[i]->getPosition().y == y) {
			if (entities[i]->getType() == EntityType::BOMB) {
				exists = true;
				break;
			}
			else if (entities[i]->getType() == EntityType::EXPLOSION) {
				shouldExplode = true;
				break;
			}
		}

	if (!exists) {
		Bomb* b = new Bomb(sf::Vector2f(x, y), tilesize, EntityType::BOMB, bombRange, bombDamage);
		if (shouldExplode) b->setExplode();
		level->addEntity(b);
	}

	std::cout << x << ", " << y << "\n" << position.x << ", " << position.y << ": playah...\n";
}