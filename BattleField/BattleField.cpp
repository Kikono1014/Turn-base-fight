#include "BattleField.h"

BattleField::BattleField ()
{
    categories = { "Attack", "Magic", "Inventory", "Run" };
    spells     = { "Spell1", "Spell2", "Spell3", "Spell4" };
    inventory  = { "Potion1", "Potion2"};
}


void BattleField::runBattle (Controller ctrl)
{
    while (1) {        
        ctrl.updateKey();
        show();
        if (ctrl.getKey() != -1) {
            if (ctrl.isCurrentAction("Exit")) {
                break;
            }

            if        (currentStep == "ChoosingCategory") {
                chooseCategory(ctrl);
            } else if (currentStep == "ChoosingAction") {
                chooseAction(ctrl);
            }
        }        
        delay(1/3);
        clear();
    }
}


void BattleField::delay(double time) {
    #if defined _WIN32
        Sleep(time * 1000);
    #elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
        usleep(time * 1000000);
    #endif
}

void BattleField::clear ()
{
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
}


void BattleField::moveCursorNext (int max)
{
    if (cursor == max) {
        cursor = 0;
    } else {
        cursor++;
    }
}

void BattleField::moveCursorPrev (int max)
{
    if (cursor == 0) {
        cursor = max;
    } else {
        cursor--;
    }
}

void BattleField::checkCursorMoving (Controller ctrl, int max)
{
    if (ctrl.isCurrentAction("CursorNext")) {
        moveCursorNext(categories.size()-1);
    }
    if (ctrl.isCurrentAction("CursorPrev")) {
        moveCursorPrev(categories.size()-1);
    }
}


void BattleField::show () {
    std::cout << currentStep << std::endl;
    std::cout << cursor      << std::endl;
    
    showBattleField ();
    showMenu        ();
    showHeros       ();
    showEnemies     ();
}

void BattleField::showBattleField () {}
void BattleField::showMenu () {
    if (currentStep == "ChoosingCategory") {
        showDirectory(&categories, "Categories");
    }
    if (currentStep == "ChoosingAction") {
        if (currentCategory == "Magic") {
            showDirectory(&spells, "Spells");
        }
        if (currentCategory == "Inventory") {
            showDirectory(&inventory, "Inventory");
        }
    }
}

void BattleField::showDirectory (vector<string> *directory, string name)
{
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < directory->size(); ++i) {
        if (i == cursor) {
            std::cout << " >> ";
        }
        std::cout << "\t" << (*directory)[i]  << std::endl;
    }
}

void BattleField::showHeros () {}
void BattleField::showEnemies () {}

void BattleField::chooseCategory (Controller ctrl)
{
    checkCursorMoving(ctrl, categories.size() - 1);
    if (ctrl.isCurrentAction("Confirm")) {
        currentCategory = categories[cursor];
        currentStep     = "ChoosingAction";
        cursor          = 0;
    }
}

void BattleField::chooseAction (Controller ctrl)
{
    int size { 0 };
    if (currentCategory == "Magic") {
        size = spells.size() - 1;
    }
    if (currentCategory == "Inventory") {
        size = inventory.size() - 1;
    }
    checkCursorMoving(ctrl, size);
    if (ctrl.isCurrentAction("Confirm")) {
        currentCategory = "";
        currentStep     = "Attacking";
        cursor          = 0;
        makeAttack(ctrl);
    }
    if (ctrl.isCurrentAction("Cancel")) {
        currentCategory = "";
        currentStep     = "ChoosingCategory";
        cursor          = 0;
    }
}

void BattleField::makeAttack (Controller ctrl)
{
    
}


BattleField::~BattleField ()
{

}