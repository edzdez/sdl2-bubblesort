//
// Created by edzdez on 6/19/21.
//
#include <SDL2/SDL.h>

#include <cstdio>
#include <tuple>

#include "../include/RenderWindow.h"

RenderWindow::RenderWindow()
= default;

void RenderWindow::create(const char* p_title, int p_w, int p_h)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        std::printf("Window failed to init. SDL_ERROR: %s\n", SDL_GetError());

//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::render(const SDL_Rect *p_rect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, p_rect);

//    std::printf("%d, ", p_rect->h);
}

void RenderWindow::render(const SDL_Rect *p_rect, const std::tuple<int, int, int> &p_color) {
    auto[r, g, b] = p_color;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    SDL_RenderFillRect(renderer, p_rect);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

void RenderWindow::cleanup() {
    SDL_DestroyWindow(window);
}
