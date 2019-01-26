#include <iostream>
#include "RenderData.hpp"
#include "SDL2/SDL.h"

RenderData::RenderData() {
    (*this).window = NULL;
    (*this).renderer = NULL;

    (*this).title = "";
    (*this).x = 0;
    (*this).y = 0;
    (*this).width = 0;
    (*this).height = 0;
}

RenderData::~RenderData() {
    SDL_DestroyWindow((*this).window);
    (*this).window = NULL;
    SDL_DestroyRenderer((*this).renderer);
    (*this).renderer = NULL;

    (*this).title = "";
    (*this).x = 0;
    (*this).y = 0;
    (*this).width = 0;
    (*this).height = 0;
}

bool RenderData::create(std::string title, int x, int y, int width, int height) {
    (*this).window = SDL_CreateWindow(title.c_str(), x, y, width, height, 0);
    if ((*this).window == NULL) {
        std::cout << "Could not create window " << title << ". SDL error: " << SDL_GetError() << std::endl;
        return false;
    }

    (*this).renderer = SDL_CreateRenderer((*this).window, -1, SDL_RENDERER_PRESENTVSYNC);
    if ((*this).renderer == NULL) {
        std::cout << "Could not create renderer for " << title << ". SDL error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor((*this).renderer, 255, 255, 255, 255);

    return true;
}

SDL_Window* RenderData::getWindow() {
    return (*this).window;
}

SDL_Renderer* RenderData::getRenderer() {
    return (*this).renderer;
}
