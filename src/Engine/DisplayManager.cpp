#include "DisplayManager.hpp"

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "Texture.hpp"


using namespace std;


// Constructors and destructor

DisplayManager::DisplayManager(int width, int height) :
  window(nullptr),
  renderer(nullptr),

  WINDOW_WIDTH(width),
  WINDOW_HEIGHT(height)
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

  window = SDL_CreateWindow("3D Projection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
  
  return true;
}

void DisplayManager::clear() const {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
}

void DisplayManager::render() const {
  SDL_RenderPresent(renderer);
}

void DisplayManager::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void DisplayManager::drawPoint(float x, float y) {
  SDL_RenderDrawPointF(renderer, x, y);
}

void DisplayManager::drawLine(float x1, float y1, float x2, float y2) {
  SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

int DisplayManager::loadTexture(string path, int w, int h) {
  Texture* t = Texture::fromImage(renderer, path, w, h);
  
  loaded_textures.push_back(t);
  return static_cast<int>(loaded_textures.size()) - 1;
}

bool DisplayManager::renderTexture(int id, int x, int y) const {
  if (id < 0 || id >= loaded_textures.size()) return false;
  SDL_Rect r = { x, y, loaded_textures[id]->getWidth(), loaded_textures[id]->getHeight() };
  SDL_RenderCopy(renderer, loaded_textures[id]->getRawTexture(), NULL, &r);
  return true;
}


// Private Methods

// code here
