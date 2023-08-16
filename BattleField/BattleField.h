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
    vector<string> categories {};

    string currentStep     { "ChoosingCategory" };
    string currentCategory { "" };
    int    cursor { 0 };


    void delay (double time);
    void clear ();

    void show            ();
    void showBattleField ();
    void showMenu        ();
    void showHeros       ();
    void showEnemies     ();


    void chooseCategory (Controller ctrl);

    void chooseAction   (Controller ctrl);

    void makeAttack     (Controller ctrl);

public:
    BattleField ();

    void runBattle (Controller ctrl);

    ~BattleField ();

};

#endif