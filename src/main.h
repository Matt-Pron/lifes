#ifndef MAIN_H
#define MAIN_H

#include <cstddef>
#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

// Entidades
struct entity {
    string name;
    int hp;
};
class Entities {
    private:
        vector<entity> pjsArr;
        vector<entity> pnjsArr;
    public:
        Entities() = default;
        void addPJ(const string& name, int hp);
        void addPNJ(const string& name, int hp);
        void remove(const int& indices);
        string getPJ(size_t index, bool returnName) const;
        string getPNJ(size_t index, bool returnName) const;
        void modifyHP(int indices, int hp);
        uint8_t getPJSize() const;
        uint8_t getPNJSize() const;
};
extern Entities entities;

// Data
string getAppDir();
void save(const Entities& entities);
void load(Entities& entities);
bool gettable(const int& indices);
size_t iPJ(const int& indices);
size_t iPNJ(const int& indices);

// Render
class WindowManager {
    private:
        int scrY, scrX;
        WINDOW * mainWB;
        WINDOW * mainW;
        WINDOW * inputWB;
        WINDOW * pjsWB;
        WINDOW * pnjsWB;

        WINDOW* winArray[4];

    public:
        WindowManager();
        WINDOW** getWin() const;

        void drawMainWin();
        void drawHelpWin();

        void highlight(int indices);
};
extern WindowManager wm;
int initTables(WindowManager& windowmanager);
int help();

// Control
int select(int indices, int ch);
int readInput(const int* mode, const string* input);
string listen(const int* ch);
int listenSpecials(const int* ch, const int* mode, const string* input);
int enableInput(WINDOW* win);

#endif
