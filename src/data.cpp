#include "data.h"
#include "entities.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <unistd.h>
#include <linux/limits.h>
#include <filesystem>

std::string getPath() {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len == -1) {
        return "./saves/";
    }
    buf[len] = '\0';

    std::string path(buf);
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return "./saves/";
    }
    path = path.substr(0, pos);
    return path + "/saves/";
}

void savePJ() {
    std::string pjsPath = getPath() + "pjs.ini";
    std::ofstream outFilePj(pjsPath);

    outFilePj << "[pj]\n";
    for (uint8_t i = 0; i < entities.getSize(0); ++i) {
        outFilePj << entities.getEntity(0, i).name << "=" << std::to_string(entities.getEntity(0, i).hp) << "\n";
    }

    outFilePj.close();
}

void loadPJ() {
    std::string pjsPath = getPath() + "pjs.ini";
    std::ifstream inFilePj(pjsPath);

    std::string line;
    while (std::getline(inFilePj, line)) {
        if (line.empty()) continue;
        if (line == "[pj]") continue;

        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string name = line.substr(0, pos);
            std::string hpStr = line.substr(pos + 1);

            try {
                int16_t hp = stoi(hpStr);
                Entity newEntity{name, hp};
                entities.add(&newEntity, 0);
            } catch (...) {
                continue;
            }
        }
    }

    inFilePj.close();
}

bool saveEncounter(std::string filename, bool overwrite) {
    if (filename == "pjs") return 0; // Dont overwrite the player characters
    
    std::string pnjsPath = getPath() + filename + ".ini";

    namespace fs = std::filesystem;

    if (!fs::exists(pnjsPath) || overwrite) {
        std::ofstream outFilePnj(pnjsPath);

        outFilePnj << "[pnj]\n";
        for (uint8_t i = 0; i < entities.getSize(1); ++i) {
            outFilePnj << entities.getEntity(1, i).name << "=" << std::to_string(entities.getEntity(1, i).hp) << "\n";
        } 
        outFilePnj.close();
        return 1;
    } else {
        return 0;
    }

}

void loadEncounter(std::string filename) {
    std::string pnjsPath = getPath() + filename + ".ini";
    std::ifstream inFilePnj(pnjsPath);

    std::string line;

    while (std::getline(inFilePnj, line)) {
        if (line.empty()) continue;
        if (line == "[pnj]") continue;

        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string name = line.substr(0, pos);
            std::string hpStr = line.substr(pos + 1);

            try {
                int16_t hp = stoi(hpStr);
                Entity newEntity{name, hp};
                entities.add(&newEntity, 1);
            } catch (...) {
                continue;
            }
        }
    }

    inFilePnj.close();
}
