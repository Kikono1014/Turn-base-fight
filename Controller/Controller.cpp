#include "Controller.h"

Controller::Controller ()
{
    controls["ConfirmAction"] = Enter;
    controls["CancelAction"]  = Backspace;
}


int Controller::getKey ()
{
    return Key::GetAsyncKey();
}


int Controller::getActionKey (string actionName)
{
    return controls[actionName];
}

Controller::~Controller ()
{

}