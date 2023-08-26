#ifndef UNIT_H
#define UNIT_H

#include <iostream>

using std::string;

class Unit
{
private:
    string name {};
    string type {};

    int LVL { 0 };

    int XP { 0 };
    int HP { 0 };
    int MP { 0 };

    int MaxHP { 0 };
    int MaxMP { 0 };

    int ATK { 0 }; // attack
    int DEF { 0 }; // defense
    int INT { 0 }; // intelligence
    int RES { 0 }; // resistance
    int DEX { 0 }; // dexterity

public:
    Unit (
        string name, string type,
        int LVL, int XP,
        int HP, int MP,
        int MaxHP, int MaxMP,
        int ATK, int DEF, int INT, int RES, int DEX 
    );

    int getLVL   ();
    int getXP    ();
    int getHP    ();
    int getMP    ();
    int getMaxHP ();
    int getMaxMP ();
    int getATK   ();
    int getDEF   ();
    int getINT   ();
    int getRES   ();
    int getDEX   ();

    void setLVL   (int LVL  );
    void setXP    (int XP   );
    void setHP    (int HP   );
    void setMP    (int MP   );
    void setMaxHP (int MaxHP);
    void setMaxMP (int MaxMP);
    void setATK   (int ATK  );
    void setDEF   (int DEF  );
    void setINT   (int INT  );
    void setRES   (int RES  );
    void setDEX   (int DEX  );

    void die ();

    ~Unit ();

};

#endif