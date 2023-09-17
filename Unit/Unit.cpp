#include "Unit.h"

Unit::Unit ()
{
    
}

Unit::Unit (
        string name, string type,
        int LVL, int XP,
        int HP, int MP,
        int MaxHP, int MaxMP,
        int ATK, int DEF, int INT, int RES, int DEX 
    )
{
    this->name  = name ;
    this->type  = type ;
    this->LVL   = LVL  ;
    this->XP    = XP   ;
    this->HP    = HP   ;
    this->MP    = MP   ;
    this->MaxHP = MaxHP;
    this->MaxMP = MaxMP;
    this->ATK   = ATK  ;
    this->DEF   = DEF  ;
    this->INT   = INT  ;
    this->RES   = RES  ;
    this->DEX   = DEX  ;
}


string Unit::getName () { return name; }
string Unit::getType () { return type; }

int Unit::getLVL   () { return LVL   ; }
int Unit::getXP    () { return XP    ; }
int Unit::getHP    () { return HP    ; }
int Unit::getMP    () { return MP    ; }
int Unit::getMaxHP () { return MaxHP ; }
int Unit::getMaxMP () { return MaxMP ; }
int Unit::getATK   () { return ATK   ; }
int Unit::getDEF   () { return DEF   ; }
int Unit::getINT   () { return INT   ; }
int Unit::getRES   () { return RES   ; }
int Unit::getDEX   () { return DEX   ; }


void Unit::setName  (string name) { this->name = name; }
void Unit::setType  (string type) { this->type = type; }

void Unit::setLVL   (int LVL  ) { this->LVL   = LVL  ; }
void Unit::setXP    (int XP   ) { this->XP    = XP   ; }
void Unit::setHP    (int HP   ) { this->HP    = HP   ; }
void Unit::setMP    (int MP   ) { this->MP    = MP   ; }
void Unit::setMaxHP (int MaxHP) { this->MaxHP = MaxHP; }
void Unit::setMaxMP (int MaxMP) { this->MaxMP = MaxMP; }
void Unit::setATK   (int ATK  ) { this->ATK   = ATK  ; }
void Unit::setDEF   (int DEF  ) { this->DEF   = DEF  ; }
void Unit::setINT   (int INT  ) { this->INT   = INT  ; }
void Unit::setRES   (int RES  ) { this->RES   = RES  ; }
void Unit::setDEX   (int DEX  ) { this->DEX   = DEX  ; }

void die ()
{
    
}

Unit::~Unit ()
{

}