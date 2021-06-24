#include <SDL2/SDL.h>

#include <algorithm>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <tuple>

#include "../include/RenderWindow.h"

bool init();

void renderBoxes();

void pollEvent();

void sort();

enum State {
    STOPPED,
    RUNNING,
    SORTING,
    PAUSED,
    COMPLETED,
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

const int NUM_BARS = 100;

RenderWindow window;
State state = STOPPED;

std::vector<SDL_Rect> bars;

int currPos = -1;
int currCheck = -1;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::printf("Failed to intialize SDL2. Error: %s\n", SDL_GetError());
        return false;
    }

    window.create("SDL2 Demo", SCREEN_WIDTH, SCREEN_HEIGHT);

    srand(time(nullptr));

    for (int i = 0; i < NUM_BARS; ++i) {
        int height = rand() % ((SCREEN_HEIGHT / 4) * 3) + 50;

        SDL_Rect bar;
        bar.x = i * SCREEN_WIDTH / NUM_BARS;
        bar.y = SCREEN_HEIGHT - height;
        bar.w = SCREEN_WIDTH / NUM_BARS - 1;
        bar.h = height;

        bars.push_back(bar);
    }

    return true;
}

void renderBoxes() {
    window.clear();

    for (int i = 0; i < NUM_BARS; ++i) {
        bars[i].x = i * SCREEN_WIDTH / NUM_BARS;
//        window.render(&bars[i]);

        if (currPos != -1) {
            if (i < currPos)
                window.render(&bars[i], std::make_tuple<int, int, int>(0, 255, 0));
            else if (i == currCheck)
                window.render(&bars[i], std::make_tuple<int, int, int>(255, 0, 0));
            else if (i == currCheck - 1)
                window.render(&bars[i], std::make_tuple<int, int, int>(255, 255, 0));
            else
                window.render(&bars[i]);
        } else {
            window.render(&bars[i]);
        }
    }

    window.display();
}

void pollEvent() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                state = STOPPED;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        state = STOPPED;
                        break;
                    case SDLK_SPACE:
                        if (state != SORTING)
                            state = SORTING;
                        else
                            state = PAUSED;

                        if (currPos == -1)
                            currPos = 0;

                        break;
                }
                break;
        }
    }
}

void sort() {
    for (; currPos < NUM_BARS; ++currPos) {
        if (state == PAUSED)
            return;

        int swaps = 0;
        for (currCheck = NUM_BARS - 1; currCheck > currPos; --currCheck) {
            if (bars[currCheck].h < bars[currCheck - 1].h) {
                ++swaps;
                SDL_Rect temp = bars[currCheck];
                bars[currCheck] = bars[currCheck - 1];
                bars[currCheck - 1] = temp;
            }

            pollEvent();

            renderBoxes();
            SDL_Delay(30);
        }

        currCheck = -1;
        if (!swaps) {
            currPos = NUM_BARS + 1;
            break;
        }
    }

    state = COMPLETED;
}

int main(int argc, char *argv[]) {
    init();

    state = RUNNING;
    while (state != STOPPED) {
        pollEvent();

        if (state == SORTING)
            sort();

        renderBoxes();
        SDL_Delay(300);
    }

    window.cleanup();
    SDL_Quit();
}