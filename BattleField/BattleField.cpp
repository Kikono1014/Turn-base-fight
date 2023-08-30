#include "BattleField.h"

BattleField::BattleField (Squad heros, Swarm enemies)
{
    // categories = { "Attack", "Magic", "Inventory", "Run" };

    categories = { "Attack", "Magic" };

    // spells     = { "Spell1", "Spell2", "Spell3", "Spell4" };
    // inventory  = { "Potion1", "Potion2" };

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

// vector<string> BattleField::makeNamesList (vector<Spell> list)
// {
//     vector<string> names {};
//     for (Spell i : list) {
//         names.push_back(i.getName());
//     }
//     return names;
// }
// TODO to spells

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
            // if (currentCategory == "Run") {
            //     // writeAction(ctrl, heros.getHero(currentHero));
            //     currentCategory = "";
            //     currentStep     = "ChoosingCategory";
            //     cursor          = 0;
            //     currentHero++;
            // }
        } else
        if (currentStep == "ChoosingAction") {
            if (currentCategory == "Attack") {
                chooseAction(ctrl, makeNamesList(enemies.getEnemies()));
            }
            if (currentCategory == "Magic") {
                // chooseAction(ctrl, makeNamesList(heros.getHero(currentHero)->getSpells()));
                chooseAction(ctrl, heros.getHero(currentHero)->getSpells());
            }
            // if (currentCategory == "Inventory") {
            //     chooseAction(ctrl, &inventory);
            // }
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
            // showDirectory(makeNamesList(heros.getHero(currentHero)->getSpells()));
            showDirectory(heros.getHero(currentHero)->getSpells(), "Spells");
        }
        // if (currentCategory == "Inventory") {
        //     showDirectory(&inventory, "Inventory");
        // }
        // if (currentCategory == "Run") {
        //     std::cout << "HAA" << std::endl;
        // }
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
    // if (currentStep == "Attacking") {
    //     timers["AttackTimer"].update();
    //     if (timers["AttackTimer"].check()) {
    //         attackStep++;
    //     }
        
    //     if (attackStep == actionsLog.size()) {
    //         attackStep = 0;
    //         currentStep = "ChoosingCategory";
    //     } else {
    //         Unit*  executant { heros.getHero(attackStep) };
    //         for (auto& [key, value] : actionsLog[executant]) {
    //             std::cout << executant->getName() << " " << value << " " << key->getName() << std::endl;
    //         }
    //     }
    // }
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
        // writeAction(ctrl, heros.getHero(currentHero), (*category)[cursor]);
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

// void BattleField::writeAction (Controller ctrl, Unit* executant, Unit* target)
// {
//     if (currentCategory == "Attack") {
//         actionsLog[executant][target] = "attack";
//     }
//     // if (currentCategory == "Magic") {
//     //     actionsLog[executant][target] = "magic";
//     // }
//     // if (currentCategory == "Inventory") {
//     //     actionsLog[executant][target] = "use";
//     // }
//     // if (currentCategory == "Run") {
//     //     actionsLog[executant][target] = "run";
//     // }
// }

BattleField::~BattleField ()
{

}