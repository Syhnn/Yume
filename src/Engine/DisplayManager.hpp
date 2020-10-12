#ifndef _DISPLAY_MANAGER_HPP_
#define _DISPLAY_MANAGER_HPP_

#include <cstdint>
#include <string>
#include <vector>


struct SDL_Window;
struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


class DisplayManager {
public:
  DisplayManager();
  ~DisplayManager();

  bool init();

  void clear();
  void render();

  void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
  void drawPoint(float x, float y);
  void drawLine(float x1, float y1, float x2, float y2);

  int loadTexture(std::string path);
  bool renderTexture(int id, int x, int y, int w, int h);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  std::vector<SDL_Texture*> loaded_textures;
};

#endif // _DISPLAY_MANAGER_HPP_
