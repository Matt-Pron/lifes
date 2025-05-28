#ifndef ENTITIES_H
#define ENTITIES_H

#include <array>
#include <string>
#include "indices.h"

struct Entity {
    std::string name;
    int16_t hp;
};

class Entities {
    private:
        std::array<Entity, 16> pjs_;
        std::array<Entity, 16> pnjs_;
        void sortArrays();

    public:
        Entities();
        void add(const Entity* entity, bool table);
        void remove();
        void modifyHP(int16_t i);
        const Entity& getEntity(bool table, uint8_t index) const;
        uint8_t getSize(bool table) const;
};

// Global instances
extern Entities entities;
extern Indices indices;

#endif // ENTITIES_H

