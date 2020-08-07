//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//basicgamerules.cpp
#include "basicgamerules.h"
#include <iostream>

BasicGameRules::BasicGameRules(){
}

BasicGameRules::~BasicGameRules(){
}

bool BasicGameRules::allowMove(Game *game, Entity *actor, const Position &source,const Position &dest) const{
  if (source.distanceFrom(dest) != 1){
    return false;
  }
  if (!game->getMaze()->inBounds(source) || !game->getMaze()->inBounds(dest)) {
      return false;
  }
  if (game->getEntityAt(dest) == nullptr && game->getMaze()->getTile(dest)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW) {
      return true;
  }
  if (game->getEntityAt(dest) != nullptr) {
      Entity* dest_entity = game->getEntityAt(dest);
      if (dest_entity->hasProperty('v')) {
          int down = dest.getY() - source.getY(); // = 1 if move down; = -1 if move up; = 0 if move horizontally
          switch (down) {
          case 1: {
              Position dest2 = Position(dest.getX(), dest.getY() + 1);
              return game->getMaze()->inBounds(dest2) && game->getEntityAt(dest2) == nullptr && game->getMaze()->getTile(dest2)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW;
          }
          case -1: {
              Position dest2 = Position(dest.getX(), dest.getY() - 1);
              return game->getMaze()->inBounds(dest2) && game->getEntityAt(dest2) == nullptr && game->getMaze()->getTile(dest2)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW;
          }
          case 0: {
              int right = dest.getX() - source.getX(); // = 1 if move right; = -1 if move left
              switch (right) {
              case 1: {
                  Position dest2 = Position(dest.getX() + 1, dest.getY());
                  return game->getMaze()->inBounds(dest2) && game->getEntityAt(dest2) == nullptr && game->getMaze()->getTile(dest2)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW;
              }
              case -1: {
                  Position dest2 = Position(dest.getX() - 1, dest.getY());
                  return game->getMaze()->inBounds(dest2) && game->getEntityAt(dest2) == nullptr && game->getMaze()->getTile(dest2)->checkMoveOnto(actor, source, dest) == MoveResult::ALLOW;
              }
              }
          }
          }
      }
      else if (dest_entity->hasProperty('h') && actor->hasProperty('m')) { //a minotaro can catch a hero
          return true;
      }
      else if (dest_entity->hasProperty('m') && actor->hasProperty('h')) { //a hero can kill itself
          return true;
      }
  }
  return false;
}
	  
void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const{
  int curr_x=actor->getPosition().getX();int curr_y=actor->getPosition().getY();
  int dest_x=dest.getX();int dest_y=dest.getY();
  if (game->getEntityAt(dest)!=nullptr && game->getEntityAt(dest)->hasProperty('v')){ //a moveable object needs to be pushed
      if (dest_x - curr_x == 1) { //move right
          game->getEntityAt(dest)->setPosition(Position(dest_x + 1, dest_y));
      }
      else if (dest_x - curr_x == -1) { //move left
          game->getEntityAt(dest)->setPosition(Position(dest_x - 1, dest_y));
      }
      else if (dest_y - curr_y == 1) { //move down
          game->getEntityAt(dest)->setPosition(Position(dest_x, dest_y + 1));
      }
      else { //move up
          game->getEntityAt(dest)->setPosition(Position(dest_x, dest_y - 1));
      }
  }
  actor->setPosition(dest);
}


GameResult BasicGameRules::checkGameResult(Game *game)const{
  std::vector<Entity *> m_list=game->getEntitiesWithProperty('m');
  std::vector<Entity *> temp=game->getEntitiesWithProperty('h');
    for (std::vector<Entity *>::iterator it=temp.begin();it!=temp.end();++it){
      if( game->getMaze()->getTile((*it)->getPosition())->isGoal()){
	return GameResult::HERO_WINS;
      }
      
      for (std::vector<Entity *>::iterator it1=m_list.begin();it1!=m_list.end();++it1){
        if((*it)->getPosition()==(*it1)->getPosition()){
	  return GameResult::HERO_LOSES;
	}
      }
    }
    return GameResult::UNKNOWN;
}  
      
    
    
	  
	
  
  
  
