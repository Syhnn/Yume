#include "GameState.hpp"

#include "SDL.h"

#include "DisplayManager.hpp"
#include "Engine.hpp"
#include "Entity.hpp"


using namespace std;


void GameState::display(const DisplayManager* dm, const int dt) {
  dm->clear();
  for (Entity* e : entities) {
    int clip = e->getClipId(dt);
    if (clip == -1) {
      dm->renderTexture(e->texture_id, e->posx, e->posy);
    } else {
      dm->renderClip(e->texture_id, e->posx, e->posy, clip);
    }
  }
}

void GameState::addEntity(Entity* e) {
  entities.insert(e);
}

void GameState::removeEntity(Entity* e) {
  entities.erase(e);
}
