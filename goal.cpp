//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//goal.cpp
#include "goal.h"

Goal::Goal() {
}

Goal::~Goal() {
}

MoveResult Goal::checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const {
	(void)entity; //to avoid unused parameter warning when compiling
	(void)fromPos;
	(void)tilePos;
	return MoveResult::ALLOW;
}

bool Goal::isGoal() const {
	return true;
}

std::string Goal::getGlyph() const {
	return "<";
}