#ifndef _KEY_BINDS_HPP_
#define _KEY_BINDS_HPP_

#include <map>
#include <string>
#include <vector>


class Engine;


enum Key {
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


class KeyBinds {
public:
  void handleInputs(Engine* engine);

  void bindKeyDown(Key k, int command_id);
  void bindKeyUp(Key k, int command_id);
  void unbind(int k);
  std::vector<int> getEvents();

private:
  std::vector<int> kp;
  std::map<int, int> commands_up;
  std::map<int, int> commands_down;
};

#endif // _KEY_BINDS_HPP_
