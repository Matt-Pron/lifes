#include "main.h"
#include "control.h"
#include "render.h"

// TODO Configurar NCurses
// TODO Repensar modos

/*      Indices ya funciona con indices.method()
            setIndexPNJ(uint8_t i), setIndexPJ(uint8_t i), setTable(bool i)
            uint8_t getIndexPNJ(), uint8_t getIndexPJ() y bool getTable()
        Entities ya funciona con entities.method()
            add(const Entity* entity, bool table), remove(), modifyHP(int16_t i)
            Entity& getEntity(bool table, uint8_t index)
            uint8_t getSize(bool table)
        Data ya funciona con save(), load() y saveVictims() */

int main()
{
    render.openMainWin();
    modeDefault();
    return 0;
}
