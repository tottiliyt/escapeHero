//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//uicontrol.cpp
#include "uicontrol.h"
#include "ui.h"

UIControl::UIControl() {
}

UIControl::~UIControl() {
}

Direction UIControl::getMoveDirection(Game* game, Entity* entity) {
	(void)game; //to avoid unused parameter compiling warning
	(void)entity;
	UI* ui = UI::getInstance();
	Direction dir = ui->getMoveDirection();
	return dir;
}

bool UIControl::isUser() const {
	return true;
}