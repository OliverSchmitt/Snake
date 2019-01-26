#include "Defines.hpp"
#include "Direction.hpp"
#include <fstream>
#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

Game::Game() {
    this->running = true;
    this->closed = false;

    this->headX = LEVEL_WIDTH / 2;
    this->headY = LEVEL_HEIGHT / 2;

    this->direction = STOP;

    this->tailLength = 1;
    this->tailX[0] = headX;
    this->tailY[0] = headY - 1;

    std::fstream fs;
    fs.open(SCORE_FILE_NAME, std::fstream::in);

    fs >> maxScore;

    fs.close();

    if (this->maxScore == 0) {
        this->percentToRecord = 1.0;
    } else {
        this->percentToRecord = 0.0;
    }

    srand(time(NULL));

    bool fruitSet = false;
    while (!fruitSet) {
        this->fruitX = rand() % LEVEL_WIDTH + 1;
        this->fruitY = rand() % LEVEL_HEIGHT + 1;
        
        if (this->fruitX != this->headX && this->fruitY != this->headY) {
            fruitSet = true;
        }
    }

    this->headAngle = 180;
    this->tailAngle = 0;

    if ((double) WINDOW_WIDTH/(LEVEL_WIDTH + 2) != TILE_WIDTH) {
        std::cout << "Tile width is not a whole number." << std::endl;
        std::cout << "Verticle stripes are not rendered. Leaving them white." << std::endl;
    }
    if ((double) WINDOW_HEIGHT/(LEVEL_HEIGHT + 2) != TILE_HEIGHT) {
        std::cout << "Tile height is not a whole number." << std::endl;
        std::cout << "Horizontal stripes are not rendered. Leaving them white." << std::endl;
    }
}

void Game::reset() {
    this->running = true;
    this->closed = false;

    this->headX = LEVEL_WIDTH / 2;
    this->headY = LEVEL_HEIGHT / 2;

    this->direction = STOP;

    this->tailLength = 1;
    this->tailX[0] = headX;
    this->tailY[0] = headY - 1;

    std::fstream fs;
    fs.open(SCORE_FILE_NAME, std::fstream::in);

    fs >> maxScore;

    fs.close();

    this->currentRecord->loadTextureFromText(renderData->getRenderer(), std::to_string(this->maxScore));

    if (this->maxScore == 0) {
        this->percentToRecord = 1.0;
    } else {
        this->percentToRecord = 0.0;
    }

    srand(time(NULL));

    bool fruitSet = false;
    while (!fruitSet) {
        this->fruitX = rand() % LEVEL_WIDTH + 1;
        this->fruitY = rand() % LEVEL_HEIGHT + 1;
        
        if (this->fruitX != this->headX && this->fruitY != this->headY) {
            fruitSet = true;
        }
    }

    this->headAngle = 180;
    this->tailAngle = 0;

    if ((double) WINDOW_WIDTH/(LEVEL_WIDTH + 2) != TILE_WIDTH) {
        std::cout << "Tile width is not a whole number." << std::endl;
        std::cout << "Verticle stripes are not rendered. Leaving them white." << std::endl;
    }
    if ((double) WINDOW_HEIGHT/(LEVEL_HEIGHT + 2) != TILE_HEIGHT) {
        std::cout << "Tile height is not a whole number." << std::endl;
        std::cout << "Horizontal stripes are not rendered. Leaving them white." << std::endl;
    }
}

