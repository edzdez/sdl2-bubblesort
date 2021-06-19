//
// Created by edzdez on 6/19/21.
//

#ifndef SDL2_TEST_RENDERWINDOW_H
#define SDL2_TEST_RENDERWINDOW_H

#include <SDL2/SDL.h>

class RenderWindow {
public:
    RenderWindow();
    void create(const char* p_title, int p_w, int p_h);
    void clear();
    void render(const SDL_Rect* p_rect);
    void display();
    void cleanup();

private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
};


#endif //SDL2_TEST_RENDERWINDOW_H
