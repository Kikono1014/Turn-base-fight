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


int BattleField::random (int min, int max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int random = mersenne() % ((max + 1) + abs(min)) + min;
    return random;
}


/// @brief check if it's within the percentage range
/// @param chance - in %
/// @return 1 - luck, 0 - not
bool BattleField::tryYourLuck (int chance)
{
    return (random(0, 100) <= chance);
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

vector<string> BattleField::compareNamesLists (
        vector<string> list1, vector<string> list2
    )
{
    vector<string> namesList {};
    for (string i : list1) {
        namesList.push_back(i);
    }
    for (string i : list2) {
        namesList.push_back(i);
    }
    return namesList;
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
        else if (currentStep == "ChoosingTarget") {
            vector<string> herosNames   { 
                    makeNamesList(heros.getHeros())
                };
            
            vector<string> enemiesNames { 
                    makeNamesList(enemies.getEnemies())
                };
            chooseTarget(ctrl, compareNamesLists(herosNames, enemiesNames));
        }

        if (currentHero == heros.getHeros().size()) {
            createEnemiesAttack();
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
    std::cout << cursor                                    << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    
    std::cout << std::endl;
    showBattleField();
    std::cout << std::endl;
    showMenu();
    std::cout << std::endl;
    showAttack();
    std::cout << std::endl;
    showHeros();
    std::cout << std::endl;
    showEnemies();
    std::cout << std::endl;
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
    if (currentStep == "ChoosingTarget") {
        if (currentCategory == "Magic") {
            vector<string> herosNames   { 
                    makeNamesList(heros.getHeros())
                };
            
            vector<string> enemiesNames { 
                    makeNamesList(enemies.getEnemies())
                };
            showDirectory(compareNamesLists(herosNames, enemiesNames), "Choose target");
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

void BattleField::showHeros ()
{
    for (Hero hero : heros.getHeros()) {
        std::cout << hero.getName() << ":" << std::endl;
        std::cout << "\tHP - "  << hero.getHP()  << std::endl;
        std::cout << "\tMP - "  << hero.getMP()  << std::endl;
        std::cout << "\tATK - " << hero.getATK() << std::endl;
    }
}

void BattleField::showEnemies ()
{
    for (Enemy enemy : enemies.getEnemies()) {
        std::cout << enemy.getName() << ":" << std::endl;
        std::cout << "\tHP - "  << enemy.getHP()  << std::endl;
        std::cout << "\tMP - "  << enemy.getMP()  << std::endl;
        std::cout << "\tATK - " << enemy.getATK() << std::endl;
    }
}

void BattleField::showAttack ()
{
    if (currentStep == "Attacking") {
        timers["AttackTimer"].update();
        if (timers["AttackTimer"].check()) {
            makeAttack();
            attackStep++;
        }
        if (attackStep == actionsLog.size()) {
            attackStep = 0;
            actionsLog.clear();
            currentStep = "ChoosingCategory";
        }
        else {
            printAttack();
        }
    }
}

void BattleField::makeAttack ()
{
    Action currentAction { actionsLog[attackStep] };
    if (currentAction.getType() == "Attack") {
        int damage {
            currentAction.getExecutant()->getATK()
        };
        currentAction.getTarget()->setHP(
                currentAction.getTarget()->getHP() -
                damage
            );
    }
    if (currentAction.getType() == "Magic") {
        currentAction.getUsedSpell()->use(
                currentAction.getExecutant(),
                currentAction.getTarget()
            );
    }
    if (currentAction.getType() == "Run") {
        int runChance { 
                20 + 
                (int)(currentAction.getExecutant()->getDEX() *
                0.2)
            }; // 20%(minimal) + 20% of heros dexterity 
        if (tryYourLuck(30)) {
            isRun = 0;
        }
    }
}

void BattleField::printAttack ()
{
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
    }
    if (actionsLog[attackStep].getType() == "Run") {
        std::cout << 
            actionsLog[attackStep].getType()                 << " " << 
            actionsLog[attackStep].getExecutant()->getName()
        << std::endl;
    }
}


void BattleField::createEnemiesAttack ()
{
    for (
            int enemyId = 0; 
            enemyId < enemies.getEnemies().size(); 
            ++enemyId
        ) {
        actionsLog.push_back(Action("Attack",
                enemies.getEnemy(enemyId),
                heros.getHero(random(0, heros.getHeros().size() - 1))
            ));
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
            pickedInPrevious = cursor;
            currentStep     = "ChoosingTarget";
        }
        if (currentCategory == "Run") {
            writeAction(currentCategory, heros.getHero(currentHero));
        }

        if (currentStep != "ChoosingTarget") {
            currentCategory = "";
            currentStep     = "ChoosingCategory";
            currentHero++;
        }
        cursor          = 0;

    }
    if (ctrl.currentActionIs("Cancel")) {
        currentCategory = "";
        currentStep     = "ChoosingCategory";
        cursor          = 0;
    }
}

void BattleField::chooseTarget (Controller ctrl, vector<string> category)
{
    checkCursorMoving(ctrl, category.size() - 1);

    if (ctrl.currentActionIs("Confirm")) {
        if (currentCategory == "Magic") {

            if (cursor < heros.getHeros().size()) {
                writeAction(currentCategory, heros.getHero(currentHero),
                            heros.getHero(cursor),
                            heros.getHero(currentHero)->getSpell(pickedInPrevious)
                );
            }
            if (cursor >= heros.getHeros().size()) {
                writeAction(currentCategory, heros.getHero(currentHero),
                            enemies.getEnemy(cursor - heros.getHeros().size()),
                            heros.getHero(currentHero)->getSpell(pickedInPrevious)
                );
            }
        }

        currentCategory  = "";
        currentStep      = "ChoosingCategory";
        pickedInPrevious = 0;
        cursor           = 0;

        currentHero++;
    }
    if (ctrl.currentActionIs("Cancel")) {
        currentCategory  = "Magic";
        currentStep      = "ChoosingAction";
        pickedInPrevious = 0;
        cursor           = 0;
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