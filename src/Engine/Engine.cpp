#include "Engine.hpp"

#include <iostream>
#include "SDL.h"

#include "DisplayManager.hpp"
#include "GameState.hpp"


using namespace std;


// Constructors and destructor

Engine::Engine() :
  quit(false),

  tmp(0),

  dm(new DisplayManager())
{}

Engine::~Engine() {
  if (dm) delete dm;
  SDL_Quit();
}


// Public methods

void Engine::mainloop() {
  Uint32 time;

  time = SDL_GetTicks();
  while (!quit) {
    handleInputs();
    update();
    // cap at roughly 60 fps (not quite) todo: improve
    if (SDL_GetTicks() - time > SCREEN_TICKS_PER_FRAME) {
      display();
      time = SDL_GetTicks();
    }
  }
}

void Engine::pushState(GameState* state) {
  if (!states.empty()) {
    states.back()->pause();
  }

  states.push_back(state);
  state->init(dm);
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

void Engine::update() {
  states.back()->update();
}

void Engine::display() {
  states.back()->display(dm);
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


// Private methods

// code here
