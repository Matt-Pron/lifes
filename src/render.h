#ifndef RENDER_H
#define RENDER_H

#include <ncurses.h>
#include <string>

class Render {
    private:
        int scrY, scrX;
        WINDOW * mainWB;
        WINDOW * mainW;
        WINDOW * inputWB;
        WINDOW * inputW;
        WINDOW * pjsWB;
        WINDOW * pjsW;
        WINDOW * pnjsWB;
        WINDOW * pnjsW;
        WINDOW * helpW;


    public:
        Render();
        ~Render();
        void openHelp();
        void openMainWin();
        void both();
        void pjs();
        void pnjs();
        void print(const std::string& str, bool cursor);
}; 

extern Render render;

#endif // RENDER_H
