//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//entity.cpp
#include "entity.h"
#include<string>

using std::string;


Entity::Entity(){
}

Entity::~Entity(){
  delete entitycontroller;
}

void Entity::setGlyph(const std::string &glyph){
  this->glyph=glyph[0];
}

void Entity::setProperties(const std::string &props){
  this->props=props;
}

std::string Entity::getGlyph() const{
  return string(1,glyph);
}

std::string Entity::getProperties() const{
  return props;
}

bool Entity::hasProperty(char prop) const{
  for(int i=0;i<(int)props.length();i++){
    if (props.at(i)==prop){
      return true;
    }
  }
  return false;
}
  
void Entity::setController(EntityController *controller){
  entitycontroller=controller;
  
}

EntityController *Entity::getController(){
  return entitycontroller;
}

void Entity::setPosition(const Position &pos){
  position=Position(pos.getX(),pos.getY());
}

Position Entity::getPosition() const{
  return position;
}


