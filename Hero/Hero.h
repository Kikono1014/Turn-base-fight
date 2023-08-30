#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <map>
#include "../Unit/Unit.h"

using std::string;
using std::map;


class Hero : public Unit
{
private:

public:
    Hero ();
    Hero (
        string name, string type,
        int LVL, int XP,
        int HP, int MP,
        int MaxHP, int MaxMP,
        int ATK, int DEF, int INT, int RES, int DEX 
    );
    ~Hero ();

};

#endif