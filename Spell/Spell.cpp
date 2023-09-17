#include "Spell.h"

Spell::Spell ()
{

}

Spell::Spell (string name)
{
    this->name = name;
}

string Spell::getName  () { return name;  }
string Spell::getType  () { return type;  }
int    Spell::getValue () { return value; }


void Spell::TryParseJson ()
{
    try
    {
        std::ifstream f("../spellList.json");
        json spellList { json::parse(f) };
    }
    catch (json::parse_error& ex)
    {
        if (ex.byte == 1) {
            std::cout << "Missed spell List file" << std::endl;
            exit(1);
        }
    }
}

json Spell::readFromJson ()
{
    std::ifstream f("../spellList.json");
    return json::parse(f);
}

Spell::~Spell ()
{

}