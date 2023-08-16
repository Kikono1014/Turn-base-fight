#include "Controller.h"

Controller::Controller ()
{
    controls["ConfirmAction"] = Enter;
    controls["CancelAction"]  = Backspace;
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

bool Controller::isCurrentAction (string actionName)
{
    return key == controls[actionName];
}

Controller::~Controller ()
{

}