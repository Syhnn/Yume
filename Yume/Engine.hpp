#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>


class DisplayManager;
class GameState;


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


class Engine {
public:
  Engine();
  ~Engine();

  void mainloop();

  void pushState(GameState* state);
  void popState();

  void handleInputs();
  void update();
  void display();

  bool init();
  void exit();

private:
  bool quit;

  // to be deleted - test variable
  int tmp;

  // todo: smart pointers
  DisplayManager* dm;

  std::vector<GameState*> states;
};

#endif // _CORE_HPP_
