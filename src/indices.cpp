#include "indices.h"

void Indices::setIndexPNJ(uint8_t i) {
    if (i <= 15) bits_ = (bits_ & 0xFFF0) | (i & 0x0F);
}

void Indices::setIndexPJ(uint8_t i) {
    if (i <= 15) bits_ = (bits_ & 0xFF0F) | ((i & 0x0F) << 4);
}

void Indices::setTable(bool i) {
    bits_ = (bits_ & 0xFEFF) | (static_cast<uint16_t>(i) << 8);
}

uint8_t Indices::getIndexPNJ() const {
    return bits_ & 0x0F;
}

uint8_t Indices::getIndexPJ() const {
    return (bits_ >> 4) & 0x0F;
}

bool Indices::getTable() const {
    return (bits_ >> 8) & 0x01;
}

