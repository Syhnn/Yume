#ifndef _DATA_LOADER_HPP_
#define _DATA_LOADER_HPP_

#include <string>


class DataMap;
class DisplayManager;
class TileMap;


class DataLoader {
public:
  static int initTextureFromTileset(DisplayManager* dm, std::string path);
  static TileMap* initTileMapFromJSON(std::string path, int id);
  static void loadStateData(std::string path);

private:
  //
};

#endif // _DATA_LOADER_HPP_
