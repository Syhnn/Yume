#include "DataLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "DisplayManager.hpp"
#include "TileMap.hpp"


using namespace rapidjson;
using namespace std;


// Public methods

int DataLoader::initTextureFromTileset(DisplayManager* dm, string path) {
  ifstream s(path);

  string content = "";
  string line;
  while (getline(s, line)) {
    std::istringstream iss(line);
    content += iss.str();
  }

  Document doc;
  if (doc.Parse(content.c_str()).HasParseError()) {
    cout << "Couldn't read tileset info from json: " << path << "\nerror: "<< doc.GetParseError() << endl;
  }

  if (!doc.IsObject() || !doc.HasMember("tileset")) {
    cout << "json doesn't contains tileset info" << endl;
    return -1;
  }

  const Value& tileset = doc["tileset"];

  if (!tileset.IsObject() ||
    !tileset.HasMember("name") || !tileset["name"].IsString() ||
    !tileset.HasMember("path") || !tileset["path"].IsString() ||
    !tileset.HasMember("tile_size") || !tileset["tile_size"].IsInt() ||
    !tileset.HasMember("width") || !tileset["width"].IsInt() ||
    !tileset.HasMember("height") || !tileset["height"].IsInt() ||
    !tileset.HasMember("format") || !tileset["format"].IsString()) {
    // todo: clean up, it's messy and doesn't tell you what's missing
    cout << "tileset info is missing or incorrect" << endl;
    return -1;
  }

  string tileset_path = tileset["path"].GetString();
  int tile_size = tileset["tile_size"].GetInt();
  int tileset_tex_id = dm->loadTexture(tileset_path, tile_size, tile_size);
  if (tileset_tex_id == -1) {
    cout << "Couldn't load texture " << tileset_path << endl;
  } else {
    int width = tileset["width"].GetInt();
    int height = tileset["height"].GetInt();

    for (int j(0); j < height; ++j) {
      for (int i(0); i < width; ++i) {
        dm->addTextureClip(tileset_tex_id, i * tile_size, j * tile_size, tile_size, tile_size);
      }
    }
  }
  return tileset_tex_id;
}

TileMap* DataLoader::initTileMapFromJSON(string path, int id) {
  ifstream s(path);

  string content = "";
  string line;
  while (getline(s, line)) {
    std::istringstream iss(line);
    content += iss.str();
  }

  Document doc;
  if (doc.Parse(content.c_str()).HasParseError()) {
    cout << "Couldn't read tilemap info from json: " << path << "\nerror: " << doc.GetParseError() << endl;
  }

  if (!doc.IsObject() || !doc.HasMember("tilemap")) {
    cout << "json doesn't contains tilemap info" << endl;
    return nullptr;
  }

  const Value& tilemap = doc["tilemap"];

  if (!tilemap.IsObject() ||
    !tilemap.HasMember("name") || !tilemap["name"].IsString() ||
    !tilemap.HasMember("using") || !tilemap["using"].IsString() ||
    !tilemap.HasMember("width") || !tilemap["width"].IsInt() ||
    !tilemap.HasMember("height") || !tilemap["height"].IsInt() ||
    !tilemap.HasMember("grid") || !tilemap["grid"].IsArray() || ! tilemap["grid"][0].IsArray()) {
    // todo: clean up, it's messy and doesn't tell you what's missing
    cout << "tilemap info is missing or incorrect" << endl;
    return nullptr;
  }

  int width = tilemap["width"].GetInt();
  int height = tilemap["height"].GetInt();
  vector<vector<int>> grid;

  if (tilemap["grid"].Size() != height) {
    cout << "tilemap written size and actual size differ" << endl;
    return nullptr;
  }

  for (SizeType j = 0; j < tilemap["grid"].Size(); ++j) {
    const Value& l = tilemap["grid"][j];
    if (!l.IsArray()) {
      cout << "warning: line is not an array" << endl;
      continue;
    }
    vector<int> row;
    for (SizeType i = 0; i < l.Size(); ++i) {
      if (!l[i].IsInt()) {
        cout << "missing value in grid" << endl;
        return nullptr;
      }
      row.push_back(l[i].GetInt());
    }
    grid.push_back(row);
  }

  TileMap* map = new TileMap(width, height, 32, grid);
  return map;
}

