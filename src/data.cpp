#include "main.h"
#include <cstddef>
#include <cstdio>
#include <string>
#include <fstream>
#include <unistd.h>
#include <linux/limits.h>

using namespace std;

string getAppDir()
{
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len == -1) {
        return "./data/";
    }
    buf[len] = '\0';

    string path(buf);
    size_t pos = path.find_last_of('/');
    if (pos == string::npos) {
        return "./data/";
    }
    path = path.substr(0, pos);
    return path + "/data/";
}

void save(const Entities& entities)
{
    string iniPath = getAppDir() + "data.ini";
    ofstream outFile(iniPath);

    outFile << "[pj]\n";
    for (size_t i = 0; i < entities.getPJSize(); ++i) {
        outFile << entities.getPJ(i, 1) << "=" << entities.getPJ(i, 0) << "\n";
    }

    outFile << "[pnj]\n";
    for (size_t i = 0; i < entities.getPNJSize(); ++i) {
        outFile << entities.getPNJ(i, 1) << "=" << entities.getPNJ(i, 0) << "\n";
    }

    outFile.close();
}

void load(Entities& entities)
{
    string iniPath = getAppDir() + "data.ini";
    ifstream inFile(iniPath);
    entities = Entities();

    string line;
    bool isPJSection = 0;
    bool isPNJSection = 0;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line == "[pj]") {
            isPJSection = 1;
            isPNJSection = 0;
            continue;
        } else if (line == "[pnj]") {
            isPJSection = 0;
            isPNJSection = 1;
            continue;
        }

        size_t pos = line.find('=');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string hpStr = line.substr(pos + 1);

            try {
                int hp = stoi(hpStr);
                if (isPJSection) {
                    entities.addPJ(name, hp);
                } else if (isPNJSection) {
                    entities.addPNJ(name, hp);
                }
            } catch (...) {
                continue;
            }
        }
    }

    inFile.close();
}

