#ifndef _DATA_LOADER_HPP_
#define _DATA_LOADER_HPP_

#include <map>
#include <string>

#include "rapidjson/document.h"


class DataMap;
class DisplayManager;
class Entity;
class TileMap;


class DataLoader {
public:
  static int initTextureFromTileset(DisplayManager* dm, std::string path);
  static TileMap* initTileMapFromJSON(std::string path, int id);
  static std::map<std::string, Entity*> loadStateData(DisplayManager* dm, std::string path);

private:
  static void parseTileset(DisplayManager* dm, const rapidjson::Value& tileset_data);
  static Entity* parseTilemap(DisplayManager* dm, const rapidjson::Value& tilemap_data);
};

#endif // _DATA_LOADER_HPP_
