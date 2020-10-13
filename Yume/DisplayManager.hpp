#ifndef _DISPLAY_MANAGER_HPP_
#define _DISPLAY_MANAGER_HPP_

#include <cstdint>
#include <string>
#include <vector>


struct SDL_Window;
struct SDL_Rect;
struct SDL_Renderer;

class Texture;


const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


class DisplayManager {
public:
  DisplayManager();
  ~DisplayManager();

  bool init();

  void clear() const;
  void render() const;

  void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
  void drawPoint(float x, float y);
  void drawLine(float x1, float y1, float x2, float y2);

  int loadTexture(std::string path, int w, int h);
  bool renderTexture(int id, int x, int y) const;

private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  std::vector<Texture*> loaded_textures;
};

#endif // _DISPLAY_MANAGER_HPP_
