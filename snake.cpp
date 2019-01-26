#include <iostream>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////

// Stops the game loop if false.
bool running;

// The dimensions of the game.
// Need to be multiples of 2 for the starting point of the head.
const int width = 20;
const int height = 10;

// The position of the head of the snake and the fruit.
int headX, headY;
int fruitX, fruitY;

// The postions of the tail.
int tailX[100], tailY[100];
int tailLength;

// Enum for the direcction that the snake is moving.
enum Direction {
    STOP,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
// The direction the snake is currently moving.
Direction direction;

// The archived score.
int score;

////////////////////////////////////////////////////////////////

// Runs before the game starts.
void setup() {
    // Game runs.
    running = true;

    // Center the snake head.
    headX = width / 2;
    headY = height / 2;

    // Set the rng seed.
    srand (time(NULL));

    // Random position for the fuit.
    fruitX = rand() % width;
    fruitY = rand() % height;

    tailLength = 0;

    // Wait for a keypress before stating the game.
    direction = STOP;

    // Start score.
    score = 0;

    // Initialize ncurses.
    initscr();
    noecho();
    cbreak();
    // Make getch() non-blocking.
    timeout(0);
}

// "Render" the game.
void draw() {
    // Clear the sscreen.
    clear();

    // Top wall.
    for (int x = -1; x < width+1; ++x)
        printw("#");
    printw("\n");

    for (int y = 0; y < height; ++y) {
        for (int x = -1; x < width+1; ++x) {
            // Left Wall.
            if (x == -1) {
                printw("#");
                continue;
            }
            // Right wall.
            if (x == width) {
                printw("#");
                continue;
            }

            // Head of the snake.
            if (x == headX && y == headY) {
                printw("O");
                continue;
            }

            bool printed = false;
            for (int i = 0; i < tailLength; ++i) {
                if (x == tailX[i] && y == tailY[i]) {
                    printw("o");
                    printed = true;
                }
            }
            if (printed)
                continue;
 
            // Fruit position.
            if (x == fruitX && y == fruitY) {
                printw("X");
                continue;
            }

            // Nothing.
            printw(" ");
        }
        printw("\n");
    }

    // Bottom wall.
    for (int x = -1; x < width+1; ++x)
        printw("#");
    printw("\n");
    
    // Print the score.
    printw("Score: %d\n", score);
    
    // Update the screen.
    refresh();
}

// Get and handle the user input.
void input() {
    // Get non-blocking user input.
    int input = getch();
    // Change direction based on the input.
    switch (input) {
        case 'w':
            direction = UP;
            break;
        case 'a':
            direction = LEFT;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'q':
            running = false;
            break;
        default:
            break;
    }

}

// Update all variables.
void update() {
    // Update the tail positions.
    if (tailLength > 0) {
        for (int i = tailLength-1; i > 0; --i) {
            tailX[i] = tailX[i-1];
            tailY[i] = tailY[i-1];
        }
        tailX[0] = headX;
        tailY[0] = headY;
    }

    // Update the head position.
    switch (direction) {
        case STOP:
            break;
        case UP:
            headY--;
            break;
        case LEFT:
            headX--;
            break;
        case DOWN:
            headY++;
            break;
        case RIGHT:
            headX++;
            break;
        default:
            break;
    }

    // Test if the snake hit a wall.
    if (headX < 0 || headX >= width || headY < 0 || headY >= height) {
        running = false;
        return;
    }

    // Test if the snake hit itself.
    for (int i = 0; i < tailLength; ++i) {
        if (headX == tailX[i] && headY == tailY[i]) {
            running = false;
            return;
        }
    }

    // The snake ate the fruit.
    if (headX == fruitX && headY == fruitY) {
        // Increase the score.
        score += 1;

        // Generate new fruit.
        fruitX = rand() % width;
        fruitY = rand() % height;

        // Increase the snake lenght.
        tailLength += 1;
        // If initialized with 0 the new tail shows in the top left corner for 1 frame.
        tailX[tailLength-1] = -1;
        tailY[tailLength-1] = -1;
    }
}

// Executed after the game.
void close() {
    endwin();
}

////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    setup();
    while (running) {
        draw();
        input();
        update();
        // Make the game slower.
        // The character size is not quadratic.
        if (direction == LEFT || direction == RIGHT) {
            usleep(65000);
        }
        else {
            usleep(100000);
        }
    }

    close();

    return 0;
}
