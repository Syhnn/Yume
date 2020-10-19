#include "DisplayManager.hpp"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Texture.hpp"
#include "TileMap.hpp"


using namespace std;


// Constructors and destructor

DisplayManager::DisplayManager(int width, int height) :
  cr(0x00),
  cg(0x00),
  cb(0x00),

  window(nullptr),
  renderer(nullptr),

  WINDOW_WIDTH(width),
  WINDOW_HEIGHT(height),

  font(nullptr)
{}

DisplayManager::~DisplayManager() {
  SDL_DestroyWindow(window);
  IMG_Quit();
}


// Public methods

bool DisplayManager::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    return false;
  }

  window = SDL_CreateWindow("Yume Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl; 
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    cout << "Renderer could not be created - SDL Error:\n" << SDL_GetError() << endl;
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    cout << "SDL_image could not initialize - SDL_image Error:\n" << IMG_GetError() << endl;
    return false;
  }

  if (TTF_Init() == -1) {
    cout << "SDL_ttf could not initialize! SDL_ttf Error:\n" << TTF_GetError() << endl;
    return false;
  }

  font = TTF_OpenFont("assets/monogram_extended.ttf", 32);
  if (font == nullptr) {
    cout << "Failed to load monogram font! SDL_ttf Error\n" << TTF_GetError() << endl;
    return false;
  }
  
  return true;
}

void DisplayManager::clear() const {
  SDL_SetRenderDrawColor(renderer, cr, cg, cb, 0xff);
  SDL_RenderClear(renderer);
}

void DisplayManager::render() const {
  SDL_RenderPresent(renderer);
}

void DisplayManager::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void DisplayManager::setClearColor(uint8_t r, uint8_t g, uint8_t b) {
  cr = r;
  cg = g;
  cb = b;
}

void DisplayManager::drawPoint(float x, float y) {
  SDL_RenderDrawPointF(renderer, x, y);
}

void DisplayManager::drawLine(float x1, float y1, float x2, float y2) {
  SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

int DisplayManager::loadTexture(string path, int w, int h) {
  Texture* t = Texture::fromImage(renderer, path, w, h);
  
  if (t) {
    loaded_textures.push_back(t);
    return static_cast<int>(loaded_textures.size()) - 1;
  } else {
    cout << "Couldn't create Texture object" << endl;
    return -1;
  }
}

int DisplayManager::createTextureFromTilemap(TileMap* const t) {
  int id = t->texture_id;
  if (id < 0 || id >= loaded_textures.size()) return -1;

  SDL_Texture* sdl_tex = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ABGR8888,
    SDL_TEXTUREACCESS_TARGET,
    t->getWidth() * t->getTileSize(),
    t->getHeight() * t->getTileSize());
  // todo: set blend mode here ?
  SDL_SetRenderTarget(renderer, sdl_tex);
  clear();
  int tile_size = t->getTileSize();
  for (int i(0); i < t->getWidth(); ++i) {
    for (int j(0); j < t->getHeight(); ++j) {
      SDL_Rect location = { i * tile_size, j * tile_size, tile_size, tile_size };
      const SDL_Rect* clip = loaded_textures[id]->getClip(t->getClip(i, j));
      SDL_RenderCopy(renderer, loaded_textures[id]->getRawTexture(), clip, &location);
    }
  }
  SDL_SetRenderTarget(renderer, nullptr);
  Texture* tex = new Texture(sdl_tex, t->getWidth() * t-> getTileSize(), t->getHeight() * t->getTileSize());
  loaded_textures.push_back(tex);
  int fti = static_cast<int>(loaded_textures.size()) - 1;
  t->fixed_texture_id = fti;
  return fti;
}

void DisplayManager::renderTexture(int id, int x, int y) const {
  if (id >= 0 && id < loaded_textures.size()) {
    SDL_Rect r = { x, y, loaded_textures[id]->getWidth(), loaded_textures[id]->getHeight() };
    SDL_RenderCopy(renderer, loaded_textures[id]->getRawTexture(), NULL, &r);
  }
}

void DisplayManager::renderClip(int id, int x, int y, int clip) const {
  if (id >= 0 && id < loaded_textures.size()) {
    SDL_Rect r = { x, y, loaded_textures[id]->getWidth(), loaded_textures[id]->getHeight() };
    SDL_RenderCopy(renderer, loaded_textures[id]->getRawTexture(), loaded_textures[id]->getClip(clip), &r);
  }
}

void DisplayManager::renderTileMap(int id, int x, int y, const TileMap* const t) const {
  if (id >= 0 && id < loaded_textures.size()) {
    int tile_size = t->getTileSize();
    for (int j(0); j < t->getHeight(); ++j) {
      for (int i(0); i < t->getWidth(); ++i) {
        int clip = t->getClip(i, j);
        if (clip == -1) continue;
        SDL_Rect r = { x + i * tile_size, y + j * tile_size, tile_size, tile_size };
        SDL_RenderCopy(renderer, loaded_textures[id]->getRawTexture(), loaded_textures[id]->getClip(clip), &r);
      }
    }
  }
}

int DisplayManager::loadText(string text) {
  Texture* t = Texture::fromTTF(renderer, font, text);

  if (t) {
    loaded_textures.push_back(t);
    return static_cast<int>(loaded_textures.size()) - 1;
  } else {
    cout << "Couldn't create Texture object" << endl;
    return -1;
  }
}

int DisplayManager::addTextureClip(int id, int x, int y, int w, int h) {
  if (id >= 0 && id < loaded_textures.size()) {
    return loaded_textures[id]->addClip(x, y, w, h);
  }
  return -1;
}


// Private Methods

// code here
