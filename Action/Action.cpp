#include "Action.h"

Action::Action (string type, Unit* executant, Unit* target)
{
    this->type      = type;
    this->executant = executant;
    this->target    = target;
}

Action::~Action ()
{
    delete executant;
    delete target;
}