#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>


class DisplayManager;
class GameState;
class KeyBinds;


const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;


class Engine {
public:
  Engine();
  ~Engine();

  void mainloop();

  void pushState(GameState* state);
  void popState();

  void handleInputs();
  void update(int dt);
  void display();

  bool init();
  void exit();

private:
  bool quit;

  // to be deleted - test variable
  int tmp;

  // todo: smart pointers
  DisplayManager* dm;
  KeyBinds* kb;

  std::vector<GameState*> states;
};

#endif // _CORE_HPP_
