#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_


class Entity {
public:
  Entity();

  virtual int getClipId(const int dt);

  int posx;
  int posy;

  int texture_id;
};

#endif // _ENTITY_HPP_
