#include <SDL2/SDL.h>

#include <algorithm>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "../include/RenderWindow.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int NUM_BARS = 100;

RenderWindow window;
std::vector<SDL_Rect> bars;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std:printf("Failed to intialize SDL2. Error: %s\n", SDL_GetError());
        return false;
    }

    window.create("SDL2 Demo", SCREEN_WIDTH, SCREEN_HEIGHT);

    srand(time(nullptr));

    for (int i = 0; i < NUM_BARS; ++i)
    {
        int height = rand() % ((SCREEN_HEIGHT / 4) * 3) + 50;

        SDL_Rect bar;
        bar.x = i * SCREEN_WIDTH / NUM_BARS;
        bar.y = SCREEN_HEIGHT - height;
        bar.w = SCREEN_WIDTH / NUM_BARS - 1;
        bar.h = height;

//        bar.x = i * SCREEN_WIDTH / NUM_BARS;
//        bar.y = SCREEN_HEIGHT - 100;
//        bar.w = SCREEN_WIDTH / NUM_BARS;
//        bar.h = 100;

        bars.push_back(bar);
    }

    return true;
}

void sort() {
    for (int i = 0; i < NUM_BARS; ++i)
    {
        int swaps = 0;
        for (int j = NUM_BARS - 1; j >= 0; --j)
        {
            if (j == i) break;
            if (bars[j].h < bars[j - 1].h)
            {
                ++swaps;
                SDL_Rect temp = bars[j];
                bars[j] = bars[j - 1];
                bars[j - 1] = temp;
            }

            window.clear();
            for (int k = 0; k < NUM_BARS; ++k)
            {
                bars[k].x = k * SCREEN_WIDTH / NUM_BARS;
                window.render(&bars[k]);
            }

            window.display();
            SDL_Delay(30);
        }

        if (!swaps) break;
    }

    std::printf("completed\n");
}

int main(int argc, char* argv[])
{
    init();

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            std::printf("space pushed\n");
                            sort();

                            break;
                    }
                    break;
            }
        }


        window.clear();
        for (int i = 0; i < NUM_BARS; ++i)
        {
            bars[i].x = i * SCREEN_WIDTH / NUM_BARS;
            window.render(&bars[i]);
        }
//        std::printf("\n");

        window.display();
        SDL_Delay(300);
    }

    window.cleanup();
    SDL_Quit();
}