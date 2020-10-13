#include "GameState.hpp"

#include "SDL.h"

#include "DisplayManager.hpp"
#include "Engine.hpp"


using namespace std;


void GameState::handleInputs(Engine* engine) {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      engine->exit();
    }
  }
}
