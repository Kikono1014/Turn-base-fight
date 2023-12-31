#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>
#include <vector>
#include <map>
#include <random>

#if defined _WIN32
    #include "windows.h"
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    #include <unistd.h>
#endif


#include "../Timer/Timer.h"
#include "../Action/Action.h"
#include "../Controller/Controller.h"
#include "../Unit/Unit.h"
#include "../Spell/Spell.h"
#include "../Squad/Squad.h"
#include "../Swarm/Swarm.h"

using std::vector;
using std::map;

class BattleField
{
private:
    map<string, Timer> timers {};
    vector<Action>     actionsLog {};

    vector<string> categories {};

    Squad heros   {};
    Swarm enemies {};

    string currentStep      { "ChoosingCategory" };
    string currentCategory  { "" };
    int    currentHero      { 0 };
    int    pickedInPrevious { 0 };
    int    attackStep       { 0 };
    int    cursor           { 0 };
    bool   isRun            { false };


    // Generate a random number in [min, max] diapason 
    int  random      (int min, int max);

    // Check a chance in percents
    bool tryYourLuck (int chance);

    void delay (double time);
    void clear ();

    void moveCursorNext    (int max);
    void moveCursorPrev    (int max);
    void checkCursorMoving (Controller ctrl, int max);

    vector<string> makeNamesList (vector<Hero>  list);
    vector<string> makeNamesList (vector<Enemy> list);
    vector<string> makeNamesList (vector<Spell> list);
    // vector<string> makeNamesList (vector<Item> list); // TODO to items in inventory
    vector<string> compareNamesLists (
        vector<string> list1, vector<string> list2
    );

    void processAction (Controller ctrl);

    void show            (Controller ctrl);
    void showBattleField ();
    void showMenu        ();
    void showDirectory   (vector<string> directory, string name);
    void showHeros       ();
    void showEnemies     ();
    void showAttack      ();

    void makeAttack  ();
    void printAttack ();

    void createEnemiesAttack ();

    void chooseCategory (Controller ctrl);
    void chooseAction   (Controller ctrl, vector<string> category);
    void chooseTarget   (Controller ctrl, vector<string> category);
    
    void writeAction (string type, Unit* executant);
    void writeAction (string type, Unit* executant, Unit* target);
    // void writeAction (string type, Unit* executant, Unit* target, Item*  usedItem);
    void writeAction (string type, Unit* executant, Unit* target, Spell* usedSpell);
    

public:
    BattleField (Squad heros, Swarm enemies);

    void runBattle (Controller ctrl);

    ~BattleField ();

};

#endif