#include "Action.h"

Action::Action (string type, Unit* executant, Unit* target)
{
    this->type      = type;
    this->executant = executant;
    this->target    = target;
}


string Action::getType      () { return type     ; }
Unit*  Action::getExecutant () { return executant; }
Unit*  Action::getTarget    () { return target   ; }

void Action::setType      (string type     ) { this->type      = type     ; }
void Action::setExecutant (Unit*  executant) { this->executant = executant; }
void Action::setTarget    (Unit*  target   ) { this->target    = target   ; }

Action::~Action ()
{
}