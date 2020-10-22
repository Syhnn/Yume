#ifndef _KEY_BINDS_HPP_
#define _KEY_BINDS_HPP_

#include <map>
#include <string>
#include <vector>


class Engine;

typedef void (*cfunc)(void);


enum Key {
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


class KeyBinds {
public:
  void handleInputs(Engine* engine);

  void bindKeyDown(Key k, cfunc f);
  void bindKeyUp(Key k, cfunc f);
  void unbind(int k);

private:
  std::vector<int> kp;
  std::map<int, cfunc> commands_up;
  std::map<int, cfunc> commands_down;
};

#endif // _KEY_BINDS_HPP_
