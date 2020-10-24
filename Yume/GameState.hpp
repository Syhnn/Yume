#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <set>


class DisplayManager;
class Engine;
class Entity;
class KeyBinds;


class GameState {
public:
  GameState();
  ~GameState();

  virtual void init(Engine* e, DisplayManager* dm) = 0;
  virtual void cleanUp() = 0;

  virtual void pause() {}
  virtual void resume() {}

  virtual void handleInputs(Engine* engine);
  virtual void update(const int dt) {}
  virtual void display(DisplayManager* const dm, const int dt);

  void addEntity(Entity* e);
  void removeEntity(Entity* e);

protected:
  KeyBinds* kb;

private:
  std::set<Entity*> entities;
};

#endif // _GAME_STATE_HPP_
