#include "Application.h"

Application::Application(int width, int height, const char* title)
	: width(width), height(height), title(title) {
	
	window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	level = new Level(tilesize);

	level->loadLevel("levels/level1.lvl");

	Entity::setLevel(level);
	initSprites();
}

Application::~Application() {
	delete level;
	delete window;
}

void Application::initSprites() {
	textures.resize((int)TextureID::ENUM_END);
	sprites.resize((int)SpriteID::ENUM_END);

	sf::Texture tex;
	tex.loadFromFile("res/tiles-48.png");
	textures[(int)TextureID::TILES] = tex;
	tex.loadFromFile("res/entities-48.png");
	textures[(int)TextureID::ENTITIES] = tex;

	sf::Sprite sp;
	sp.setTexture(textures[(int)TextureID::TILES]);
	sp.setTextureRect(sf::IntRect(0, 2 * tilesize, tilesize, tilesize));
	sprites[(int)SpriteID::GRASS] = sp;
	sp.setTextureRect(sf::IntRect(0, 3 * tilesize, tilesize, tilesize));
	sprites[(int)SpriteID::WALL] = sp;

	sp.setTexture(textures[(int)TextureID::ENTITIES]);
	sp.setTextureRect(sf::IntRect(0, 0 * tilesize, tilesize, tilesize));
	sprites[(int)SpriteID::BOMB] = sp;
	sp.setTextureRect(sf::IntRect(0, 1 * tilesize, tilesize, tilesize));
	sprites[(int)SpriteID::EXPLOSION] = sp;
	sp.setTextureRect(sf::IntRect(0, 2 * tilesize, tilesize, tilesize));
	sprites[(int)SpriteID::PLAYER] = sp;
}

void Application::run() {
	while (window->isOpen()) {
		processEvents();
		level->update();
		render();
	}
}

void Application::render() {
	/*static float xOffset = 0, yOffset = 0;
	if (level->getWidth() + xOffset > width && level->getPlayer()->getPosition().x + xOffset > tilesize + width / 2) {
		xOffset--;
	}
	else if (xOffset < 0 && level->getPlayer()->getPosition().x + xOffset < (width / 2) - tilesize) {
		xOffset++;
	}*/

	// Actual rendering
	window->clear();
	
	// render the ground
	const std::vector<Tile>& tiles = level->getTiles();
	for (int i = 0; i < tiles.size(); i++) {
		sf::Vector2f pos(tiles[i].getPosition());

		if (tiles[i].getType() == TileType::AIR) {
			sprites[(int)SpriteID::GRASS].setPosition(pos);
			window->draw(sprites[(int)SpriteID::GRASS]);
		}
		else {
			sprites[(int)SpriteID::WALL].setPosition(pos);
			window->draw(sprites[(int)SpriteID::WALL]);
		}
	}

	// render entities
	const std::vector<Entity*>& entities = level->getEntities();
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->getType() == EntityType::BOMB) {
			sprites[(int)SpriteID::BOMB].setPosition(entities[i]->getPosition());
			window->draw(sprites[(int)SpriteID::BOMB]);
		}
		else if (entities[i]->getType() == EntityType::EXPLOSION) {
			sprites[(int)SpriteID::EXPLOSION].setPosition(entities[i]->getPosition());
			window->draw(sprites[(int)SpriteID::EXPLOSION]);
		}
		else if (entities[i]->getType() == EntityType::PLAYER) {
			sprites[(int)SpriteID::PLAYER].setPosition(entities[i]->getPosition());
			window->draw(sprites[(int)SpriteID::PLAYER]);
		}
	}

	window->display();
}

void Application::processEvents() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			window->close();

		if (event.type == sf::Event::KeyPressed)
			level->getPlayer()->processInput(event.key.code, true);
		else if(event.type == sf::Event::KeyReleased)
			level->getPlayer()->processInput(event.key.code, false);
	}
}

/*

store x,y where damage occured, and if from bomb


*/