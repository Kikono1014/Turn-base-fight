#ifndef SPELL_H
#define SPELL_H
#include <iostream>

using std::string;

class Spell
{
private:
    string type {};
public:
    Spell ();

    void use ();

    ~Spell ();

};

#endif