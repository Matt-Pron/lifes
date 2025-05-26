#include "main.h"
#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Entities entities;

void Entities::addPJ(const string& name, int hp)
{
    pjsArr.push_back({name, hp});
}

void Entities::addPNJ(const string& name, int hp)
{
    pnjsArr.push_back({name, hp});
}

bool Entities::removePJ(const string& name)
{
    auto it = find_if(pjsArr.begin(), pjsArr.end(), [&name](const entity& e) {
            return e.name == name; });
    if (it != pjsArr.end()) {
        pjsArr.erase(it);
        return true;
    }
    return false;
}

bool Entities::removePNJ(const string& name)
{
    auto it = find_if(pnjsArr.begin(), pnjsArr.end(), [&name](const entity& e) {
            return e.name == name; });
    if (it != pnjsArr.end()) {
        pnjsArr.erase(it);
        return true;
    }
    return false;
}

string Entities::getPJ(size_t index, bool returnName) const
{
    if (index < pjsArr.size()){
        return returnName ? pjsArr[index].name : to_string(pjsArr[index].hp);
    }
    return returnName ? "" : "0";
}

string Entities::getPNJ(size_t index, bool returnName) const
{
    if (index < pnjsArr.size()){
        return returnName ? pnjsArr[index].name : to_string(pnjsArr[index].hp);
    }
    return returnName ? "" : "0";
}

void Entities::modifyHP(bool type, size_t index, int hp)
{
    if (type) {
        if (index < pnjsArr.size())
            pnjsArr[index].hp += hp;
    } else {
        if (index < pjsArr.size())
            pjsArr[index].hp += hp;
    }
    initTables(wm);
}

uint8_t Entities::getPJSize() const
{
    return pjsArr.size();
}

uint8_t Entities::getPNJSize() const
{
    return pnjsArr.size();
}

