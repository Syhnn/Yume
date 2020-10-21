#ifndef _TILE_MAP_HPP_
#define _TILE_MAP_HPP_

#include "Entity.hpp"

#include <vector>


class TileMap : public Entity {
public:
  TileMap(int w, int h, int s, std::vector<std::vector<int>> g);

  int getWidth() const;
  int getHeight() const;
  int getTileSize() const;

  void setTileSize(int size);

  int getClip(int x, int y) const;


  int fixed_texture_id;

private:
  int width;
  int height;

  int tile_size;

  std::vector<std::vector<int>> grid;
};

#endif // _TILE_MAP_HPP_
