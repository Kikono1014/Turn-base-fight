#include "BattleField.h"

BattleField::BattleField (Squad heros, Swarm enemies)
{
    categories = { "Attack", "Magic", "Inventory", "Run" };

    this->heros   = heros;
    this->enemies = enemies;
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
    }
    else {
        cursor++;
    }
}

void BattleField::moveCursorPrev (int max)
{
    if (cursor == 0) {
        cursor = max;
    }
    else {
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


vector<string> BattleField::makeNamesList (vector<Hero>  list)
{
    vector<string> names {};
    for (Hero item : list) {
        names.push_back(item.getName());
    }
    return names;
}

vector<string> BattleField::makeNamesList (vector<Enemy> list)
{
    vector<string> names {};
    for (Enemy item : list) {
        names.push_back(item.getName());
    }
    return names;
}

vector<string> BattleField::makeNamesList (vector<Spell> list)
{
    vector<string> names {};
    for (Spell i : list) {
        names.push_back(i.getName());
    }
    return names;
}

// vector<string> BattleField::makeNamesList (vector<Item> list); // TODO to items in inventory


void BattleField::processAction (Controller ctrl)
{
    if (ctrl.getKey() != -1) {
        if (ctrl.currentActionIs("Exit")) {
            isRun = false;
        }
        if (currentStep == "Attacking") {
            if (ctrl.currentActionIs("Confirm")) {
                timers["AttackTimer"].skip();
            }
        }

        if (currentStep == "ChoosingCategory") {
            chooseCategory(ctrl);
            if (currentCategory == "Run") {
                writeAction("Run", heros.getHero(currentHero));
                currentCategory = "";
                currentStep     = "ChoosingCategory";
                cursor          = 0;
                currentHero++;
            }
        }
        else if (currentStep == "ChoosingAction") {
            if (currentCategory == "Attack") {
                chooseAction(ctrl, makeNamesList(enemies.getEnemies()));
            }
            if (currentCategory == "Magic") {
                chooseAction(ctrl, makeNamesList(heros.getHero(currentHero)->getSpells()));
            }
            if (currentCategory == "Inventory") {
                // chooseAction(ctrl, makeNamesList(heros.getInventory()));
                chooseAction(ctrl, heros.getInventory());
            }
        }
        else if (currentStep == "ChoosingMagicTarget") {
            // chooseTarget(ctrl, makeNamesList(heros.getHeros()));
            // chooseTarget(ctrl, makeNamesList(enemies.getEnemies()));
        }

        if (currentHero == heros.getHeros().size()) {
            currentStep = "Attacking";
            timers["AttackTimer"] = Timer(1000);
            currentHero = 0;
        }
    }   
}

void BattleField::show (Controller ctrl) {
    std::cout << heros.getHero(currentHero)->getName()     << std::endl;
    std::cout << currentStep                               << std::endl;
    std::cout << currentCategory                           << std::endl;
    std::cout << ctrl.getKey()                             << std::endl;
    std::cout << cursor                                    << std::endl;
    for (Hero hero : heros.getHeros()) {
        std::cout << hero.getName() << " " << hero.getHP() << std::endl;
    }
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
        showDirectory(categories, "Categories");
    }
    if (currentStep == "ChoosingAction") {
        if (currentCategory == "Attack") {
            showDirectory(makeNamesList(enemies.getEnemies()), "Enemies");
        }
        if (currentCategory == "Magic") {
            showDirectory(makeNamesList(heros.getHero(currentHero)->getSpells()), "Spells");
        }
        if (currentCategory == "Inventory") {
            // showDirectory(makeNamesList(makeNamesList(heros.getInventory()), "Inventory");
            showDirectory(heros.getInventory(), "Inventory");
        }
    }
}

void BattleField::showDirectory (vector<string> directory, string name)
{
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < directory.size(); ++i) {
        if (i == cursor) {
            std::cout << " >> ";
        }
        std::cout << "\t" << directory[i]  << std::endl;
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
        
        if (attackStep == actionsLog.size()) {
            attackStep = 0;
            actionsLog.clear();
            currentStep = "ChoosingCategory";
        }
        else {
            if (actionsLog[attackStep].getType() == "Attack") {
                std::cout << 
                    actionsLog[attackStep].getExecutant()->getName() << " " << 
                    "attack"                                         << " " << 
                    actionsLog[attackStep].getTarget()->getName()
                << std::endl;
            }
            if (actionsLog[attackStep].getType() == "Magic") {
                std::cout << 
                    actionsLog[attackStep].getExecutant()->getName() << " " << 
                    "used"                                           << " " << 
                    actionsLog[attackStep].getUsedSpell()->getName() << " " << 
                    "to"                                             << " " << 
                    actionsLog[attackStep].getTarget()->getName()
                << std::endl;
                actionsLog[attackStep].getUsedSpell()->use(
                        actionsLog[attackStep].getExecutant(),
                        actionsLog[attackStep].getTarget(),
                        actionsLog[attackStep].getUsedSpell()
                    );
            }
            if (actionsLog[attackStep].getType() == "Run") {
                std::cout << 
                    actionsLog[attackStep].getType()                 << " " << 
                    actionsLog[attackStep].getExecutant()->getName()
                << std::endl;
            }
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

void BattleField::chooseAction (Controller ctrl, vector<string> category)
{
    checkCursorMoving(ctrl, category.size() - 1);

    if (ctrl.currentActionIs("Confirm")) {
        if (currentCategory == "Attack") {
            writeAction(currentCategory, heros.getHero(currentHero),
                        enemies.getEnemy(cursor));
        }
        if (currentCategory == "Magic") {
            // currentStep     = "ChoosingMagicTarget";

            writeAction(currentCategory, heros.getHero(currentHero),
                        heros.getHero(currentHero),
                        &(heros.getHero(currentHero)->getSpells()[cursor])
            );
        }
        if (currentCategory == "Run") {
            writeAction(currentCategory, heros.getHero(currentHero));
        }

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

void BattleField::writeAction (string type, Unit* executant)
{
    if (currentCategory == "Run") {
        actionsLog.push_back(Action(type, executant));
    }
}

void BattleField::writeAction (string type, Unit* executant, Unit* target)
{
    if (currentCategory == "Attack") {
        actionsLog.push_back(Action(type, executant, target));
    }
}

// void BattleField::writeAction (string type, Unit* executant, Unit* target, Item* usedItem)
// {
//     if (currentCategory == "Inventory") {
//         actionsLog.push_back(Action(type, executant, target, usedItem));
//     }
// }

void BattleField::writeAction (string type, Unit* executant, Unit* target, Spell* usedSpell)
{
    if (currentCategory == "Magic") {
        actionsLog.push_back(Action(type, executant, target, usedSpell));
    }
    
}

BattleField::~BattleField ()
{

}