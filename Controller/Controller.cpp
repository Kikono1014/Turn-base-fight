#include "Controller.h"

Controller::Controller ()
{
    controls["Confirm"]    = Enter;
    controls["Cancel"]     = Backspace;
    controls["Exit"]       = Escape;
    controls["CursorNext"] = ArrowDown;
    controls["CursorPrev"] = ArrowUp;
}


void Controller::updateKey ()
{
    key = Key::GetAsyncKey();
}

int Controller::getKey ()
{
    return key;
}


int Controller::getActionKey (string actionName)
{
    return controls[actionName];
}

bool Controller::currentActionIs (string actionName)
{
    bool res { key == controls[actionName] };
    if (res) {
        key = -1;
    }
    return res;
}

Controller::~Controller ()
{

}