#ifndef SPELL_H
#define SPELL_H

#include <iostream>
#include <fstream>
#include "../lib/nlohmann_json/single_include/nlohmann/json.hpp"
#include "../Unit/Unit.h"

using json = nlohmann::json;
using std::string;

class Spell
{
private:
    string name    {};
    string type    {};
    string useType {};
    int    turns   {};
    int    value   {};
    void (*useSpell) (Unit* executant, Unit* target) {};

    
    json readFromJson ();
    void tryParseJson ();
    void createSpellByNameFromList (string name);
public:
    Spell ();
    Spell (string name);

    void use ();

    string getName  ();
    string getType  ();
    int    getValue ();

    ~Spell ();

};

#endif