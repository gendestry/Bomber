#pragma once
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Tile.h"

class Level {
private:
	int width, height;
	int tilesize;

	std::vector<Tile> tiles;
	std::vector<Entity*> entities;

	Player* player;
public:
	Level(int tilesize);
	~Level();

	void loadLevel(const char* path);
	const Tile& findTile(float x, float y);
	Entity* findEntity(float x, float y);
	Entity* findEntityAt(float x, float y, int index);

	void update();
	void addEntity(Entity* e);
	int entityCount(EntityType type);

	inline Player* getPlayer() { return player; }

	inline const int getWidth() { return width * tilesize; }
	inline const int getHeight() { return height * tilesize; }
	inline const std::vector<Tile>& getTiles() { return tiles; }
	inline const std::vector<Entity*>& getEntities() { return entities; }
};