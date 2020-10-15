#include "KeyBinds.hpp"

#include <iostream>
#include "SDL.h"

#include "Engine.hpp"


using namespace std;


// Constructors and destructor

//


// Public methods

void KeyBinds::handleInputs(Engine* engine) {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      engine->exit();
    } else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
      int k = e.key.keysym.sym;
      if (k >= SDLK_a && k <= SDLK_z) {
        int command = k - SDLK_a;
        if (commands_down.find(command) != commands_down.end()) {
          commands_down[command]->callback();
        }
      }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {
      int k = e.key.keysym.sym;
      if (k >= SDLK_a && k <= SDLK_z) {
        int command = k - SDLK_a;
        if (commands_up.find(command) != commands_up.end()) {
          commands_up[command]->callback();
        }
      }
    }
  }
}

void KeyBinds::bindKeyUp(Key k, KeyBind* b) {
  commands_up[k] = b;
}

void KeyBinds::bindKeyDown(Key k, KeyBind* b) {
  commands_down[k] = b;
}

void KeyBinds::unbind(int k) {
  commands_down.erase(k);
}


// Private methods

//
