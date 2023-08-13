#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <map>
#include "../lib/Key/Key.h"
#include "../lib/Key/KeyPlus.h"

using std::string;
using std::map;

class Controller
{
private:
    map<string, int> controls {};
public:
    Controller ();
    int getKey ();
    int getActionKey (string actionName);
    ~Controller ();

};

#endif