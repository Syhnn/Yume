#include "Texture.hpp"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"


using namespace std;


// Constructors and destructor

Texture::Texture(SDL_Texture* t, int w, int h) :
  texture(t),

  width(w),
  height(h)
{}

Texture::~Texture() {
  free();
}


// Public methods

void Texture::free() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
  for (int i(0); i < clips.size(); ++i) {
    delete clips[i];
  }
  clips.clear();
}

SDL_Texture* Texture::getRawTexture() const {
  return texture;
}

int Texture::getWidth() const {
  return width;
}
int Texture::getHeight() const {
  return height;
}

Texture* Texture::fromImage(SDL_Renderer* r, std::string path, int w, int h) {
  SDL_Texture* new_texture = nullptr;
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());

  if (loaded_surface == nullptr) {
    cout << "Unable to load image " << path << " - SDL_image Error:\n" << IMG_GetError() << endl;
    return nullptr;
  } else {
    new_texture = SDL_CreateTextureFromSurface(r, loaded_surface);
    if (new_texture == nullptr) {
      cout << "Unable to create texture from " << path << " - SDL Error:\n" << SDL_GetError() << endl;
      return nullptr;
    }
    SDL_FreeSurface(loaded_surface);
  }

  Texture* tp = new Texture(new_texture, w, h);
  return tp;
}

int Texture::addClip(int x, int y, int w, int h) {
  clips.push_back(new SDL_Rect({x, y, w, h}));
  return static_cast<int>(clips.size()) - 1;
}

const SDL_Rect* Texture::getClip(int id) {
  if (id < clips.size() && id >= 0) return clips[id];
  else return nullptr;
}

// Private Methods

//
