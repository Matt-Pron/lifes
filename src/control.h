#ifndef CONTROL_H
#define CONTROL_H

#include <string>

void modeDefault();
void modeAddTable();
void modeAddName(const bool table);
void modeAddHP(const bool table, const std::string& name);

void modeRemove();

void quit();

bool moveUp();
bool moveDown();
void navigate(const int& ch);

#endif // CONTROL_H
