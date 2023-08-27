#include <iostream>

#include "Timer/Timer.h"
#include "BattleField/BattleField.h"
#include "Controller/Controller.h"
#include "Spell/Spell.h"
#include "Unit/Unit.h"
#include "Hero/Hero.h"
#include "Squad/Squad.h"

Controller ctrl { };

int main ()
{
    Hero h1 {
        "Hero1", "Warrior",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Hero h2 {
        "Hero2", "Warrior",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Hero h3 {
        "Hero3", "Warrior",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Hero h4 {
        "Hero4", "Warrior",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Squad heros { h1, h2, h3, h4 };
    
    BattleField battle { heros };
    battle.runBattle(ctrl);    
    return 0;
}



