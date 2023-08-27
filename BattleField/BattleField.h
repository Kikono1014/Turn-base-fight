#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>
#include <vector>
#include <map>

#if defined _WIN32
    #include "windows.h"
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    #include <unistd.h>
#endif


#include "../Timer/Timer.h"
#include "../Controller/Controller.h"
#include "../Spell/Spell.h"
#include "../Unit/Unit.h"
#include "../Squad/Squad.h"
#include "../Swarm/Swarm.h"

using std::vector;
using std::map;

class BattleField
{
private:
    map<string, Timer> timers {};
    map<Unit*, map<Unit*, string>> actionsLog {};

    vector<string> categories {}; 
    // vector<string> spells     {}; // in unit
    // vector<string> inventory  {}; // in squad

    Squad heros   {};
    Swarm enemies {};

    string currentStep     { "ChoosingCategory" };
    string currentCategory { "" };
    int    currentHero     { 0 };
    int    attackStep      { 0 };
    int    cursor          { 0 };
    bool   isRun           { false };


    void delay (double time);
    void clear ();

    void moveCursorNext    (int max);
    void moveCursorPrev    (int max);
    void checkCursorMoving (Controller ctrl, int max);

    vector<string> makeNamesList (vector<Hero>  list);
    vector<string> makeNamesList (vector<Enemy> list);
    vector<string> makeNamesList (vector<Spell> list);
    // vector<string> makeNamesList (vector<Item> list); // TODO to items in inventory

    void processAction (Controller ctrl);

    void show            (Controller ctrl);
    void showBattleField ();
    void showMenu        ();
    void showDirectory   (vector<string> directory, string name);
    void showHeros       ();
    void showEnemies     ();
    void showAttack      ();

    void chooseCategory (Controller ctrl);

    void chooseAction   (Controller ctrl, vector<string> category);
    // void writeAction    (Controller ctrl, Unit* executant, Unit* target);

public:
    BattleField (Squad heros, Swarm enemies);

    void runBattle (Controller ctrl);

    ~BattleField ();

};

#endif