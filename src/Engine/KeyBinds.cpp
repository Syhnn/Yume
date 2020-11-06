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
      if (key_down.find(e.key.keysym.sym) != key_down.end()) {
        key_down[e.key.keysym.sym]();
      }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {
      if (key_up.find(e.key.keysym.sym) != key_up.end()) {
        key_up[e.key.keysym.sym]();
      }
    }
  }
}

void KeyBinds::bindKeyDown(Key k, cfunc f) {
  key_down[k] = f;
}

void KeyBinds::bindKeyUp(Key k, cfunc f) {
  key_up[k] = f;
}

void KeyBinds::unbindKeyDown(Key k) {
  key_down.erase(k);
}

void KeyBinds::unbindKeyUp(Key k) {
  key_up.erase(k);
}
