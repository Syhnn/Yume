#include "GameState.hpp"

#include "SDL.h"

#include "DisplayManager.hpp"
#include "Engine.hpp"
#include "Entity.hpp"


using namespace std;


void GameState::display(const DisplayManager* dm) {
  dm->clear();
  for (Entity* e : entities) {
    dm->renderTexture(e->texture_id, e->posx, e->posy);
  }
}

void GameState::addEntity(Entity* e) {
  entities.insert(e);
}

void GameState::removeEntity(Entity* e) {
  entities.erase(e);
}
