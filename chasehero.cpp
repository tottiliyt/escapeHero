//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//chasehero.cpp
#include "chasehero.h"
#include "game.h"
#include "entity.h"
#include "gamerules.h"

ChaseHero::ChaseHero() {
}

ChaseHero::~ChaseHero() {
}

Direction ChaseHero::getMoveDirection(Game* game, Entity* entity) {
	Entity* target = findClosestHero(game, entity);
	if (target == nullptr) { // no Hero entity exists
		return Direction::NONE;
	}
	int xdiff = target->getPosition().getX() - entity->getPosition().getX(); //horizontal difference
	int ydiff = target->getPosition().getY() - entity->getPosition().getY(); //vertical difference
	int xabs = xdiff;
	int yabs = ydiff;
	if (xabs < 0) {
		xabs = -xabs;
	}
	if (yabs < 0) {
		yabs = -yabs;
	}
	if (xabs >= yabs) { //movement direction is horizontal
		if (xdiff > 0) { //right movement
			if (canMove(game, entity, entity->getPosition(), Direction::RIGHT)) { //right movement is allowed
				return Direction::RIGHT;
			}
			else { //right movement is not allowed
				if (ydiff > 0) { //down movement
					if (canMove(game, entity, entity->getPosition(), Direction::DOWN)) { //down movement is allowed
						return Direction::DOWN;
					}
					else {
						return Direction::NONE;
					}
				}
				else if (ydiff < 0) { // up movement
					if (canMove(game, entity, entity->getPosition(), Direction::UP)) { //up movement is allowed
						return Direction::UP;
					}
					else {
						return Direction::NONE;
					}
				}
				else { //ydiff == 0
					return Direction::NONE;
				}
			}
		}
		else { //left movement
			if (canMove(game, entity, entity->getPosition(), Direction::LEFT)) { //left movement is allowed
				return Direction::LEFT;
			}
			else { //left movement is not allowed
				if (ydiff > 0) { //down movement
					if (canMove(game, entity, entity->getPosition(), Direction::DOWN)) { //down movement is allowed
						return Direction::DOWN;
					}
					else {
						return Direction::NONE;
					}
				}
				else if (ydiff < 0) { //up movement
					if (canMove(game, entity, entity->getPosition(), Direction::UP)) { //up movement is allowed
						return Direction::UP;
					}
					else {
						return Direction::NONE;
					}
				}
				else { //ydiff == 0
					return Direction::NONE;
				}
			}
		}
	}
	else { //movement direction is vertical
		if (ydiff > 0) { //down movement
			if (canMove(game, entity, entity->getPosition(), Direction::DOWN)) { //down movement is allowed
				return Direction::DOWN;
			}
			else { //down movement is not allowed
				if (xdiff > 0) { //right movement
					if (canMove(game, entity, entity->getPosition(), Direction::RIGHT)) { //right movement is allowed
						return Direction::RIGHT;
					}
					else {
						return Direction::NONE;
					}
				}
				else if (xdiff < 0) { //left movement
					if (canMove(game, entity, entity->getPosition(), Direction::LEFT)) { //left movement is allowed
						return Direction::LEFT;
					}
					else {
						return Direction::NONE;
					}
				}
				else { //xdiff == 0
					return Direction::NONE;
				}
			}
		}
		else { //up movement
			if (canMove(game, entity, entity->getPosition(), Direction::UP)) { //up movement is allowed
				return Direction::UP;
			}
			else { //up movement is not allowed
				if (xdiff > 0) { //right movement
					if (canMove(game, entity, entity->getPosition(), Direction::RIGHT)) { //right movement is allowed
						return Direction::RIGHT;
					}
					else {
						return Direction::NONE;
					}
				}
				else if (xdiff < 0) { //left movement
					if (canMove(game, entity, entity->getPosition(), Direction::LEFT)) { //left movement is allowed
						return Direction::LEFT;
					}
					else {
						return Direction::NONE;
					}
				}
				else { //xdiff == 0
					return Direction::NONE;
				}
			}
		}
	}
}

bool ChaseHero::isUser() const {
	return false;
}

Entity* ChaseHero::findClosestHero(Game* game, Entity* entity) {
	std::vector<Entity*> heros = game->getEntitiesWithProperty('h');
	if ((int)heros.size() == 0) { //no entity has hero property, which is unlikely to happen
		return nullptr;
	}
	Position ori = entity->getPosition();
	int min_distance = 0;
	Entity* target_hero = nullptr;
	for (std::vector<Entity*>::const_iterator it = heros.cbegin(); it != heros.cend(); ++it) {
		Position tar = (*it)->getPosition();
		if (ori == tar) { //if the argument entity has hero property, which should not happen
			continue;
		}
		if (min_distance == 0) { //no distance has been calculated
			min_distance = ori.distanceFrom(tar);
			target_hero = *it;
		}
		int distance = ori.distanceFrom(tar);
		if (distance < min_distance) {
			min_distance = distance;
			target_hero = *it;
		}
	}
	return target_hero;
}

bool ChaseHero::canMove(Game* game, Entity* entity, Position pos, Direction dir) {
	Position tar = pos.displace(dir);
	return game->getGameRules()->allowMove(game, entity, pos, tar);
}