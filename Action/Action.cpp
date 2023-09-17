#include "Action.h"


Action::Action::Action (string type, Unit* executant)
{
    this->type      = type;
    this->executant = executant;
}

Action::Action (string type, Unit* executant, Unit* target)
{
    this->type      = type;
    this->executant = executant;
    this->target    = target;
}

// Action::Action (string type, Unit* executant, Unit* target, Item* usedItem)
// {
//     this->type      = type;
//     this->executant = executant;
//     this->target    = target;
//     this->usedItem = usedItem;
// }

Action::Action (string type, Unit* executant, Unit* target, Spell* usedSpell)
{
    this->type      = type;
    this->executant = executant;
    this->target    = target;
    this->usedSpell = usedSpell;
}


string Action::getType      () { return type     ; }
Unit*  Action::getExecutant () { return executant; }
Unit*  Action::getTarget    () { return target   ; }
Spell* Action::getUsedSpell () { return usedSpell; }

void Action::setType      (string type     ) { this->type      = type     ; }
void Action::setExecutant (Unit*  executant) { this->executant = executant; }
void Action::setTarget    (Unit*  target   ) { this->target    = target   ; }

Action::~Action ()
{
}