#include <iostream>

#include "Controller/Controller.h"
#include "Spell/Spell.h"
#include "Unit/Unit.h"
#include "Squad/Squad.h"

Controller controller { };

int main ()
{
    while (1) {
        int key { controller.getKey() };
        if (key != -1) {
            std::cout << " " << key << std::endl;
            if (key == controller.getActionKey("CancelAction")) {
                break;
            }
        }
    }
    
    return 0;
}