bool Game::loadTextures() {
    this->head = new Texture();
    if (!this->head->loadTextureFromFile(renderData->getRenderer(), HEAD_PATH)) {
        return false;
    }

    this->body = new Texture();
    if (!this->body->loadTextureFromFile(renderData->getRenderer(), BODY_PATH)) {
        return false;
    }

    this->tail = new Texture();
    if (!this->tail->loadTextureFromFile(renderData->getRenderer(), TAIL_PATH)) {
        return false;
    }

    this->wall = new Texture();
    if (!this->wall->loadTextureFromFile(renderData->getRenderer(), WALL_PATH)) {
        return false;
    }

    this->fruit = new Texture();
    if (!this->fruit->loadTextureFromFile(renderData->getRenderer(), FRUIT_PATH)) {
        return false;
    }

    this->score = new Texture();
    if (!this->score->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->score->loadTextureFromText(renderData->getRenderer(), SCORE_TEXT)) {
        return false;
    }

    this->currentScore = new Texture();
    if (!this->currentScore->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->currentScore->loadTextureFromText(renderData->getRenderer(), std::to_string(this->getScore()))) {
        return false;
    }

    this->start = new Texture();
    if (!this->start->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->start->loadTextureFromText(renderData->getRenderer(), START_TEXT)) {
        return false;
    }

    this->record = new Texture();
    if (!this->record->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->record->loadTextureFromText(renderData->getRenderer(), RECORD_TEXT)) {
        return false;
    }

    this->currentRecord = new Texture();
    if (!this->currentRecord->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->currentRecord->loadTextureFromText(renderData->getRenderer(), std::to_string(this->maxScore))) {
        return false;
    }

    this->bar = new Texture();
    if (!this->bar->loadTextureFromFile(renderData->getRenderer(), BAR_PATH)) {
        return false;
    }

    this->barBorder = new Texture();
    if (!this->barBorder->loadTextureFromFile(renderData->getRenderer(), BAR_BORDER_PATH)) {
        return false;
    }

    this->died = new Texture();
    if (!this->died->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->died->loadTextureFromText(renderData->getRenderer(), DIED_TEXT)) {
        return false;
    }

    this->reached = new Texture();
    if (!this->reached->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->reached->loadTextureFromText(renderData->getRenderer(), REACHED_TEXT)) {
        return false;
    }

    this->recordWas = new Texture();
    if (!this->recordWas->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->recordWas->loadTextureFromText(renderData->getRenderer(), RECORD_WAS_TEXT)) {
        return false;
    }

    this->again = new Texture();
    if (!this->again->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->again->loadTextureFromText(renderData->getRenderer(), AGAIN_TEXT)) {
        return false;
    }

    this->yes = new Texture();
    if (!this->yes->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->yes->loadTextureFromText(renderData->getRenderer(), YES_TEXT)) {
        return false;
    }

    this->no = new Texture();
    if (!this->no->loadFont(FONT_PATH, FONT_SIZE)) {
        return false;
    }
    if (!this->no->loadTextureFromText(renderData->getRenderer(), NO_TEXT)) {
        return false;
    }

    return true;
}

bool Game::setup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Could not initialize SDL. SDL error: " << SDL_GetError() << std::endl;
        return false;
    }

    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags) {
        std::cout << "Could not initialize png support. IMG error: " << IMG_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0) {
        std::cout << "Could not initalize TTF. TTF error: " << TTF_GetError() << std::endl;
        return false;
    }

    this->renderData = new RenderData();
    if (!this->renderData->create(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT)) {
       return false; 
    }

    if (!this->loadTextures()) {
        return false;
    }

    return true;
}

