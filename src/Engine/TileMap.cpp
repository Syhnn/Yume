#include "TileMap.hpp"


using namespace std;


// Cosntructors and destructor

TileMap::TileMap(int w, int h, int s, vector<vector<int>> g) :
  Entity(),

  width(w),
  height(h),

  tile_size(s),

  fixed_texture_id(-1),

  grid(g)
{}


// Public methods

int TileMap::getWidth() const {
  return width;
}

int TileMap::getHeight() const {
  return height;
}

int TileMap::getTileSize() const {
  return tile_size;
}

void TileMap::setTileSize(int size) {
  tile_size = size;
}

int TileMap::getClip(int x, int y) const {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    return grid[y][x];
  }
  return -1;
}
