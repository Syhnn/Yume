#ifndef _KEY_BINDS_HPP_
#define _KEY_BINDS_HPP_

#include <map>
#include <string>
#include <vector>


class Command;
class Engine;


enum Key {
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


class KeyBinds {
public:
  void handleInputs(Engine* engine);

  void bindKeyDown(Key k, Command* c);
  void bindKeyUp(Key k, Command* c);
  void unbind(int k);

private:
  std::vector<int> kp;
  std::map<int, Command*> commands_up;
  std::map<int, Command*> commands_down;
};

#endif // _KEY_BINDS_HPP_
