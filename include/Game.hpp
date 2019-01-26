#pragma once

#include "Defines.hpp"
#include "Direction.hpp"
#include "RenderData.hpp"
#include "Texture.hpp"

class Game {
    private:
        bool running;
        bool closed;

        int headX;
        int headY;

        int fruitX;
        int fruitY;

        Direction direction;

        int tailX[LEVEL_WIDTH * LEVEL_HEIGHT];
        int tailY[LEVEL_WIDTH * LEVEL_HEIGHT];
        int tailLength;

        Texture* score;
        Texture* currentScore;

        int maxScore;
        Texture* record;
        Texture* currentRecord;
        Texture* bar;
        Texture* barBorder;
        double percentToRecord;

        Texture* start;

        RenderData* renderData;

        Texture* head;
        double headAngle;
        Texture* body;
        Texture* tail;
        double tailAngle;
        Texture* wall;
        Texture* fruit;

        Texture* died;
        Texture* reached;
        Texture* recordWas;
        Texture* again;
        Texture* yes;
        Texture* no;

    public:
        Game();

        void reset();

        bool loadTextures();

        bool setup();

        void render();
        void input();
        void update();

        void saveScore();

        void close();

        void doAfterGame();

        bool isRunning();
        bool isClosed();

        int getScore();
};
