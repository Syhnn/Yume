#ifndef _DATA_LOADER_HPP_
#define _DATA_LOADER_HPP_

#include <string>


class DataMap;


class DataLoader {
public:
  static DataMap* fromJSON(std::string path);

private:
  //
};

#endif // _DATA_LOADER_HPP_
