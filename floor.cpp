//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//floor.cpp
#include "floor.h"

Floor::Floor() {
}

Floor::~Floor() {
}

MoveResult Floor::checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const {
	(void)entity; //to avoid unused parameter warning when compiling
	(void)fromPos;
	(void)tilePos;
	return MoveResult::ALLOW;
}

bool Floor::isGoal() const {
	return false;
}

std::string Floor::getGlyph() const {
	return ".";
}