#include "Squad.h"

Squad::Squad (Hero h1, Hero h2, Hero h3, Hero h4)
{
    heros.push_back(h1);
    heros.push_back(h2);
    heros.push_back(h3);
    heros.push_back(h4);
}

Hero*        Squad::getHero  (int id) { return &heros[id]; }
vector<Hero> Squad::getHeros ()       { return heros;      }

Squad::~Squad ()
{

}