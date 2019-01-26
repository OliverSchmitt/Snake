#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>

class Texture {
    private:
        SDL_Texture* texture;
        TTF_Font* font;
        int width;
        int height;

        void freeTexture();
        void freeFont();

    public:
        Texture();

        ~Texture();

        bool loadFont(std::string path, int ptsize);
        bool loadTextureFromText(SDL_Renderer* renderer, std::string text, SDL_Color = {0, 0, 0, 255});

        bool loadTextureFromFile(SDL_Renderer* renderer, std::string path);

        void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* position, double angle = 0.0);

        int getWidth();
        int getHeight();
};
