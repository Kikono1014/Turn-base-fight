#include "Hero.h"

Hero::Hero () {

}

Hero::Hero (
        string name, string type,
        int LVL, int XP,
        int HP, int MP,
        int MaxHP, int MaxMP,
        int ATK, int DEF, int INT, int RES, int DEX 
    ) : Unit ( 
        name, type, LVL, XP,
        HP, MP, MaxHP, MaxMP,
        ATK, DEF, INT, RES, DEX
    )
{

}



Spell* Hero::getSpell (int id) { return &spells[id]; }

vector<Spell> Hero::getSpells () { return spells; }

void Hero::setSpells (vector<Spell> spells) { this->spells = spells; }

Hero::~Hero ()
{

}