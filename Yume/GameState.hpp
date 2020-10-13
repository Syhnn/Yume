#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_


class Engine;
class DisplayManager;


class GameState {
public:
  virtual void init(DisplayManager* dm) = 0;
  virtual void cleanUp() = 0;

  virtual void pause() {};
  virtual void resume() {};

  void handleInputs(Engine* engine);
  virtual void update() = 0;
  virtual void display(const DisplayManager* dm) = 0;

  // figure this out
  //virtual void changeState(Engine* engine, GameState* state) = 0;

private:
  //
};

#endif // _GAME_STATE_HPP_
