#ifndef _KEY_BINDS_HPP_
#define _KEY_BINDS_HPP_

#include <map>
#include <string>
#include <vector>


class Engine;

typedef void (*cfunc)(void);


enum Key {
  A = 'a',
  B = 'b',
  C = 'c',
  D = 'd',
  E = 'e',
  F = 'f',
  G = 'g',
  H = 'h',
  I = 'i',
  J = 'j',
  K = 'k',
  L = 'l',
  M = 'm',
  N = 'n',
  O = 'o',
  P = 'p',
  Q = 'q',
  R = 'r',
  S = 's',
  T = 't',
  U = 'u',
  V = 'v',
  W = 'w',
  X = 'x',
  Y = 'y',
  Z = 'z',

  NUM_0 = '0',
  NUM_1 = '1',
  NUM_2 = '2',
  NUM_3 = '3',
  NUM_4 = '4',
  NUM_5 = '5',
  NUM_6 = '6',
  NUM_7 = '7',
  NUM_8 = '8',
  NUM_9 = '9'
};


class KeyBinds {
public:
  void handleInputs(Engine* engine);

  void bindKeyDown(Key k, cfunc f);
  void bindKeyUp(Key k, cfunc f);
  void unbindKeyDown(Key k);
  void unbindKeyUp(Key k);

private:
  std::vector<int> kp;
  std::map<int, cfunc> key_up;
  std::map<int, cfunc> key_down;
};

#endif // _KEY_BINDS_HPP_
