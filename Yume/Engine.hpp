#ifndef _CORE_HPP_
#define _CORE_HPP_


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


class DisplayManager;


class Engine {
public:
  Engine();
  ~Engine();

  void mainloop();

  void handleInputs();
  void update();
  void display();

  bool init();

private:
  bool quit;

  // to be deleted - test variable
  int tmp;

  // todo: smart pointers
  DisplayManager* dm;
};

#endif // _CORE_HPP_
