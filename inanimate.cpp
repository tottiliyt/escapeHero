//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//inanimate.cpp
#include "inanimate.h"

Inanimate::Inanimate() {
}

Inanimate::~Inanimate() {
}

Direction Inanimate::getMoveDirection(Game* game, Entity* entity) {
	(void)game; //to avoid unused parameter warning when compiling
	(void)entity;
	return Direction::NONE;
}

bool Inanimate::isUser() const {
	return false;
}