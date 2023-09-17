#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "../Spell/Spell.h"
#include "../Unit/Unit.h"

using std::string;

class Action
{
private:
    string type      {};
    Unit*  executant {};
    Unit*  target    {};
    // Item*  usedItem  {};
    Spell*  usedSpell  {};

public:
    Action (string type, Unit* executant);
    Action (string type, Unit* executant, Unit* target);
    // Action (string type, Unit* executant, Unit* target, Item*  usedItem);
    Action (string type, Unit* executant, Unit* target, Spell* usedSpell);

    string getType      ();
    Unit*  getExecutant ();
    Unit*  getTarget    ();
    Spell* getUsedSpell ();

    void setType      (string type     );
    void setExecutant (Unit*  executant);
    void setTarget    (Unit*  target   );

    ~Action ();

};

#endif