//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//astarchasehero.cpp
#include "astarchasehero.h"
#include "game.h"
#include "entity.h"
#include "gamerules.h"
#include <cstdlib>
#include <iostream>

AStarChaseHero::AStarChaseHero() {
}

AStarChaseHero::~AStarChaseHero() {
}

Direction AStarChaseHero::getMoveDirection(Game* game, Entity* entity) {
    	Entity* target = findClosestHero(game, entity);
  	if (target == nullptr) { // no Hero entity exists
  		return Direction::NONE;
  	}
  	std::vector<Node*> openNode; //to store all nodes to be evaluated
  	std::vector<Node*> closedNode; //to store all nodes already evaluated
  	bool findPath = false; //check if path exists
	openNode.push_back(create_Node(entity->getPosition())); //add the start node
	while ((int)openNode.size() != 0) {
		Node* current = findLowestF(openNode, closedNode); //node in openNode with the lowest f, erase from openNode and add to closedNode
		if (current->pos == target->getPosition()) { //current node is the destination
			findPath = true;
			break;
		}
		updateNode(game, entity, current, Direction::UP, target->getPosition(), openNode, closedNode);
		updateNode(game, entity, current, Direction::DOWN, target->getPosition(), openNode, closedNode);
		updateNode(game, entity, current, Direction::LEFT, target->getPosition(), openNode, closedNode);
		updateNode(game, entity, current, Direction::RIGHT, target->getPosition(), openNode, closedNode);

		
	}

	
	  if (findPath) {
		Direction dir = getDirectionFromClosedNode(closedNode);
		for (Node* elem : openNode) {
			delete elem;
		}
		for (Node* elem : closedNode) {
			delete elem;
		}
		return dir;
	}
	else { //no path exists
		for (Node* elem : openNode) {
			delete elem;
		}
		for (Node* elem : closedNode) {
			delete elem;
		}
		return Direction::NONE;
		} 
}

bool AStarChaseHero::isUser() const {
	return false;
}

Entity* AStarChaseHero::findClosestHero(const Game* game, const Entity* entity) {
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

//create a dynamically allocated Node
Node* AStarChaseHero::create_Node(Position pos, int f, int g, int h, Node* prev) {
	Node* node = new Node;
	node->pos = pos;
	node->f = f;
	node->g = g;
	node->h = h;
	node->prev = prev;
	return node;
}

// find the node with lowest f in openNode, remove it from openNode and add it to closedNode
Node* AStarChaseHero::findLowestF(std::vector<Node*>& openNode, std::vector<Node*>& closedNode) {
	std::vector<Node*>::const_iterator result;
	int min = 0;
	Node* minNode = nullptr;
	for (std::vector<Node*>::const_iterator it = openNode.cbegin(); it != openNode.cend(); ++it) {
		if (min == 0) {
			min = (*it)->f;
			minNode = (*it);
			result = it;
		}
		if ((*it)->f < min) {
			min = (*it)->f;
			minNode = (*it);
			result = it;
		}
	}
	closedNode.push_back(*result);
	openNode.erase(result);
	return minNode;
}
	
//find a node according to its Posotion and return its index within the vector<Node*>
//return -1 if not found
int AStarChaseHero::findNode(Position pos, std::vector<Node*>& nodes) {
	int index;
	bool found = false;
	for (int i = 0; i < (int)nodes.size(); i++) {
		if (nodes[i]->pos == pos) {
			index = i;
			found = true;
			break;
		}
	}
	if (found) {
		return index;
	}
	else {
		return -1;
	}
}

// update a neighbour node
// skip the node if it cannot be moved onto or if it's in closedNode
// update fields of the node if it's already in openNode and new path to it has smaller f
// add the node to openNode if it's neither in openNode or closedNode
void AStarChaseHero::updateNode(Game* game, Entity* entity, Node* current, Direction dir, Position target, std::vector<Node*>& openNode, std::vector<Node*>& closedNode) {
	Position pos = current->pos.displace(dir);
	int indexOpen = findNode(pos, openNode);
	int indexClosed = findNode(pos, closedNode);
	if (!game->getGameRules()->allowMove(game, entity, current->pos, pos) || indexClosed != -1) { //movement not allowed or it's found in closedNode
		return;
	}
	else if (indexOpen != -1) { //found in openNode
		int g = current->g + 1;
		if (g < openNode[indexOpen]->g) { //new path to it is shorter
			openNode[indexOpen]->g = g;
			openNode[indexOpen]->f = openNode[indexOpen]->g + openNode[indexOpen]->h;
			openNode[indexOpen]->prev = current;
		}
		return;
	}
	else { //can be move onto, not found in openNode nor closedNode
		Node* neighbour = create_Node(pos);
		neighbour->prev = current;
		neighbour->g = current->g + 1;
		neighbour->h = neighbour->pos.distanceFrom(target);
		neighbour->f = neighbour->g + neighbour->h;
		openNode.push_back(neighbour);
	}
}

//get movement direction from closedNode if path is found
Direction AStarChaseHero::getDirectionFromClosedNode(std::vector<Node*>& closedNode) {
	Node* tar = closedNode.back();
	if (tar->prev == nullptr) { //source is destination (should not happen)
		return Direction::NONE;
	}
	while (tar->prev->prev != nullptr) {
		tar = tar->prev;
	}
	Position ori = tar->prev->pos;
	Position after = tar->pos;
	if (ori.displace(Direction::UP) == after) {
		return Direction::UP;
	}
	else if (ori.displace(Direction::DOWN) == after) {
		return Direction::DOWN;
	}
	else if (ori.displace(Direction::LEFT) == after) {
		return Direction::LEFT;
	}
	else {
		return Direction::RIGHT;
	}
}
