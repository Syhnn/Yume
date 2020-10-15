#ifndef _KEY_BINDS_HPP_
#define _KEY_BINDS_HPP_

#include <map>
#include <string>
#include <vector>

#include "KeyBind.hpp"


class Engine;


enum Key {
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


class KeyBinds {
public:
  void handleInputs(Engine* engine);

  void bindKeyDown(Key k, KeyBind* b);
  void bindKeyUp(Key k, KeyBind* b);
  void unbind(int k);

private:
  std::vector<int> kp;
  std::map<int, KeyBind*> commands_up;
  std::map<int, KeyBind*> commands_down;
};

#endif // _KEY_BINDS_HPP_
