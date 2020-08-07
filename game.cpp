//Yuntao Li
//yli346
//Wenxuan Lu
//wlu15
//Alex Zhang
//azhang41

//game.cpp
#include "game.h"

Game::Game() : game_entity(new EntityVec) {
}

Game::~Game(){

  delete game_ui;
  delete game_gameRules;
  delete game_maze;
  //delete[] game_entity;
  for(Entity* p: *game_entity){delete p;}
  //game_entity->clear();
  delete game_entity;
  
}

void Game::setMaze(Maze *maze){
  game_maze=maze;
}

void Game::setUI(UI *ui){
  game_ui=ui;
}

void Game::setGameRules(GameRules *gameRules){
  game_gameRules=gameRules;
}

void Game::addEntity(Entity *entity){
  game_entity->push_back(entity);
}

Entity *Game::getEntityAt(const Position &pos){
  int count = 0;
  for (std::vector<Entity *>::iterator it=game_entity->begin();it!=game_entity->end();++it){
      if ((*it)->getPosition() == pos) {
          count++;
      }
  }
  for (std::vector<Entity*>::iterator it = game_entity->begin();it != game_entity->end();++it) {
      if (count == 1) {
          if ((*it)->getPosition() == pos) {
              return *it;
          }
      }
      else if (count > 1) {
          char m = (*it)->getGlyph()[0];
          if ((*it)->getPosition() == pos && m == 'M') {
              return *it;
          }
      }
      
  }
  return nullptr;
}

const std::vector<Entity *>& Game::getEntities() const{
  return *game_entity;
}

std::vector<Entity *> Game::getEntitiesWithProperty(char prop) const{
  std::vector<Entity *> temp;
  for (std::vector<Entity *>::iterator it=game_entity->begin();it!=game_entity->end();++it){
    if((*it)->hasProperty(prop)){
      temp.push_back(*it);
    }
  }
  return temp;
}

Maze *Game::getMaze(){
  return game_maze;
}

UI *Game::getUI(){
  return game_ui;
}

GameRules *Game::getGameRules(){
  return game_gameRules;
}


void Game::gameLoop(){
  std::vector<Entity *> temp_entities=this->getEntities();
  while(this->getGameRules()->checkGameResult(this)==GameResult::UNKNOWN){
  for(std::vector<Entity *>::iterator it=temp_entities.begin();it!=temp_entities.end();++it){

    if((*it)->getController()->isUser()){
      this->getUI()->render(this);
    }
    takeTurn(*it);
    GameResult temp_result=getGameRules()->checkGameResult(this);
    if (temp_result==GameResult::HERO_WINS){
      this->getUI()->displayMessage("Hero wins",true);
      this->getUI()->render(this);
      return; //to avoid multiple print of the game result if game wins not at the last entity (so that the for loop continues)
    }
    if (temp_result==GameResult::HERO_LOSES){
      this->getUI()->displayMessage("Hero loses",true);
      this->getUI()->render(this);
      return; //to avoid multiple print of the game result if game losses not at the last entity (so that the for loop continues)
    } 
  }
  
  }
}

void Game::takeTurn(Entity *actor){
  EntityController* temp_controller=actor->getController();
  Direction temp_dir=temp_controller->getMoveDirection(this,actor);
  Position dest = actor->getPosition().displace(temp_dir);
  if (this->getGameRules()->allowMove(this, actor, actor->getPosition(), dest)) {
      this->getGameRules()->enactMove(this, actor, dest);
  }
  else {
      if (temp_controller->isUser()) {
          this->getUI()->displayMessage("Illegal move", false);
      }
  }
}

Game *Game::loadGame(std::istream &in){
  Game* temp_game=new Game;
  temp_game->game_maze=Maze::read(in);
  if (temp_game->game_maze == nullptr) {
      delete temp_game;
      return nullptr;
  }
  char c;int x;int y;
  EntityControllerFactory* ecfac=EntityControllerFactory::getInstance();
  while (in>>c){
    Entity* temp_entity=new Entity;
    temp_entity->setGlyph(std::string(1,c));
    temp_game->addEntity(temp_entity);
    if (in >> c) {
        EntityController* temp_controller = ecfac->createFromChar(c);
        temp_entity->setController(temp_controller);
    }
    else {
        delete temp_game;
        return nullptr;
    }
    if (in >> c) {
        temp_entity->setProperties(std::string(1,c));
    }
    else {
        delete temp_game;
        return nullptr;
    }
    if((in>>x)&&(in>>y)){
	temp_entity->setPosition(Position(x,y));
      }
    else {
        delete temp_game;
        return nullptr;
    }
  }
  return temp_game;
}





