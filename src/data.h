#ifndef DATA_H
#define DATA_H

#include <string>

std::string getPath();
void savePJ();
void loadPJ();

bool saveEncounter(std::string filename, bool overwrite);
void loadEncounter(std::string filename);

#endif // DATA_H

