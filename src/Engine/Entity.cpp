#include "Entity.hpp"


using namespace std;


// Constructors and destructor

Entity::Entity() :
  posx(0),
  posy(0),
  texture_id(-1),
  name("")
{}

// Public methods

int Entity::getClipId(const int dt) {
  return -1;
}


// Private methods

//
