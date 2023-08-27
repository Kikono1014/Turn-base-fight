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
    map<string, string> spells {
        { "AttackType", "Spell1" },
        { "AttackType", "Spell2" },
        { "AttackType", "Spell3" },
        { "AttackType", "Spell4" }
    }; // second type must be Spell
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