#include <ncurses.h>
#include "main.h"

//int main(int argc, char ** argv)
int main()
{

    // Cargar datos
    load(entities);

    // Dibujar ventanas
    wm.drawMainWin();
    //initTables(wm);

    // Mover cursor al input
    WINDOW** win = wm.getWin();
    enableInput(win[2]);

    endwin();

    return 0;
}

/*
    string pjs[7] = {"Ani", "Aylu", "Cata", "Jose", "Kari", "Lucho", "Vodo"};
    int keypressPJ;
    int highlight = 0;

    while (1)
    {
        for(int i = 0; i < 7; i++)
        {
            if (i == highlight)
                wattron(pjsW, A_REVERSE);
            mvwprintw(pjsW, i+1, 1, pjs[i].c_str());
            mvwprintw(pjsW, i+1, 10, "16");
            mvwprintw(pjsW, i+1, 15, "12");
            wattroff(pjsW, A_REVERSE);
        }
        keypressPJ = wgetch(pjsW);

        switch (keypressPJ) {
            case 'k':
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case 'j':
                highlight++;
                if (highlight == 7)
                    highlight = 6;
                break;
            default:
                break;
        }
        if(keypressPJ == 10)
            break;
    }

    wclear(inputW);
    mvwprintw(inputW, 0, 0, "Eleccion: %s", pjs[highlight].c_str());
    refresh();
    wrefresh(inputW);

    return 0;
}

*/
