#include "Engine.hpp"

#include <iostream>
#include "SDL.h"

#include "DisplayManager.hpp"
#include "GameState.hpp"
#include "KeyBinds.hpp"


using namespace std;


// Constructors and destructor

Engine::Engine() :
  quit(false),

  dm(nullptr)
{
  dm = new DisplayManager();
}

Engine::~Engine() {
  if (dm) {
    delete dm;
    dm = nullptr;
  }

  SDL_Quit();
}


// Public methods

void Engine::mainloop() {
  uint32_t time, new_time, frame_duration;

  time = SDL_GetTicks();
  while (!quit) {
    new_time = SDL_GetTicks();
    frame_duration = new_time - time;
    time = new_time;

    handleInputs();
    update(frame_duration);
    display(frame_duration);
    
    // todo: this is a quick fix
    // since Yume is very early in its development
    // a mainloop iteration is often less than 1ms, which causes issues
    // later i should be able to remove this or just use another type of mainloop
    SDL_Delay(1);
  }
}

void Engine::pushState(GameState* state) {
  if (!states.empty()) {
    states.back()->pause();
  }

  states.push_back(state);
  state->init(this, dm);
}

void Engine::popState() {
  if (!states.empty()) {
    GameState* state = states.back();
    states.pop_back();

    state->cleanUp();
    delete state;
  }

  if (states.empty()) {
    exit();
  } else {
    states.back()->resume();
  }
}

void Engine::handleInputs() {
  states.back()->handleInputs(this);
}

void Engine::update(const int dt) {
  states.back()->update(dt);
}

void Engine::display(const int dt) {
  states.back()->display(dm, dt);
}

bool Engine::init() {
  if (!dm->init()) {
    cout << "Something went wrong initializing the display manager" << endl;
    return false;
  }

  return true;
}

void Engine::exit() {
  quit = true;
}

bool Engine::loadTextComponent(string path) {
  if (!dm->initText(path)) {
    cout << "Error : display manager couldn't initialize text component" << endl;
    return false;
  }

  return true;
}


// Private methods

// code here