void Game::render() {
    SDL_RenderClear(this->renderData->getRenderer());

    for (int x = 0; x < LEVEL_HEIGHT + 2; ++x) {
        SDL_Rect topWall = {x*TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect bottomWall = {x*TILE_WIDTH, (LEVEL_HEIGHT + 1) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        this->wall->render(this->renderData->getRenderer(), NULL, &topWall);
        this->wall->render(this->renderData->getRenderer(), NULL, &bottomWall);
    }

    for (int y = 1; y < LEVEL_HEIGHT + 1; ++y) {
        SDL_Rect leftWall = {0, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect rightWall = {(LEVEL_WIDTH + 1) * TILE_WIDTH, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        this->wall->render(this->renderData->getRenderer(), NULL, &leftWall);
        this->wall->render(this->renderData->getRenderer(), NULL, &rightWall);
    }

    SDL_Rect headPos = {headX*TILE_WIDTH, headY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    this->head->render(this->renderData->getRenderer(), NULL, &headPos, headAngle);

    for (int i = 0; i < tailLength; ++i) {
        SDL_Rect tailPos = {tailX[i] * TILE_WIDTH, tailY[i] * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
        this->body->render(this->renderData->getRenderer(), NULL, &tailPos);
        if (i == tailLength-1) {
            this->tail->render(this->renderData->getRenderer(), NULL, &tailPos, tailAngle);
        }
    }

    SDL_Rect scorePos = {SCORE_X, SCORE_Y, this->score->getWidth(), this->score->getHeight()};
    this->score->render(this->renderData->getRenderer(), NULL, &scorePos);

    this->currentScore->loadTextureFromText(this->renderData->getRenderer(), std::to_string(this->getScore()));
    SDL_Rect currentScorePos = {CURRENT_SCORE_X, CURRENT_SCORE_Y, this->currentScore->getWidth(), this->currentScore->getHeight()};
    this->currentScore->render(this->renderData->getRenderer(), NULL, &currentScorePos);

    if (this->maxScore == 0){
        this->percentToRecord = 1.0;
    } else {
        this->percentToRecord =  (double) this->getScore() / maxScore;
    }
    if (this->percentToRecord > 1.0) {
        this->percentToRecord = 1.0;
    }
    SDL_Rect barPos = {BAR_X, BAR_Y, (int) (percentToRecord * BAR_WIDTH), BAR_HEIGHT};
    this->bar->render(this->renderData->getRenderer(), NULL, &barPos);

    SDL_Rect barBorderPos = {BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT};
    this->barBorder->render(this->renderData->getRenderer(), NULL, &barBorderPos);

    SDL_Rect recordPos = {RECORD_X, RECORD_Y, this->record->getWidth(), this->record->getHeight()};
    this->record->render(this->renderData->getRenderer(), NULL, &recordPos);

    SDL_Rect currentRecordPos = {CURRENT_RECORD_X, CURRENT_RECORD_Y, this->currentRecord->getWidth(), this->currentRecord->getHeight()};
    this->currentRecord->render(this->renderData->getRenderer(), NULL, &currentRecordPos);

    SDL_Rect fruitPos = {fruitX*TILE_WIDTH, fruitY*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    this->fruit->render(this->renderData->getRenderer(), NULL, &fruitPos);

    if (this->direction == STOP) {
        SDL_Rect startPos = {START_X, START_Y, this->start->getWidth(), this->start->getHeight()};
        this->start->render(this->renderData->getRenderer(), NULL, &startPos);
    }

    SDL_RenderPresent(this->renderData->getRenderer());
    SDL_Delay(RENDER_DELAY);
}


void Game::input() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_q:
                case SDLK_ESCAPE:
                    this->running = false;
                    break;

                case SDLK_w:
                case SDLK_UP:
                    if (this->direction != DOWN) {
                        this->direction = UP;
                        this->headAngle = 0;
                        if (this->tailLength < 3) {
                            this->tailAngle = 180;
                        }
                    }
                    break;
 
                case SDLK_a:
                case SDLK_LEFT:
                    if (this->direction != RIGHT) {
                        this->direction = LEFT;
                        this->headAngle = 270;
                        if (this->tailLength < 3) {
                            this->tailAngle = 90;
                        }
                    }
                    break;
 
                case SDLK_s:
                case SDLK_DOWN:
                    if (this->direction != UP) {
                        this->direction = DOWN;
                        this->headAngle = 180;
                        if (this->tailLength < 3) {
                            this->tailAngle = 0;
                        }
                    }
                    break;
 
                case SDLK_d:
                case SDLK_RIGHT:
                    if (this->direction != LEFT) {
                        this->direction = RIGHT;
                        this->headAngle = 90;
                        if (this->tailLength < 3) {
                            this->tailAngle = 270;
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }
}

void Game::update() {
    if (tailLength >= 2) {
        int oneX;
        int oneY;
        int otherX;
        int otherY;
        if (tailLength > 2) {
            oneX = tailX[tailLength - 2];
            oneY = tailY[tailLength - 2];
            otherX = tailX[tailLength - 3];
            otherY = tailY[tailLength - 3];
        }
        else {
            oneX = tailX[tailLength - 1];
            oneY = tailY[tailLength - 1];
            otherX = tailX[tailLength - 2];
            otherY = tailY[tailLength - 2];
//             otherX = headX;
//             otherY = headY;
        }
//         if (otherX < oneX && oneX != LEVEL_WIDTH) {
//             this->tailAngle = 90;
//         }
//         else if (otherX > oneX && oneX != 1) {
//             this->tailAngle = 270;
//         }
//         else if (otherY < oneY && oneY != LEVEL_HEIGHT) {
//             this->tailAngle = 180;
//         }
//         else if (otherY > oneY && oneY != 1) {
//             this->tailAngle = 0;
//         }
        if (otherY - oneY == 0) {
            if (otherX - oneX < 0 && oneX != LEVEL_WIDTH) {
                this->tailAngle = 90;
            } else if (otherX - oneX > 0 && oneX != 1) {
                this->tailAngle = 270;
            }
        } else if (otherX - oneX == 0) {
            if (otherY - oneY < 0 && oneY != LEVEL_HEIGHT) {
                this->tailAngle = 180;
            } else if (otherY - oneY > 0 && oneY != 1) {
                this->tailAngle = 0;
            }
        }
    }
    
    for (int i = tailLength - 1; i > 0; --i) {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    if (tailLength > 0 && direction != STOP) {
        tailX[0] = headX;
        tailY[0] = headY;
    }

    switch (this->direction) {
        case UP:
            headY--;
            if (this->headY == 0) {
                this->headY = LEVEL_HEIGHT;
            }
            break;

        case LEFT:
            headX--;
            if (this->headX == 0) {
                this->headX = LEVEL_WIDTH;
            }
            break;

        case DOWN:
            headY++;
            if (this->headY == LEVEL_HEIGHT + 1) {
                this->headY = 1;
            }
            break;

        case RIGHT:
            headX++;
            if (this->headX == LEVEL_WIDTH + 1) {
                this->headX = 1;
            }
            break;

        default:
        case STOP:
            break;
    }

    if (headX <= 0 || headX >= LEVEL_WIDTH + 1 || headY <= 0 || headY >= LEVEL_HEIGHT + 1) {
        this->running = false;
    }

    for (int i = 0; i < tailLength; ++i) {
        if (headX == tailX[i] && headY == tailY[i]) {
             this->running = false;
        }
    }

    if (headX == fruitX && headY == fruitY) {
        bool fruitSet = false;
        while (!fruitSet) {
            this->fruitX = rand() % LEVEL_WIDTH + 1;
            this->fruitY = rand() % LEVEL_HEIGHT + 1;
            
            if (this->tailLength < 1 && this->headX != this->fruitX && this->headY != this->fruitY) {
                fruitSet = true;
                break;
            }

            for (int i = 0; i < tailLength; ++i) {
                if (this->fruitX == tailX[i] && this->fruitY == tailY[i]) {
                    break;
                } else {
                    if (i == this->tailLength - 1 && this->headX != this->fruitX && this->headY != this->fruitY) {
                        fruitSet = true;
                        break;
                    }
                }
            }
        }

        tailLength += 1;
        tailX[tailLength-1] = tailX[tailLength-2];
        tailY[tailLength-1] = tailY[tailLength-2];
    }
}

void Game::saveScore() {
    if (this->getScore() > this->maxScore) {
        std::fstream fs;
        fs.open (SCORE_FILE_NAME, std::fstream::out);

        fs << this->getScore();

        fs.close();
    }
}

void Game::close() {
    SDL_Delay(500);

    this->score->~Texture();
    this->currentScore->~Texture();
    this->record->~Texture();
    this->currentRecord->~Texture();
    this->bar->~Texture();
    this->barBorder->~Texture();
    this->start->~Texture();
    this->wall->~Texture();
    this->head->~Texture();
    this->body->~Texture();
    this->fruit->~Texture();

    this->died->~Texture();
    this->reached->~Texture();
    this->recordWas->~Texture();
    this->again->~Texture();
    this->yes->~Texture();
    this->no->~Texture();

    this->renderData->~RenderData();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    this->saveScore();
}

void Game::doAfterGame() {
    SDL_RenderClear(this->renderData->getRenderer());

    SDL_Rect diedPos = {WINDOW_WIDTH / 2 - this->died->getWidth() / 2, DIED_Y,
        this->died->getWidth(), this->died->getHeight()};
    this->died->render(this->renderData->getRenderer(), NULL, &diedPos);

    SDL_Rect reachedPos = {REACHED_X, REACHED_Y, this->reached->getWidth(), this->reached->getHeight()};
    this->reached->render(this->renderData->getRenderer(), NULL, &reachedPos);

    SDL_Rect afterScorePos = {REACHED_X + this->reached->getWidth() + 10, REACHED_Y, 
        this->currentScore->getWidth(), this->currentScore->getHeight()};
    this->currentScore->render(this->renderData->getRenderer(), NULL, &afterScorePos);

    SDL_Rect recordWasPos = {RECORD_WAS_X, RECORD_WAS_Y, this->recordWas->getWidth(), this->recordWas->getHeight()};
    this->recordWas->render(this->renderData->getRenderer(), NULL, &recordWasPos);

    SDL_Rect afterRecordPos = {RECORD_WAS_X + this->recordWas->getWidth() + 10, RECORD_WAS_Y, 
        this->currentRecord->getWidth(), this->currentRecord->getHeight()};
    this->currentRecord->render(this->renderData->getRenderer(), NULL, &afterRecordPos);

    SDL_Rect againPos = {WINDOW_WIDTH / 2 - this->again->getWidth() / 2, AGAIN_Y,
        this->again->getWidth(), this->again->getHeight()};
    this->again->render(this->renderData->getRenderer(), NULL, &againPos);

    SDL_Rect yesPos = {WINDOW_WIDTH / 2 - YES_NO_OFFSET - this->yes->getWidth(), YES_Y, 
        this->yes->getWidth(), this->yes->getHeight()};
    this->yes->render(this->renderData->getRenderer(), NULL, &yesPos);

    SDL_Rect noPos = {WINDOW_WIDTH / 2 + YES_NO_OFFSET, NO_Y, 
        this->no->getWidth(), this->no->getHeight()};
    this->no->render(this->renderData->getRenderer(), NULL, &noPos);

    SDL_RenderPresent(this->renderData->getRenderer());
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_y:
                    this->saveScore();
                    this->reset();
                    break;
                case SDLK_n:
                    this->closed = true;
                    break;
            }
        }
    }
}

bool Game::isRunning() {
    return this->running;
}

bool Game::isClosed() {
    return this->closed;
}

int Game::getScore() {
    return (tailLength - 1) * 10;
}
