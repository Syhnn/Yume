#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <cstdint>
#include <string>
#include <vector>


struct SDL_Color;
struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;


class Texture {
public:
  Texture(SDL_Texture* t, int w, int h);
  ~Texture();

  void free();

  SDL_Texture* getRawTexture() const;
  int getWidth() const;
  int getHeight() const;

  void setColor(SDL_Color* c);

  static Texture* fromImage(SDL_Renderer* r, std::string path, int w, int h);
  static Texture* fromTTF(SDL_Renderer* r, TTF_Font* f, std::string text);

  bool loadFromText(SDL_Renderer* r, TTF_Font* f, std::string text);

  int addClip(int x, int y, int w, int h);
  const SDL_Rect* getClip(int id);

private:
  SDL_Texture* texture;

  int width;
  int height;

  std::vector<SDL_Rect*> clips;

  SDL_Color* color;
};

#endif // _TEXTURE_HPP_
