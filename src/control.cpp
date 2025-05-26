#include "main.h"
#include <cstddef>
#include <cstdint>
#include <ncurses.h>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

/*
    DEFAULT >> 0
    ADD >> 1
    ADD_NAME >> 10
    ADD_HP >> 100
    RM >> 1000
*/ 

int select(int indices, int ch)
{
    bool table = gettable(indices);
    int8_t indexPJ = iPJ(indices);
    int8_t indexPNJ = iPNJ(indices);
    
        switch (ch) {
            case 'h':
                indices &= 0xFF;
                move(0, 0);
                printw("%d", indices);
                return indices;
            case 'l':
                indices &= 0xFF;
                indices |= (0b1 << 8);
                move(0, 0);
                printw("%d", indices);
                return indices;
            case 'j':
                if (table && indexPNJ < entities.getPNJSize()) {
                    indexPNJ++;
                } else if (!table && indexPJ < entities.getPJSize()) {
                    indexPJ++;
                }
                move(0, 0);
                indices = (table << 8) | ((indexPJ & 0xF) << 4) | (indexPNJ & 0xF);
                printw("%d", indices);
                return (table << 8) | ((indexPJ & 0xF) << 4) | (indexPNJ & 0xF);
            case 'k':
                if (table && indexPNJ > 0) {
                    indexPNJ--;
                } else if (!table && indexPJ > 0) {
                    indexPJ--;
                }
                indices = (table << 8) | ((indexPJ & 0xF) << 4) | (indexPNJ & 0xF);
                printw("%d", indices);
                return (table << 8) | ((indexPJ & 0xF) << 4) | (indexPNJ & 0xF);
            default:
                break;
        }

    return 0;
}

int readInput(const int* mode, const string* input)
{
            // 0  continue listening
            // 5  quit
            // 6  to mode ADD
            // 7  to mode ADD_NAME
            // 8  to mode ADD_HP
            // 9  add entity
            // 10 to mode RM
            // 11 modify hp

    if (input == nullptr || input->empty()) return 0;
    if (*input == "exit" || *input == "quit") return 5;

    switch (*mode) {
        case 0:
            if (*input == "add" || *input == "a") return 6;
            if (*input == "remove" || *input == "r") return 10;

            try {
                size_t pos;
                int hp = stoi(*input, &pos, 10);
                if (pos == input->length() && hp >= 0){
                    return 11;
                }
            }
            catch (...) {
                return 0;
            }

            break;

        case 1:
            if (input == nullptr || input->empty()) return 0;
            if (*input == "pj" || *input == "pnj" ||
                    *input == "j" || *input == "n") return 7;
            break;

        case 0b10:
            if (input == nullptr || input->empty()) return 0;
            return 8;

        case 0b100:
            if (input == nullptr || input->empty()) return 0;
            try {
                size_t pos;
                int hp = stoi(*input, &pos);
                if (pos == input->length() && hp >= 0){
                    return 9;
                }
            }
            catch (...) {
                return 0;
            }
            return 0;

        case 0b1000:
            if (input == nullptr || input->empty()) return 0;
            try {
                size_t pos;
                int i = stoi(*input, &pos);
                if (pos == input->length() && i >= 0){
                    return 12;
                }
            }
            catch (...) {
                return 0;
            }
            return 0;

        default:
            break;
    }

    return 0;
}

int listenSpecials(const int* ch, const int* mode, const string* input)
{
    switch (*ch) {
        case '\n': // return
            return readInput(mode, input);

        case 27: // escape
            return 2; // 2 -> clear input

        case KEY_BACKSPACE:
            return 3; // 3 -> clear last character

        case KEY_F(1):
            return 4; // 4 -> help

        default:
            return 0;
    }
}

