#include "data.h"
#include "entities.h"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <linux/limits.h>

std::string getPath() {
    char buf[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len == -1) {
        return "./data/";
    }
    buf[len] = '\0';

    std::string path(buf);
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) {
        return "./data/";
    }
    path = path.substr(0, pos);
    return path + "/data/";
}

void save() {
    std::string pjsPath = getPath() + "pjs.ini";
    std::string pnjsPath = getPath() + "pnjs.ini";
    std::ofstream outFilePj(pjsPath);
    std::ofstream outFilePnj(pnjsPath);

    outFilePj << "[pj]\n";
    for (uint8_t i = 0; i < entities.getSize(0); ++i) {
        outFilePj << entities.getEntity(0, i).name << "=" << std::to_string(entities.getEntity(0, i).hp) << "\n";
    }


    outFilePnj << "[pnj]\n";
    for (uint8_t i = 0; i < entities.getSize(1); ++i) {
        outFilePnj << entities.getEntity(1, i).name << "=" << std::to_string(entities.getEntity(1, i).hp) << "\n";
    }

    outFilePj.close();
    outFilePnj.close();
}

void saveVictims() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y.%m.%d_%H.%M.%S");

    std::string victimsPath = getPath().erase(getPath().length() - 5) + ss.str() + ".ini";
    std::ofstream outFileVictim(victimsPath);

    outFileVictim << "Rest in peace,\n";
    if (entities.getSize(1) == 1) {
        outFileVictim << entities.getEntity(1, entities.getSize(1) - 1).name << ".\n";
    } else if (entities.getSize(1) > 1) {

        for (uint8_t i = 0; i < entities.getSize(1); ++i) {
            if (i < entities.getSize(1) - 2) {
                outFileVictim << entities.getEntity(1, i).name << ",\n";
            } else if (i < entities.getSize(1) - 1) {
                outFileVictim << entities.getEntity(1, i).name << "\n";
            } else if (i == entities.getSize(1) - 1) {
                outFileVictim << "and " << entities.getEntity(1, i).name << ".\n";
            }
        }
    }

    outFileVictim.close();
}

void load() {
    std::string pjsPath = getPath() + "pjs.ini";
    std::string pnjsPath = getPath() + "pnjs.ini";
    std::ifstream inFilePj(pjsPath);
    std::ifstream inFilePnj(pnjsPath);

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

    inFilePj.close();
    inFilePnj.close();
}

