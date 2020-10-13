#include "GameState.hpp"

#include "SDL.h"

#include "DisplayManager.hpp"
#include "Engine.hpp"
#include "Entity.hpp"


using namespace std;


void GameState::handleInputs(Engine* engine) {
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      engine->exit();
    }
  }
}

void GameState::display(const DisplayManager* dm) {
  dm->clear();
  for (Entity* e : entities) {
    dm->renderTexture(e->textureId, e->posx, e->posy);
  }
}

void GameState::addEntity(Entity* e) {
  entities.insert(e);
}

void GameState::removeEntity(Entity* e) {
  entities.erase(e);
}