map<string, Entity*> DataLoader::loadStateData(DisplayManager* dm, string path) {
  map<string, Entity*> entities;
  ifstream s(path);

  string content = "";
  string line;
  while (getline(s, line)) {
    std::istringstream iss(line);
    content += iss.str();
  }

  Document doc;
  if (doc.Parse(content.c_str()).HasParseError()) {
    cout << "Couldn't read tilemap info from json: " << path << "\nerror: " << doc.GetParseError() << endl;
  }

  if (!doc.IsObject()) {
    cout << "json does not contain an object" << endl;
    return entities;
  }

  bool error(false);
  if (!doc.HasMember("ressources") || !doc["ressources"].IsArray()) {
    cout << "json doesn't contains ressources array" << endl;
    error = true;
  }
    
  if (!doc.HasMember("entities") || !doc["entities"].IsArray()) {
    cout << "json doesn't contains entities array" << endl;
    error = true;
  }
  
  if (error) return entities;

  const Value& assets_data = doc["ressources"];
  const Value& entities_data = doc["entities"];

  // Parse Ressources

  for (SizeType i(0); i < assets_data.Size(); ++i) {
    if (assets_data[i].HasMember("tileset") && assets_data[i]["tileset"].IsObject()) {
      parseTileset(dm, assets_data[i]["tileset"]);
    } else {
      cout << "unidentified object in json" << endl;
      // get data from object ?
    }
  }

  // Parse Entities

  for (SizeType i(0); i < entities_data.Size(); ++i) {
    if (entities_data[i].HasMember("tilemap") && entities_data[i]["tilemap"].IsObject()) {
      Entity* e = parseTilemap(dm, entities_data[i]["tilemap"]);
      if (e != nullptr) {
        string ename = e->name;
        entities.insert(make_pair(ename, e));
      }
    } else {
      cout << "unidentified object in json" << endl;
      // get data from object ?
    }
  }
  return entities;
}


// Private methods

void DataLoader::parseTileset(DisplayManager* dm, const Value& tileset) {
  if (!tileset.IsObject() ||
    !tileset.HasMember("name") || !tileset["name"].IsString() ||
    !tileset.HasMember("path") || !tileset["path"].IsString() ||
    !tileset.HasMember("tile_size") || !tileset["tile_size"].IsInt() ||
    !tileset.HasMember("width") || !tileset["width"].IsInt() ||
    !tileset.HasMember("height") || !tileset["height"].IsInt() ||
    !tileset.HasMember("format") || !tileset["format"].IsString()) {
    cout << "tileset info is missing or incorrect" << endl;
  } else {
    ;
    string tileset_name = tileset["name"].GetString();
    string tileset_path = tileset["path"].GetString();
    int tile_size = tileset["tile_size"].GetInt();
    int tileset_tex_id = dm->loadTexture(tileset_path, tile_size, tile_size);
    if (tileset_tex_id == -1) {
      cout << "Couldn't load texture " << tileset_path << endl;
    } else {
      int width = tileset["width"].GetInt();
      int height = tileset["height"].GetInt();

      for (int j(0); j < height; ++j) {
        for (int i(0); i < width; ++i) {
          dm->addTextureClip(tileset_tex_id, i * tile_size, j * tile_size, tile_size, tile_size);
        }
      }
    }
    dm->defineNameForTexture(tileset_name, tileset_tex_id);
  }
}

Entity* DataLoader::parseTilemap(DisplayManager* dm, const Value& tilemap_data) {
  if (!tilemap_data.IsObject() ||
    !tilemap_data.HasMember("name") || !tilemap_data["name"].IsString() ||
    !tilemap_data.HasMember("using") || !tilemap_data["using"].IsString() ||
    !tilemap_data.HasMember("width") || !tilemap_data["width"].IsInt() ||
    !tilemap_data.HasMember("height") || !tilemap_data["height"].IsInt() ||
    !tilemap_data.HasMember("grid") || !tilemap_data["grid"].IsArray() || !tilemap_data["grid"][0].IsArray()) {
    // todo: clean up, it's messy and doesn't tell you what's missing
    cout << "tilemap info is missing or incorrect" << endl;
    return nullptr;
  }

  int width = tilemap_data["width"].GetInt();
  int height = tilemap_data["height"].GetInt();
  vector<vector<int>> grid;

  if (tilemap_data["grid"].Size() != height) {
    cout << "tilemap written size and actual size differ" << endl;
    return nullptr;
  }

  for (SizeType j = 0; j < tilemap_data["grid"].Size(); ++j) {
    const Value& l = tilemap_data["grid"][j];
    if (!l.IsArray()) {
      cout << "warning: line is not an array" << endl;
      continue;
    }
    vector<int> row;
    for (SizeType i = 0; i < l.Size(); ++i) {
      if (!l[i].IsInt()) {
        cout << "missing value in grid" << endl;
        return nullptr;
      }
      row.push_back(l[i].GetInt());
    }
    grid.push_back(row);
  }

  TileMap* tilemap = new TileMap(width, height, 32, grid);
  tilemap->name = tilemap_data["name"].GetString();
  string texture_name = tilemap_data["using"].GetString();
  tilemap->texture_id = dm->getTextureId(texture_name);
  if (dm->createTextureFromTilemap(tilemap) == -1) {
    cout << "coudln't generate fixed tilemap" << endl;
  }

  return tilemap;
}
