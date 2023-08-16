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
    int key {};
    map<string, int> controls {};
public:
    Controller ();
    void updateKey          ();
    int  getKey             ();
    int  getActionKey       (string actionName);
    bool isCurrentAction (string actionName);
    ~Controller ();

};

#endif