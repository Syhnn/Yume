#include "DisplayManager.hpp"

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"


using namespace std;


// Constructors and destructor

DisplayManager::DisplayManager() :
  window(nullptr),
  renderer(nullptr)
{}

DisplayManager::~DisplayManager() {
  SDL_DestroyWindow(window);
  SDL_Quit();
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

void DisplayManager::clear() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
}

void DisplayManager::render() {
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

int DisplayManager::loadTexture(string path) {
  SDL_Texture* new_texture = nullptr;
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());

  if (loaded_surface == nullptr) {
    cout << "Unable to load image " << path << " - SDL_image Error:\n" << IMG_GetError() << endl;
    return -1;
  } else {
    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (new_texture == nullptr) {
      cout << "Unable to create texture from " << path << " - SDL Error:\n" << SDL_GetError() << endl;
      return -1;
    }
    SDL_FreeSurface(loaded_surface);
  }
  
  loaded_textures.push_back(new_texture);
  return static_cast<int>(loaded_textures.size()) - 1;
}

bool DisplayManager::renderTexture(int id, int x, int y, int w, int h) {
  if (id < 0 || id >= loaded_textures.size()) return false;
  SDL_Rect r = { x, y, w, h };
  SDL_RenderCopy(renderer, loaded_textures[id], NULL, &r);
  return true;
}


// Private Methods

// code here
