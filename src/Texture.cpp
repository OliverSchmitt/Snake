#include "Defines.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.hpp"

Texture::Texture() {
    this->texture = NULL;
    this->font = NULL;

    this->width = 0;
    this->height = 0;
}

Texture::~Texture() {
    freeTexture();
    freeFont();
}

void Texture::freeTexture() {
    SDL_DestroyTexture(this->texture);
    this->texture = NULL;

    this->width = 0;
    this->height = 0;
}

void Texture::freeFont() {
    TTF_CloseFont(this->font);
    this->font = NULL;
}

bool Texture::loadFont(std::string path, int ptsize) {
    if (this->font != NULL) {
        freeFont();
    }

    this->font = TTF_OpenFont(path.c_str(), ptsize);
    if (this->font == NULL) {
        std::cout << "Could not load font " << path << ". TTF error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Texture::loadTextureFromText(SDL_Renderer* renderer, std::string text, SDL_Color color) {
    if (this->texture != NULL) {
        freeTexture();
    }

    SDL_Surface* tmpSurface = NULL;
    tmpSurface = TTF_RenderText_Blended_Wrapped(this->font, text.c_str(), color, TEXT_WIDTH);
    if (tmpSurface == NULL) {
        std::cout << "Could not create surface for text '" << text << "'. TTF error: " << TTF_GetError() << std::endl;
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    if (this->texture == NULL) {
        std::cout << "Could not create texture for text '" << text << "'. TTF error: " << TTF_GetError() << std::endl;
        return false;
    } else {
        this->width = tmpSurface->w;
        this->height = tmpSurface->h;
    }

    SDL_FreeSurface(tmpSurface);
    tmpSurface = NULL;

    return this->texture != NULL;
}

bool Texture::loadTextureFromFile(SDL_Renderer* renderer, std::string path) {
    if (this->texture != NULL) {
        freeTexture();
    }

    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(path.c_str());
    if (tempSurface == NULL) {
        std::cout << "Could not load surface for " << path << ". IMG error: " << IMG_GetError() << std::endl;
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (this->texture == NULL) {
        std::cout << "Could not create texture for " << path << ". SDL error: " << SDL_GetError() << std::endl;
    }
    else {
        this->width = tempSurface->w;
        this->height = tempSurface->h;
    }

    if (TILE_WIDTH != this->width) {
        std::cout << "Tile width of " << TILE_WIDTH << " does not match width of picture " << path 
            << " of " << this->width << "." << std::endl;
        std::cout << "It is scaled while rendering." << std::endl;
    }
    if (TILE_HEIGHT != this->height) {
        std::cout << "Tile height of " << TILE_HEIGHT << " does not match height of picture " << path 
            << " of " << this->height << "." << std::endl;
        std::cout << "It is scaled while rendering." << std::endl;
    }

    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;

    return this->texture != NULL;
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* position, double angle) {
    if (this->texture == NULL) {
        return;
    }

    SDL_RenderCopyEx(renderer, this->texture, clip, position, angle, NULL, SDL_FLIP_NONE);
}

int Texture::getWidth() {
    return this->width;
}

int Texture::getHeight() {
    return this->height;
}

