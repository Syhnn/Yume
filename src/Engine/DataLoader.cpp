#include "DataLoader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "document.h"

#include "DataMap.hpp"


using namespace rapidjson;
using namespace std;


// Public mathods

DataMap* DataLoader::fromJSON(string path) {
  ifstream s(path);

  string content = "";
  string line;
  while (getline(s, line)) {
    std::istringstream iss(line);
    content += iss.str();
  }

  Document doc;
  if (doc.Parse(content.c_str()).HasParseError()) {
    cout << "error" << endl;
    cout << doc.GetParseError() << endl;
  }

  cout << "document parsed" << endl;
  if (doc.IsObject()) {
    cout << "document is an object" << endl;
    if (doc.HasMember("tilemap")) {
      cout << "doc is tilemap" << endl;
      if (doc["tilemap"].IsObject()) {
        cout << "tilemap parsed" << endl;
        if (doc["tilemap"].HasMember("grid")) {
          cout << "tilemap has grid member" << endl;

          if (doc["tilemap"]["grid"].IsArray()) {
            cout << "gird is array" << endl;
            const Value& table = doc["tilemap"]["grid"];
            for (SizeType i = 0; i < table.Size(); ++i) {
              const Value& l = table[i];
              if (l.IsArray()) {
                for (SizeType j = 0; j < l.Size(); ++j) {
                  if (l[j].IsInt()) {
                    cout << l[j].GetInt() << " ";
                  }
                }
                cout << endl;
              }
            }
            
          }
        }
      }
    }
  }

  return nullptr;
}
