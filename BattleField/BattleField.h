#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>

#include "../Controller/Controller.h"
#include "../Spell/Spell.h"
#include "../Unit/Unit.h"
#include "../Squad/Squad.h"
class BattleField
{
private:

public:
    BattleField ();
    void runBattle (Controller ctrl);

    void chooseCategory (Controller ctrl);

    void chooseAction   (Controller ctrl);

    void makeAttack     (Controller ctrl);
    
    ~BattleField ();

};

#endif