#ifndef DATA_H
#define DATA_H

#include <string>

std::string getPath();
void save();
void saveVictims();
void load();

void saveEncounter(std::string filename);
void loadEncounter(std::string filename);

#endif // DATA_H

