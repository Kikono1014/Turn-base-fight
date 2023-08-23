#include <iostream>

#include "Timer/Timer.h"
#include "BattleField/BattleField.h"
#include "Controller/Controller.h"
#include "Spell/Spell.h"
#include "Unit/Unit.h"
#include "Squad/Squad.h"

Controller ctrl { };

int main ()
{
    BattleField battle {  };
    battle.runBattle(ctrl);    
    return 0;
}



