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

public:
    Action (string type, Unit* executant = {}, Unit* target = {});

    ~Action ();

};

#endif