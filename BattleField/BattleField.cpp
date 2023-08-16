#include "BattleField.h"

BattleField::BattleField ()
{

}


void BattleField::runBattle (Controller ctrl)
{
    while (1) {
        ctrl.updateKey();
        if (ctrl.getKey() != -1) {
            std::cout << " " << ctrl.getKey() << std::endl;
            chooseCategory (ctrl);
            chooseAction (ctrl);
            makeAttack (ctrl);
            if (ctrl.isCurrentAction("CancelAction")) {
                break;
            }
        }
    }
}

void BattleField::chooseCategory (Controller ctrl)
{

}

void BattleField::chooseAction (Controller ctrl)
{

}

void BattleField::makeAttack (Controller ctrl)
{

}


BattleField::~BattleField ()
{

}