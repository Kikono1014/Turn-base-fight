#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <iostream>
#include <vector>

#if defined _WIN32
    #include "windows.h"
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
    #include <unistd.h>
#endif

#include "../Controller/Controller.h"
#include "../Spell/Spell.h"
#include "../Unit/Unit.h"
#include "../Squad/Squad.h"

using std::vector;

class BattleField
{
private:
    vector<string> log {};

    vector<string> categories {};
    vector<string> spells     {};
    vector<string> inventory  {};

    vector<string> heros   {};
    vector<string> enemies {};

    string currentStep     { "ChoosingCategory" };
    string currentCategory { "" };
    int    currentHero     { 0 };
    int    cursor          { 0 };
    bool   isRun           { false };


    void delay (double time);
    void clear ();

    void moveCursorNext    (int max);
    void moveCursorPrev    (int max);
    void checkCursorMoving (Controller ctrl, int max);

    void processAction (Controller ctrl);

    void show            ();
    void showBattleField ();
    void showMenu        ();
    void showDirectory   (vector<string> *directory, string name);
    void showHeros       ();
    void showEnemies     ();

    void chooseCategory (Controller ctrl);

    void chooseAction   (Controller ctrl, vector<string> *category);

    void makeAttack     (Controller ctrl, string executant, string target);

public:
    BattleField ();

    void runBattle (Controller ctrl);

    ~BattleField ();

};

#endif