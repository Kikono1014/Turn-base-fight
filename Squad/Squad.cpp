#include "Squad.h"

Squad::Squad (Hero hero1, Hero hero2, Hero hero3, Hero hero4)
{
    heros.push_back(hero1);
    heros.push_back(hero2);
    heros.push_back(hero3);
    heros.push_back(hero4);
}

Hero* Squad::getHero (int id) { return &heros[id]; }

vector<Hero>   Squad::getHeros     () { return heros;     }
vector<string> Squad::getInventory () { return inventory; }

void Squad::setInventory (vector<string> inventory) { this->inventory = inventory; }

Squad::~Squad ()
{

}