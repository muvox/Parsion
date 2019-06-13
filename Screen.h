//
// Created by Master on 09/06/2019.
//

#ifndef PARSION_SCREEN_H
#define PARSION_SCREEN_H
#include <SDL.h>

namespace muvoksi {

class Screen {
public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;

public:
    Screen();
    bool init();
    bool processEvents();
    void close();
    void update();
//    void clear();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void setSquare(int width, int height, int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void log(std::string output);
    void boxBlur();
};

} /* namespace muvoksi */


#endif //PARSION_SCREEN_H
