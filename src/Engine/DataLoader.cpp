#include "DataLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "document.h"

#include "DisplayManager.hpp"
#include "TileMap.hpp"


using namespace rapidjson;
using namespace std;


// Public mathods

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
    !tileset.HasMember("id") || !tileset["id"].IsInt() ||
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

TileMap* DataLoader::initTileMapFromJSON(std::string path, int id) {
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
    !tilemap.HasMember("id") || !tilemap["id"].IsInt() ||
    !tilemap.HasMember("using") || !tilemap["using"].IsInt() ||
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

void DataLoader::loadStateData(string path) {
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
    return;
  }

  bool error(false);
  if (!doc.HasMember("ressources")) {
    cout << "json doesn't contains tilemap info" << endl;
    error = true;
  }
    
  if (!doc.HasMember("entities")) {
    cout << "json doesn't contains tilemap info" << endl;
    error = true;
  }
  
  if (error) return;

  const Value& ressources = doc["ressources"];
  const Value& entities = doc["entities"];

  // parse everything calling private methods and store data
}
