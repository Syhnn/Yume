#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <set>


class DisplayManager;
class Engine;
class Entity;
class KeyBinds;


class GameState {
public:
  virtual void init(DisplayManager* dm, KeyBinds* kb) = 0;
  virtual void cleanUp() = 0;

  virtual void pause() {};
  virtual void resume() {};

  virtual void handleInputs(KeyBinds* kb) = 0;
  virtual void update(int dt) = 0;
  virtual void display(const DisplayManager* dm);

  void addEntity(Entity* e);
  void removeEntity(Entity* e);

  // figure this out
  //virtual void changeState(Engine* engine, GameState* state) = 0;

private:
  std::set<Entity*> entities;
};

#endif // _GAME_STATE_HPP_
