#include <cstddef>
#include <ncurses.h>
#include "main.h"

WindowManager wm;

WindowManager::WindowManager()
{
    // Iniciar NCurses
    set_escdelay(10);
    initscr();
    noecho();
    keypad(stdscr, true);
}

void WindowManager::drawMainWin()
{
    // Draw main window border
    int scrY, scrX;
    getmaxyx(stdscr, scrY, scrX); // Get screen size
    WINDOW * mainWB = newwin(scrY, scrX, 0, 0);
    box(mainWB, 0, 0);
    refresh();
    wattron(mainWB, A_REVERSE);
    wmove(mainWB, 0, 1);
    wprintw(mainWB, " Lifes ");
    wmove(mainWB, 0, scrX-12);
    wprintw(mainWB, " F1: Help ");
    wattroff(mainWB, A_REVERSE);
    wrefresh(mainWB);

    // Draw main window content
    WINDOW * mainW = derwin(mainWB, scrY-2, scrX-2, 1, 1);
    refresh();
    wrefresh(mainW);

    // Window Input Border
    WINDOW * inputWB = newwin(3, scrX, scrY-3, 0);
    wborder(inputWB, 0, 0, 0, 0, (int)ACS_LTEE, (int)ACS_RTEE, 0, 0);
    refresh();
    wrefresh(inputWB);

    // Window Pcs Border
    WINDOW * pjsWB = newwin(scrY-4, 20, 1, 1);
    box(pjsWB, 0, 0);
    mvwprintw(pjsWB, 0, 1, "PJs");
    mvwprintw(pjsWB, 0, 20-5, "HP");
    refresh();
    wrefresh(pjsWB);

    // Window Npcs Border
    WINDOW * pnjsWB = newwin(scrY-4, 20, 1, 21);
    box(pnjsWB, 0, 0);
    mvwprintw(pnjsWB, 0, 1, "PNJs");
    mvwprintw(pnjsWB, 0, 20-5, "HP");
    refresh();
    wrefresh(pnjsWB);
    
    // Ventanas dinamicas
    winArray[0] = derwin(pjsWB,scrY-5,21-2,0,0); // PJ
    refresh();
    wrefresh(winArray[0]);
    winArray[1] = derwin(pnjsWB,scrY-5,21-2,0,0); // PNJ
    refresh();
    wrefresh(winArray[1]);
    winArray[2] = derwin(inputWB, 1, scrY-5, 1, 1); // Input
    refresh();
    wrefresh(winArray[2]);

    initTables(wm);

}

void WindowManager::drawHelpWin()
{
}

void highlight(int indices)
{
    WINDOW** win = wm.getWin();

    bool table = gettable(indices);
    size_t indexPJ = iPJ(indices);
    size_t indexPNJ = iPNJ(indices);

    wclear(win[0]);
    if (!table) {
        wmove(win[0], 0, 0);
        for(size_t i = 0; i < entities.getPJSize(); i++)
        {
            if (i == indexPJ)
                wattron(win[0], A_REVERSE);
            int maxx = getmaxx(win[0]);
            string hp = entities.getPJ(i, 0).c_str();
            int hpx = maxx - hp.length();
            if (i < 10){
                mvwprintw(win[0], i+1, 2, "%zu", i);
            } else mvwprintw(win[0], i+1, 1, "%zu", i);
            mvwprintw(win[0], i+1, 4, "%s", entities.getPJ(i, 1).c_str());
            mvwprintw(win[0], i+1, hpx, "%s", hp.c_str());
            wattroff(win[0], A_REVERSE);
        }
        wrefresh(win[0]);
    }

    wclear(win[1]);
    if (table) {
        for(size_t i = 0; i < entities.getPNJSize(); i++)
        {
            if (i == indexPNJ)
                wattron(win[1], A_REVERSE);
            int maxx = getmaxx(win[1]);
            string hp = entities.getPNJ(i, 0).c_str();
            int hpx = maxx - hp.length();
            if (i < 10){
                mvwprintw(win[1], i+1, 2, "%zu", i);
            } else mvwprintw(win[1], i+1, 1, "%zu", i);
            mvwprintw(win[1], i+1, 4, "%s", entities.getPNJ(i, 1).c_str());
            mvwprintw(win[1], i+1, hpx, "%s", hp.c_str());
            wattroff(win[1], A_REVERSE);
        }
        wrefresh(win[1]);
    }
}

WINDOW** WindowManager::getWin() const
{
    return const_cast<WINDOW**>(winArray);
}

int initTables(WindowManager& windowmanager)
{

    WINDOW** win = windowmanager.getWin();
    WINDOW* pjs = win[0];
    WINDOW* pnjs = win[1];

    wmove(pjs, 0, 0);
    for(size_t i = 0; i < entities.getPJSize(); i++)
    {
        int maxx = getmaxx(pjs);
        string hp = entities.getPJ(i, 0).c_str();
        int hpx = maxx - hp.length();
        if (i < 10){
        mvwprintw(pjs, i+1, 2, "%zu", i);
        } else mvwprintw(pjs, i+1, 1, "%zu", i);
        mvwprintw(pjs, i+1, 4, "%s", entities.getPJ(i, 1).c_str());
        mvwprintw(pjs, i+1, hpx, "%s", hp.c_str());
        wrefresh(pjs);
    }

    wmove(pnjs, 0, 0);
    for(size_t w = 0; w < entities.getPNJSize(); w++)
    {
        int maxx = getmaxx(pnjs);
        string hp = entities.getPNJ(w, 0).c_str();
        int hpx = maxx - hp.length();
        if (w < 10){
        mvwprintw(pnjs, w+1, 2, "%zu", w);
        } else mvwprintw(pnjs, w+1, 1, "%zu", w);
        mvwprintw(pnjs, w+1, 4, "%s", entities.getPNJ(w, 1).c_str());
        mvwprintw(pnjs, w+1, hpx, "%s", hp.c_str());
        wrefresh(pnjs);
    }

    return 0;
}

int help()
{
    return 0;
}

