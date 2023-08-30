#include <iostream>

#include "Timer/Timer.h"
#include "BattleField/BattleField.h"
#include "Controller/Controller.h"
#include "Spell/Spell.h"
#include "Unit/Unit.h"
#include "Hero/Hero.h"
#include "Squad/Squad.h"
#include "Enemy/Enemy.h"
#include "Swarm/Swarm.h"

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

    heros.setInventory({ "Item1", "Item2", "Item3", "Item4", "Item5" });
    

    Enemy e1 {
        "Enemy1", "Goblin",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Enemy e2 {
        "Enemy2", "Goblin",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Enemy e3 {
        "Enemy3", "Goblin",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Enemy e4 {
        "Enemy4", "Goblin",
        0, 0,
        50, 0,
        50, 0,
        10, 20, 10, 10, 20
    };

    Swarm enemies { {e1, e2, e3, e4} };

    BattleField battle { heros, enemies };
    battle.runBattle(ctrl);    
    return 0;
}



