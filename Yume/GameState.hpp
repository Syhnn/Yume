#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <set>


class Engine;
class Entity;
class DisplayManager;


class GameState {
public:
  virtual void init(DisplayManager* dm) = 0;
  virtual void cleanUp() = 0;

  virtual void pause() {};
  virtual void resume() {};

  void handleInputs(Engine* engine);
  virtual void update() = 0;
  virtual void display(const DisplayManager* dm);

  void addEntity(Entity* e);
  void removeEntity(Entity* e);

  // figure this out
  //virtual void changeState(Engine* engine, GameState* state) = 0;

private:
  std::set<Entity*> entities;
};

#endif // _GAME_STATE_HPP_
