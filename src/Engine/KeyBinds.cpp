#include "KeyBinds.hpp"

#include <iostream>
#include "SDL.h"

#include "Engine.hpp"


using namespace std;


// Public methods

void KeyBinds::handleInputs(Engine* engine) {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      engine->exit();
    } else if (e.type == SDL_KEYDOWN && !e.key.repeat) {
      if (commands_down.find(e.key.keysym.sym) != commands_down.end()) {
        commands_down[e.key.keysym.sym]();
      }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {
      if (commands_up.find(e.key.keysym.sym) != commands_up.end()) {
        commands_up[e.key.keysym.sym]();
      }
    }
  }
}

void KeyBinds::bindKeyUp(Key k, cfunc f) {
  commands_up[k] = f;
}

void KeyBinds::bindKeyDown(Key k, cfunc f) {
  commands_down[k] = f;
}

void KeyBinds::unbind(int k) {
  commands_down.erase(k);
}
