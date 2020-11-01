#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <string>
#include <vector>


class DisplayManager;
class GameState;


const int FPS = 60;
const int MS_PER_FRAME = 1000 / FPS;


class Engine {
public:
  Engine();
  ~Engine();

  void mainloop();

  void pushState(GameState* state);
  void popState();

  void handleInputs();
  void update(const int dt);
  void display(const int dt);

  bool init();
  void exit();

  bool loadTextComponent(std::string path);

private:
  bool quit;

  DisplayManager* dm;

  std::vector<GameState*> states;
};

#endif // _CORE_HPP_
