#ifndef INDICES_H
#define INDICES_H

#include <cstdint>

class Indices {
    private:
        uint16_t bits_ = 0;

    public:
        void setIndexPNJ(uint8_t i);
        void setIndexPJ(uint8_t i);
        void setTable(bool i);
        uint8_t getIndexPNJ() const;
        uint8_t getIndexPJ() const;
        bool getTable() const;
};

#endif // INDICES_H

