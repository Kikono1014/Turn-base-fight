#include "BattleField.h"

BattleField::BattleField ()
{

}


void BattleField::runBattle (Controller ctrl)
{
    while (1) {
        int key { ctrl.getKey() };
        if (key != -1) {
            std::cout << " " << key << std::endl;
            if (key == ctrl.getActionKey("CancelAction")) {
                break;
            }
        }
    }
}

BattleField::~BattleField ()
{

}