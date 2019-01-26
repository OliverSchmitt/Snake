#include <ncurses.h>

int main() {
    initscr();
    noecho();
    cbreak();
    timeout(0);
    printw("Hello World !!!\n");
    refresh();
    int c = getch();
    if (c == 'q') {
        printw("q");
    }
    refresh();
    getch();
    endwin();

    return 0;
}
