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
          kp.push_back(commands_down[command]);
        }
      }
    } else if (e.type == SDL_KEYUP && !e.key.repeat) {
      int k = e.key.keysym.sym;
      if (k >= SDLK_a && k <= SDLK_z) {
        int command = k - SDLK_a;
        if (commands_up.find(command) != commands_up.end()) {
          kp.push_back(commands_up[command]);
        }
      }
    }
  }
}

void KeyBinds::bindKeyUp(Key k, int command_id) {
  if (commands_up.find(k) == commands_up.end()) {
    commands_up[k] = command_id;
  }
}

void KeyBinds::bindKeyDown(Key k, int command_id) {
  if (commands_down.find(k) == commands_down.end()) {
    commands_down[k] = command_id;
  }
}

void KeyBinds::unbind(int k) {
  commands_down.erase(k);
}

std::vector<int> KeyBinds::getEvents() {
  vector<int> events = kp; // disgusting
  kp = vector<int>();
  return events;
}


// Private methods

//
