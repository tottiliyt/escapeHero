//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//wall.cpp
#include "wall.h"

Wall::Wall() {
}

Wall::~Wall() {
}

MoveResult Wall::checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const {
	(void)entity; //to avoid unused parameter warning when compiling
	(void)fromPos;
	(void)tilePos;
	return MoveResult::BLOCK;
}

bool Wall::isGoal() const {
	return false;
}

std::string Wall::getGlyph() const {
	return "#";
}