#include "Level.h"
#include "Bomb.h"
#include "Explosion.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>

Level::Level(int tilesize) : tilesize(tilesize) {
	player = new Player(sf::Vector2f(48,48), tilesize, EntityType::PLAYER);
	entities.push_back(player);
}

Level::~Level() {
	for (int i = 0; i < entities.size(); i++)
		delete entities[i];
}

void Level::update() {
	for (int i = 0; i < entities.size(); i++)
		entities[i]->update();

	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->getType() == EntityType::BOMB) { // bomb exploded check
			Bomb* b = (Bomb*)entities[i];
			if (b->exploded()) {
				delete entities[i];
				entities.erase(entities.begin() + i);
				break;
			}
		}

		if (entities[i]->getType() == EntityType::EXPLOSION) { // explosion exploded check
			Explosion* e = (Explosion*)entities[i];
			if (e->exploded()) {
				delete entities[i];
				entities.erase(entities.begin() + i);
				break;
			}
		}
	}
}

void Level::addEntity(Entity* e) {
	entities.push_back(e);
}

int Level::entityCount(EntityType type) {
	int res = 0;
	for (int i = 0; i < entities.size(); i++)
		if (entities[i]->getType() == type) res++;

	return res;
}

const Tile& Level::findTile(float x, float y) {
	if (x < getWidth() && x > -1 && y < getHeight() && y > -1)
		return tiles[(int)(x / tilesize + (y / tilesize) * width)];
}

Entity* Level::findEntity(float x, float y) {
	/*for (int i = 0; i < entities.size(); i++)
		if (entities[i]->getPosition().x == x && entities[i]->getPosition().y == y)
			return entities[i];

	return nullptr;*/
	return findEntityAt(x, y, 0);
}

Entity* Level::findEntityAt(float x, float y, int index) {
	float margin = 5.0f;

	for (int i = index; i < entities.size(); i++)
		if (entities[i]->getPosition().x + tilesize - margin > x && entities[i]->getPosition().x + margin < x + tilesize &&
			entities[i]->getPosition().y + tilesize - margin > y && entities[i]->getPosition().y + margin < y + tilesize)
			return entities[i];

	return nullptr;
}

void Level::loadLevel(const char* path) {
	std::ifstream file;
	std::stringstream ss;
	file.open(path);
	ss << file.rdbuf();
	file.close();
	
	std::string data = ss.str();

	int x = 0, y = 0;
	for (int i = 0; i < data.length(); i++) {
		char c = data[i];
		if (c == '0') {
			tiles.emplace_back(sf::Vector2f(x++ * tilesize, y * tilesize), sf::Vector2f(0, 1), tilesize, TileType::WALL);
		}
		else if (c == '1') {
			tiles.emplace_back(sf::Vector2f(x++ * tilesize, y * tilesize), sf::Vector2f(0, 0), tilesize, TileType::AIR);
		}
		else if (c == '\n') {
			x = 0;
			y++;
		}
	}
	width = x;
	++height = y;
}