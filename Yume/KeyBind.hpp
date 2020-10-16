#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_


class KeyBind {
public:
  virtual void callback() = 0;
};

#endif // _COMMAND_HPP_
