#include "Spell.h"


Spell::Spell ()
{

}

Spell::Spell (string name)
{
    this->name = name;
    createSpellByNameFromList(name);
}

string Spell::getName  () { return name;  }
string Spell::getType  () { return type;  }
int    Spell::getValue () { return value; }


void Spell::tryParseJson ()
{
    try
    {
        json spellList { readFromJson() };
    }
    catch (json::parse_error& ex)
    {
        if (ex.byte == 1) {
            std::cout << "Missed spell list file or fail open" << std::endl;
            exit(1);
        }
    }
}

json Spell::readFromJson ()
{
    std::ifstream f("./spellList.json");
    return json::parse(f);
}

void Spell::createSpellByNameFromList (string name)
{
    tryParseJson();
    json spellList { readFromJson() };
    for (auto spell : spellList[0]) {
        if (spell["name"] == name) {
            type    = spell["type"];
            useType = spell["useType"];
            turns   = spell["turns"];
            value   = spell["value"];
        }
    }
    std::cout << std::endl;
}

void Spell::use (Unit* executant, Unit* target)
{
    if (useType == "changeStatOnce") {
        useChangeStatOnceType(executant, target);
    }
}

Spell::~Spell ()
{

}


void Spell::useChangeStatOnceType (Unit* executant, Unit* target)
{
    if (type == "HP") {
        target->setHP(target->getHP() + value);
    }
    if (type == "MP") {
        target->setMP(target->getMP() + value);
    }
}
