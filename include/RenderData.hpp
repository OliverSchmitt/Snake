#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class RenderData {
    private:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        std::string title;
        int x;
        int y;
        int width;
        int height;

    public:
        RenderData();

        ~RenderData();

        bool create(std::string title, int x, int y, int width, int height);

        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
};
