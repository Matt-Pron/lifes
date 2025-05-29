#include "control.h"
#include "data.h"
#include "entities.h"
#include "indices.h"
#include "render.h"
#include <cstdint>
#include <ncurses.h>
#include <string>

void modeDefault() {
    std::string input = "";
    render.print(input, 1);
    bool on = 1;

    while (on) {
        int ch = getch();
        curs_set(2);

        if (input.length() < 4 &&
                ((ch == 45) ||
                 (ch >= 48 && ch <= 57)))
            input.push_back(ch);

        navigate(ch);                   // h j k l navigation
        if (ch == 'a') modeAddTable();  // add entity
        if (ch == 'r') modeRemove();  // add entity

        if (ch == 'S') modeEncounter(1);  // save encounter
        if (ch == 'L') modeEncounter(0);  // load encounter

        if (ch == KEY_BACKSPACE && input.length() > 0)
            input.pop_back();               // Erase

        render.print(input, 1);

        if (ch == '\n' && input.length() > 0) {
            uint16_t hp_ = std::stoi(input);
            input = "";
            entities.modifyHP(hp_);
            save();
            saveEncounter(entities.getEncounter());
            indices.getTable() ? render.pnjs() : render.pjs();
            render.print(input, 1);
        }

        if (ch == 'q') quit();          // quit
    }
}

void modeAddTable() {
    std::string str = "Add PJ[h] / PNJ[l]";
    render.print(str, 0);

    bool on = 1;

    while (on) {
        int ch = getch();

        if (ch == 'h') {
            modeAddName(0);         // to add name
            return;
        } else if (ch == 'l') {
            modeAddName(1);         // to add name
            return;
        }

        if (ch == 27) break;       // return to default
        if (ch == 'q') quit();      // quit
    }
}

void modeAddName(const bool table) {
    std::string input = "";
    std::string str;
    table ? str = "PNJ name > " : str = "PJ name > ";
    render.print(str, 1);

    bool on = 1;

    while (on) {
        int ch = getch();

        if (input.length() < 8 &&
                ((ch == 32) ||
                 (ch >= 48 && ch <= 57) ||
                 (ch >= 65 && ch <= 90) ||
                 (ch >= 97 && ch <= 122)))
            input.push_back(ch);

        if (ch == KEY_BACKSPACE && input.length() > 0)
            input.pop_back();

        render.print(str + input, 1);

        if (ch == '\n' && input.length() > 0) {
            modeAddHP(table, input);
            break;
        }
        if (ch == 27) break;       // return to default
    }
}

void modeAddHP(const bool table, const std::string& name) {
    Entity* newEntity = new Entity;
    newEntity->name = name;

    std::string input = "";
    std::string str = name;
    str = str + " HP > ";
    render.print(str, 1);

    bool on = 1;

    while (on) {
        int ch = getch();

        if (input.length() < 4 &&
                ((ch == 45) ||
                (ch >= 48 && ch <= 57)))
            input.push_back(ch);

        if (ch == KEY_BACKSPACE && input.length() > 0)
            input.pop_back();               // Erase

        render.print(str + input, 1);

        if (ch == '\n' && input.length() > 0) {
            uint16_t hp_ = std::stoi(input);
            newEntity->hp = hp_;            // Add the entity
            entities.add(newEntity, table);
            save();
            saveEncounter(entities.getEncounter());
            delete newEntity;
            table ? render.pnjs() : render.pjs();
            break;
        }

        if (ch == 27) break;                // return to default
    }
}

void modeRemove() {
    std::string name = indices.getTable() ?
        entities.getEntity(1, indices.getIndexPNJ()).name :
        entities.getEntity(0, indices.getIndexPJ()).name;
    std::string str = "Confirm to remove " + name + ", [y]es [n]o";
    render.print(str, 1);

    bool on = 1;

    while (on) {
        int ch = getch();

        if (ch == 'y') {
            entities.remove();
            save();
            saveEncounter(entities.getEncounter());
            if (indices.getIndexPNJ() >= entities.getSize(1)) indices.setIndexPNJ(entities.getSize(1) - 1);
            if (indices.getIndexPJ() >= entities.getSize(0)) indices.setIndexPJ(entities.getSize(0) - 1);
            indices.getTable() ? render.pnjs() : render.pjs();
            break;
        }

        if (ch == 27 || ch == 'n') break;                // return to default
        if (ch == 'q') quit();
    }
}

void modeEncounter(bool save) {
    std::string input = "";
    std::string str;
    save ? str = "Save > " : str = "Load > ";
    render.print(str, 1);

    bool on = 1;

    while (on) {
        int ch = getch();

        if (input.length() < 8 &&
                ((ch == 32) ||
                 (ch >= 48 && ch <= 57) ||
                 (ch >= 65 && ch <= 90) ||
                 (ch >= 97 && ch <= 122)))
            input.push_back(ch);

        if (ch == KEY_BACKSPACE && input.length() > 0)
            input.pop_back();

        render.print(str + input, 1);

        if (ch == '\n' && input.length() > 0 && save) {
            saveEncounter(input);
            entities.changeEncounter(input);
            break;
        }

        if (ch == '\n' && input.length() > 0 && !save) {
            entities.changeEncounter(input);
            render.pnjs();
            break;
        }

        if (ch == 27) break;       // return to default
    }

}

void quit() {
        endwin();
        exit(1);
}

bool moveUp() {
    if (!indices.getTable() && indices.getIndexPJ() > 0) {
        indices.setIndexPJ(indices.getIndexPJ() - 1);
        return 1;
    } else if (indices.getTable() && indices.getIndexPNJ() > 0) {
        indices.setIndexPNJ(indices.getIndexPNJ() - 1);
        return 1;
    }
    return 0;
}

bool moveDown() {
    if (!indices.getTable() && indices.getIndexPJ() < entities.getSize(0) - 1) {
        indices.setIndexPJ(indices.getIndexPJ() + 1);
        return 1;
    } else if (indices.getTable() && indices.getIndexPNJ() < entities.getSize(1) - 1) {
        indices.setIndexPNJ(indices.getIndexPNJ() + 1);
        return 1;
    }
    return 0;
}

void navigate(const int& ch) {
    curs_set(0);
    switch (ch) {
        case 'h':
            if (!indices.getTable())
                break;
            indices.setTable(0);
            render.pjs();
            render.pnjs();
            break;
        case 'j':
            if (moveDown())
                indices.getTable() ? render.pnjs() : render.pjs();
            break;
        case 'k':
            if (moveUp())
                indices.getTable() ? render.pnjs() : render.pjs();
            break;
        case 'l':
            if (indices.getTable())
                break;
            indices.setTable(1);
            render.pjs();
            render.pnjs();
            break;
        default:
            break;
    }
}
    
