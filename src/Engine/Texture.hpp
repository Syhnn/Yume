#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <cstdint>
#include <string>
#include <vector>


struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;


class Texture {
public:
  Texture(SDL_Texture* t, int w, int h);
  ~Texture();

  void free();

  SDL_Texture* getRawTexture() const;
  int getWidth() const;
  int getHeight() const;

  static Texture* fromImage(SDL_Renderer* r, std::string path, int w, int h);

  int addClip(int x, int y, int w, int h);
  const SDL_Rect* getClip(int id);

private:
  SDL_Texture* texture;

  int width;
  int height;

  std::vector<SDL_Rect*> clips;
};

#endif // _TEXTURE_HPP_