int enableInput(WINDOW* win)
{
    wmove(win, 0, 0);
    noecho();
    raw();
    keypad(win, TRUE);
    nodelay(win, TRUE);
    curs_set(2);

    int mode = 0;
    int indices = 0;
    string input;
    int ch;
    bool enabled = true;

    entity newEntity;
    bool newEntityType;
    //int _hp;

    while (enabled)
    {
        wmove(win, 0, 0);
        wclrtoeol(win);
        switch (mode) {
            case 0:
                wprintw(win, "%s",  input.c_str());
                break;
            case 1:
                wprintw(win, "add: %s",  input.c_str());
                break;
            case 0b10:
                wprintw(win, "name: %s",  input.c_str());
                break;
            case 0b100:
                wprintw(win, "hp: %s",  input.c_str());
                break;
            case 0b1000:
                wprintw(win, "remove: %s",  input.c_str());
                break;
        }
        wrefresh(win);

        ch = wgetch(win);

        switch (listenSpecials(&ch, &mode, &input))
        {
            case 0: // continue listening
                break;

            case 1: // clear input
                input.clear();
                break;

            case 2: // reset mode
                input.clear();
                mode = 0;
                break;

            case 3: // backspace
                if (!input.empty()) {
                    input.pop_back();
                }
                break;

            case 4: // help
                help();
                enabled = false;
                break;

            case 5: // quit
                enabled = false;
                break;

            case 6: // to mode ADD
                input.clear();
                mode = 1;
                break;

            case 7: // to mode ADD_NAME
                if (input == "pj" || input == "j") newEntityType = 0;
                else newEntityType = 1;
                input.clear();
                mode = 0b10;
                break;

            case 8: // to mode ADD_HP
                newEntity.name = input;
                input.clear();
                mode = 0b100;
                break;

            case 9: // add entity
                newEntity.hp = stoi(input);
                if (newEntityType == 0){
                    entities.addPJ(newEntity.name, newEntity.hp);
                } else {
                    entities.addPNJ(newEntity.name, newEntity.hp);
                };
                initTables(wm);
                save(entities);
                input.clear();
                mode = 0;
                break;

            case 10: // to mode RM
                input.clear();
                mode = 0b1000;
                break;

            case 11: // modify HP
                newEntity.hp = stoi(input);
                entities.modifyHP(indices, newEntity.hp);
                initTables(wm);
                input.clear();
                mode = 0;
                break;

            case 12: // remove entity
                newEntity.hp = stoi(input);
                entities.remove(0x30);
                initTables(wm);
                input.clear();
                mode = 0;
                break;

            default:
                break;
        }

        switch (mode) {                             // input permitido por modo
            case 0:                                 // DEFAULT
                if (input.length() < 8 &&
                        ((ch == 32) ||              // space
                        (ch == 45) ||               // -
                        (ch >= 48 && ch <= 57) ||   // 0 to 9
                        (ch >= 65 && ch <= 90) ||   // A to Z
                        (ch >= 97 && ch <= 122)))   // a to z
                {
                    input.push_back(ch);
                }
                break;

            case 1:                                 // ADD
                if ((ch == 112 || ch == 110 || ch == 106) && input.length() < 3)
                {
                    input.push_back(ch);
                }
                break;

            case 0b10:                              // ADD_NAME
                if (input.length() < 8 &&
                        ((ch == 32) ||
                        (ch >= 48 && ch <= 57) ||
                        (ch >= 65 && ch <= 90) ||
                        (ch >= 97 && ch <= 122)))
                {
                    input.push_back(ch);
                }
                break;

            case 0b100:                             // ADD_HP
                if (input == "h" || input == "j" ||
                    input == "k" || input == "l")
                    indices = select(indices, ch);
                if (ch >= 48 && ch <= 57 && input.length() < 8)
                {
                    input.push_back(ch);
                }
                break;

            case 0b1000:                            // RM
                if (input == "h" || input == "j" ||
                    input == "k" || input == "l")
                    indices = select(indices, ch);
                if (ch >= 48 && ch <= 57 && input.length() < 8)
                {
                    input.push_back(ch);
                }
                break;

            default:
                break;
        }
    }

    return 0;
}
