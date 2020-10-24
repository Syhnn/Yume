#ifndef _DISPLAY_MANAGER_HPP_
#define _DISPLAY_MANAGER_HPP_

#include <cstdint>
#include <string>
#include <vector>


struct SDL_Window;
struct SDL_Rect;
struct SDL_Renderer;

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

class Texture;
class TileMap;


class DisplayManager {
public:
  DisplayManager(int width = 1024, int height = 768);
  ~DisplayManager();

  bool init();

  void clear() const;
  void render() const;

  void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff) const;
  void setClearColor(uint8_t r, uint8_t g, uint8_t b);
  void drawPoint(float x, float y) const;
  void drawLine(float x1, float y1, float x2, float y2) const;

  int loadTexture(std::string path, int w, int h);
  int createTextureFromTilemap(TileMap* const t);
  void initiateTextureCreation(int w, int h);
  int finalizeTexture();
  void renderTexture(int id, int x, int y) const;
  void renderClip(int id, int x, int y, int clip) const;
  void renderTileMap(int id, int x, int y, const TileMap* const t) const;

  int loadText(std::string text);

  int addTextureClip(int id, int x, int y, int w, int h);

  const int WINDOW_WIDTH;
  const int WINDOW_HEIGHT;

private:
  uint8_t cr;
  uint8_t cg;
  uint8_t cb;

  SDL_Window* window;
  SDL_Renderer* renderer;
  Texture* buffer_texture;

  std::vector<Texture*> loaded_textures;

  TTF_Font* font;
};

#endif // _DISPLAY_MANAGER_HPP_
