#include "Engine.hpp"

#include <iostream>
#include "DisplayManager.hpp"
#include "SDL.h"


using namespace std;


Engine::Engine() :
  quit(false),

  tmp(0),

  dm(new DisplayManager())
{}

Engine::~Engine() {
  if (dm) delete dm;
  SDL_Quit();
}


void Engine::handleInputs() {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      quit = true;
    }
  }
}

void Engine::update() {
  
}

void Engine::display() {
  dm->clear();
  dm->renderTexture(tmp, 0, 0);
  dm->render();
}

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

bool Engine::init() {
  if (!dm->init()) {
    cout << "Something went wrong initializing the display manager" << endl;
    return false;
  }

  string path = "assets/culture.png";
  tmp = dm->loadTexture(path, 383, 501);
  if (tmp == -1) {
    cout << "Couldn't load texture " << path << endl;
    return false;
  }

  return true;
}


// Private methods

// code here
