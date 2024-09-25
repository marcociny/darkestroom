#pragma once
#include <ncurses.h>

void wwborder(WINDOW* win, wchar_t l, wchar_t r, wchar_t t, wchar_t b, wchar_t tl, wchar_t tr, wchar_t bl, wchar_t br) {
    
    int lines = getmaxy(win);
    int cols = getmaxx(win);

    for(int i = 1; i < cols-1; i++) {
        mvwprintw(win, 0, i, "%lc", L'─');
        mvwprintw(win, lines-1, i, "%lc", L'─');
    }
    for(int i = 0; i < lines; i++) {
        mvwprintw(win, i, 0, "%lc", L'│');
        mvwprintw(win, i, cols-1, "%lc", L'│');
    }
    mvwprintw(win, 0, 0, "%lc", L'┌');
    mvwprintw(win, 0, cols-1, "%lc", L'┐');
    mvwprintw(win, lines-1, 0, "%lc", L'└');
    mvwprintw(win, lines-1, cols-1, "%lc", L'┘');
    return;
}