#include "Enemy.h"

Enemy::Enemy () {

}

Enemy::Enemy (
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

Enemy::~Enemy ()
{

}