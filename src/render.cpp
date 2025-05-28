#include "render.h"
#include "entities.h"
#include <cstdint>
#include <cstdlib>
#include <ncurses.h>
#include <string>

#define LOW_HP  1
#define DEAD    2

Render render;

Render::Render() {
    initscr();

    noecho();
    raw();
    keypad(stdscr, true);
    set_escdelay(10);
    nodelay(stdscr, 0);
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        printf("The terminal does not support colors.\n");
        exit(1);
    }

    start_color();
    use_default_colors();
    assume_default_colors(-1, -1);
    init_pair(LOW_HP, COLOR_YELLOW, -1);
    init_pair(DEAD, COLOR_RED, -1);

    /*WINDOW * mainWB;
    WINDOW * mainW;
    WINDOW * inputWB;
    WINDOW * inputW;
    WINDOW * pjsWB;
    WINDOW * pjsW;
    WINDOW * pnjsWB;
    WINDOW * pnjsW;
    WINDOW * helpW;*/
}

Render::~Render() {
    endwin();
}

void Render::openHelp() {
}

void Render::openMainWin() {
    // Main window Border
    getmaxyx(stdscr, scrY, scrX);
    mainWB = newwin(scrY, scrX, 0, 0);
    box(mainWB, 0, 0);
    refresh();
    wattron(mainWB, A_REVERSE);
    wmove(mainWB, 0, 1);
    wprintw(mainWB, " Lifes ");
    wmove(mainWB, 0, scrX-12);
    wprintw(mainWB, " F1: Help ");
    wattroff(mainWB, A_REVERSE);
    wrefresh(mainWB);

    // Main window
    mainW = derwin(mainWB, scrY-2, scrX-2, 1, 1);
    refresh();
    wrefresh(mainW);

    // Input window border
    inputWB = newwin(3, scrX, scrY-3, 0);
    wborder(inputWB, 0, 0, 0, 0, (int)ACS_LTEE, (int)ACS_RTEE, 0, 0);
    refresh();
    wrefresh(inputWB);

    // Pjs window border
    pjsWB = derwin(mainW, scrY-4, 20, 0, 0);
    box(pjsWB, 0, 0);
    mvwprintw(pjsWB, 0, 1, "PJs");
    mvwprintw(pjsWB, 0, 20-4, "HP");
    refresh();
    wrefresh(pjsWB);

    // Pnjs window border
    pnjsWB = derwin(mainW, scrY-4, 20, 0, 20);
    box(pnjsWB, 0, 0);
    mvwprintw(pnjsWB, 0, 1, "PNJs");
    mvwprintw(pnjsWB, 0, 20-4, "HP");
    refresh();
    wrefresh(pnjsWB);

    // Dynamic windows
    pjsW = derwin(pjsWB, scrY-6, 21-3, 1, 1);
    refresh();
    wrefresh(pjsW);
    pnjsW = derwin(pnjsWB, scrY-6, 21-3, 1, 1);
    refresh();
    wrefresh(pnjsW);
    inputW = derwin(inputWB, 1, getmaxx(inputWB)-2, 1, 1);
    refresh();
    wrefresh(inputW);

    pjs();
    pnjs();

}

void Render::both() {
    pjs();
    pnjs();
}

void Render::pjs() {
    for (uint8_t y = 0; y < getmaxy(pjsW); y++) {
        wmove(pjsW, y, 0);
        wclrtoeol(pjsW);
    }

    for(uint8_t i = 0; i < entities.getSize(0); i++) {
        if (!indices.getTable() && i == indices.getIndexPJ())
            wattron(pjsW, A_REVERSE);
        if (entities.getEntity(0, i).hp < 10)
            wattron(pjsW, COLOR_PAIR(LOW_HP));
        if (entities.getEntity(0, i).hp <= 0)
            wattron(pjsW, COLOR_PAIR(DEAD));
        uint8_t maxx = getmaxx(pjsW);
        std::string hp = std::to_string(entities.getEntity(0, i).hp);
        uint8_t hpx = maxx - hp.length();
        /*if (i < 10) {
            mvwprintw(pjsW, i, 1, "%d.", i);
        } else mvwprintw(pjsW, i, 0, "%d.", i);*/
        mvwprintw(pjsW, i, 0, "%s", entities.getEntity(0, i).name.c_str());
        mvwprintw(pjsW, i, hpx, "%s", hp.c_str());
        wrefresh(pjsW);
        if (!indices.getTable() && i == indices.getIndexPJ())
            wattroff(pjsW, A_REVERSE);
        if (entities.getEntity(0, i).hp < 10)
            wattroff(pjsW, COLOR_PAIR(LOW_HP));
        if (entities.getEntity(0, i).hp <= 0)
            wattroff(pjsW, COLOR_PAIR(DEAD));
    }
    wrefresh(pjsW);
}

void Render::pnjs() {
    for (uint8_t y = 0; y < getmaxy(pnjsW); y++) {
        wmove(pnjsW, y, 0);
        wclrtoeol(pnjsW);
    }

    for(uint8_t i = 0; i < entities.getSize(1); i++) {
        if (indices.getTable() && i == indices.getIndexPNJ())
            wattron(pnjsW, A_REVERSE);
        if (entities.getEntity(1, i).hp < 10)
            wattron(pnjsW, COLOR_PAIR(LOW_HP));
        if (entities.getEntity(1, i).hp <= 0)
            wattron(pnjsW, COLOR_PAIR(DEAD));
        uint8_t maxx = getmaxx(pnjsW);
        std::string hp = std::to_string(entities.getEntity(1, i).hp);
        uint8_t hpx = maxx - hp.length();
        /*if (i < 10) {
            mvwprintw(pnjsW, i, 1, "%d.", i);
        } else mvwprintw(pnjsW, i, 0, "%d.", i);*/
        mvwprintw(pnjsW, i, 0, "%s", entities.getEntity(1, i).name.c_str());
        mvwprintw(pnjsW, i, hpx, "%s", hp.c_str());
        wrefresh(pnjsW);
        if (indices.getTable() && i == indices.getIndexPNJ())
            wattroff(pnjsW, A_REVERSE);
        if (entities.getEntity(1, i).hp < 10)
            wattroff(pnjsW, COLOR_PAIR(LOW_HP));
        if (entities.getEntity(1, i).hp <= 0)
            wattroff(pnjsW, COLOR_PAIR(DEAD));
    }
    wrefresh(pnjsW);
}

void Render::print(const std::string& str, bool cursor) {
    cursor ? curs_set(2) : curs_set(0);
    wmove(inputW, 0, 0);
    wclrtoeol(inputW);
    wprintw(inputW, "%s", str.c_str());
    wrefresh(inputW);
}

