#include "main.h"
#include <cstdint>
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

void Entities::remove(const int& indices)
{
    bool table = gettable(indices);

    if (table) {
        if (iPNJ(indices) < pnjsArr.size())
            pnjsArr.erase(pnjsArr.begin() + iPNJ(indices));
    } else {
        if (iPJ(indices) < pjsArr.size())
            pjsArr.erase(pjsArr.begin() + iPJ(indices));
    }
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

void Entities::modifyHP(int indices, int hp)
{
    bool pnj = gettable(indices);
    size_t indexPJ = iPJ(indices);
    size_t indexPNJ = iPNJ(indices);
    
    if (pnj) {
        if (indexPNJ < pnjsArr.size()) {
            pnjsArr[indexPNJ].hp += hp;
        } else if (indexPJ < pjsArr.size()) {
            pjsArr[indexPJ].hp += hp;
        }
    }
}

uint8_t Entities::getPJSize() const
{
    return pjsArr.size();
}

uint8_t Entities::getPNJSize() const
{
    return pnjsArr.size();
}

