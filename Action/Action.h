#ifndef ACTION_H
#define ACTION_H

#include <iostream>
#include "../Unit/Unit.h"

using std::string;

class Action
{
private:
    string type      {};
    Unit*  executant {};
    Unit*  target    {};
    // Item*  usedItem  {};
    // Spell*  usedSpell  {};

public:
    Action (string type, Unit* executant = {}, Unit* target = {});

    string getType      ();
    Unit*  getExecutant ();
    Unit*  getTarget    ();

    void setType      (string type     );
    void setExecutant (Unit*  executant);
    void setTarget    (Unit*  target   );

    ~Action ();

};

#endif