#include "Entity.h"
#include "Level.h"

Level* Entity::level = nullptr;

Entity::Entity(sf::Vector2f pos, int size, EntityType type) : position(pos), tilesize(size), type(type) {

}