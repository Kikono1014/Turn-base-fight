#include "BattleField.h"

BattleField::BattleField ()
{
    categories = { "Attack", "Magic", "Inventory", "Run" };
    spells     = { "Spell1", "Spell2", "Spell3", "Spell4" };
    inventory  = { "Potion1", "Potion2" };

    heros   = { "Hero1", "Hero2", "Hero3" };
    enemies = { "Enemy1", "Enemy2", "Enemy3", "Enemy4" };
}


void BattleField::runBattle (Controller ctrl)
{
    isRun = true;
    while (isRun) {        
        ctrl.updateKey();
        show(ctrl);
        processAction(ctrl);
        delay(0.001);
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
    if (ctrl.currentActionIs("CursorNext")) {
        moveCursorNext(max);
    }
    if (ctrl.currentActionIs("CursorPrev")) {
        moveCursorPrev(max);
    }
}

void BattleField::processAction (Controller ctrl)
{
    if (ctrl.getKey() != -1) {
        if (ctrl.currentActionIs("Exit")) {
            isRun = false;
        }
        if (ctrl.currentActionIs("Confirm")) {
            if (currentStep == "Attacking") {
                timers["AttackTimer"].reset();
            }
        }

        if (currentStep == "ChoosingCategory") {
            chooseCategory(ctrl);
            if (currentCategory == "Run") {
                writeAction(ctrl, heros[currentHero], "runaway");
                currentCategory = "";
                currentStep     = "ChoosingCategory";
                cursor          = 0;
                currentHero++;
            }
        } else
        if (currentStep == "ChoosingAction") {
            if (currentCategory == "Attack") {
                chooseAction(ctrl, &enemies);
            }
            if (currentCategory == "Magic") {
                chooseAction(ctrl, &spells);
            }
            if (currentCategory == "Inventory") {
                chooseAction(ctrl, &inventory);
            }
        }

        if (currentHero == heros.size()) {
            currentStep = "Attacking";
            timers["AttackTimer"] = Timer(1000);
            currentHero = 0;
        }
    }   
}

void BattleField::show (Controller ctrl) {
    std::cout << currentHero     << std::endl;
    std::cout << currentStep     << std::endl;
    std::cout << currentCategory << std::endl;
    std::cout << ctrl.getKey()   << std::endl;
    std::cout << cursor          << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    
    showBattleField ();
    showMenu        ();
    showHeros       ();
    showEnemies     ();
    showAttack      ();
}

void BattleField::showBattleField () {}
void BattleField::showMenu () {
    if (currentStep == "ChoosingCategory") {
        showDirectory(&categories, "Categories");
    }
    if (currentStep == "ChoosingAction") {
        if (currentCategory == "Attack") {
            showDirectory(&enemies, "Enemies");
        }
        if (currentCategory == "Magic") {
            showDirectory(&spells, "Spells");
        }
        if (currentCategory == "Inventory") {
            showDirectory(&inventory, "Inventory");
        }
        if (currentCategory == "Run") {
            std::cout << "HAA" << std::endl;
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

void BattleField::showAttack ()
{
    if (currentStep == "Attacking") {
        timers["AttackTimer"].update();
        if (timers["AttackTimer"].check()) {
            attackStep++;
        }
        
        if (attackStep == herosActionsLog.size()) {
            attackStep = 0;
            currentStep = "ChoosingCategory";
        } else {
            string executant { heros[attackStep] };
            string action    { herosActionsLog[executant][0] };
            string target    { herosActionsLog[executant][1] };
            std::cout << executant << " " << action << " " << target << std::endl;
        }
    }
}

void BattleField::chooseCategory (Controller ctrl)
{
    checkCursorMoving(ctrl, categories.size() - 1);
    if (ctrl.currentActionIs("Confirm")) {
        currentCategory = categories[cursor];
        currentStep     = "ChoosingAction";
        cursor          = 0;
    }
    if (ctrl.currentActionIs("Cancel")) {
        currentHero--;
        if (currentHero < 0) {
            currentHero = 0;
        }
        cursor          = 0;
    }
}

void BattleField::chooseAction (Controller ctrl, vector<string> *category)
{
    checkCursorMoving(ctrl, category->size() - 1);

    if (ctrl.currentActionIs("Confirm")) {
        writeAction(ctrl, heros[currentHero], (*category)[cursor]);
        currentCategory = "";
        currentStep     = "ChoosingCategory";
        cursor          = 0;

        currentHero++;
    }
    if (ctrl.currentActionIs("Cancel")) {
        currentCategory = "";
        currentStep     = "ChoosingCategory";
        cursor          = 0;
    }
}

void BattleField::writeAction (Controller ctrl, string executant, string target)
{
    if (currentCategory == "Attack") {
        herosActionsLog[executant] = { "attack", target };
    }
    if (currentCategory == "Magic") {
        herosActionsLog[executant] = { "magic",  target };
    }
    if (currentCategory == "Inventory") {
        herosActionsLog[executant] = { "use",    target };
    }
    if (currentCategory == "Run") {
        herosActionsLog[executant] = { "run",    target };
    }
}

BattleField::~BattleField ()
{

}