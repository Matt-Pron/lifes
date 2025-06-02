#include <algorithm>
#include <ncurses.h>
#include "entities.h"
#include "data.h"

Entities entities;
Indices indices;

Entities::Entities() {
    encounter_ = "pnjs";
    loadPJ();
    loadEncounter(encounter_);
}

void Entities::sortArrays() {
    auto sortArray = [](std::array<Entity, 16>& arr) {
        std::sort(arr.begin(), arr.end(), [](const Entity& a, const Entity& b) {
                if (a.name.empty() && b.name.empty()) return false;
                if (a.name.empty()) return false;
                if (b.name.empty()) return true;
                return a.name < b.name;
                });
    };
    sortArray(pjs_);
    sortArray(pnjs_);
}

void Entities::add(const Entity* entity, bool table) {
    if (!entity || entity->name.empty()) return;
    auto& arr = (table == 1) ? pnjs_ : pjs_;
    for (auto& slot : arr) {
        if (slot.name.empty()) {
            slot = *entity;
            break;
        }
    }
    sortArrays();
}

void Entities::remove() {
    auto& arr = indices.getTable() ? pnjs_ : pjs_;
    uint8_t index = indices.getTable() ? indices.getIndexPNJ() : indices.getIndexPJ();
    if (index < 16) {
        arr[index].name = "";
    }
    sortArrays();
}

void Entities::modifyHP(int16_t i) {
    auto& arr = indices.getTable() ? pnjs_ : pjs_;
    uint8_t index = indices.getTable() ? indices.getIndexPNJ() : indices.getIndexPJ();
    if (index < 16) {
        arr[index].hp += i;
    }
}

const Entity& Entities::getEntity(bool table, uint8_t index) const {
    static const Entity defaultEntity{};
    if (index >= 16) return defaultEntity;
            return (table == 1) ? pnjs_[index] : pjs_[index];
}

uint8_t Entities::getSize(bool table) const {
    const auto& arr = (table == 1) ? pnjs_ : pjs_;
    uint8_t count = 0;
    for (const auto& entity : arr) {
        if (!entity.name.empty()) count++;
    }
    return count;
}

void Entities::changeEncounter(std::string encounter) {
    encounter_ = encounter;

    for (uint8_t i = 0; i < 16; i++) {
        pnjs_[i].name = "";
    }

    loadEncounter(encounter_);
}

const std::string& Entities::getEncounter() const {
    return encounter_;
}

