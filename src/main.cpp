#include <ncurses.h>
#include "main.h"

int main()
{

    // Cargar datos
    load(entities);

    // Dibujar ventanas
    wm.drawMainWin();

    WINDOW** win = wm.getWin();
    enableInput(win[2]);

    endwin();

    return 0;
}

// string pjs[7] = {"Ani", "Aylu", "Cata", "Jose", "Kari", "Lucho", "Vodo"};
