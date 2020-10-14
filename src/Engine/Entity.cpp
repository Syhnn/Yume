#include "Entity.hpp"


using namespace std;


// Constructors and destructor

Entity::Entity() :
  posx(0),
  posy(0),
  vx(0),
  vy(0),
  texture_id(-1)
{}

// Public methods

int Entity::getClipId(const int dt) {
  return -1;
}


// Private methods

//
