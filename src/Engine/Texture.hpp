#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <cstdint>
#include <string>


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

private:
  SDL_Texture* texture;

  int width;
  int height;
};

#endif // _TEXTURE_HPP_
