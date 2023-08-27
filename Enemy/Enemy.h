#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <map>
#include "../Unit/Unit.h"

using std::string;
using std::map;


class Enemy : public Unit
{
private:
    map<string, string> spells {}; // second type must be Spell
public:
    Enemy ();
    Enemy (
        string name, string type,
        int LVL, int XP,
        int HP, int MP,
        int MaxHP, int MaxMP,
        int ATK, int DEF, int INT, int RES, int DEX 
    );
    ~Enemy ();

};

#endif