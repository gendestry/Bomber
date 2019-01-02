#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Level.h"
#include "Tile.h"
#include "Player.h"

class Application {
private:
	sf::RenderWindow* window;
	int width;
	int height;
	const char* title;
	const int tilesize = 48;

	Level* level;

	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;

	enum class TextureID : int {
		TILES,
		ENTITIES,
		ENUM_END
	};
	enum class SpriteID : int {
		GRASS,
		WALL,

		BOMB,
		EXPLOSION,
		PLAYER,
		
		ENUM_END
	};
public:
	Application(int width, int height, const char* title);
	~Application();

	void run();
private:
	void initSprites();
	void processEvents();
	void render();
};