#ifndef SQUAD_H
#define SQUAD_H

#include <iostream>
#include <vector>
#include "../Hero/Hero.h"

using std::vector;

class Squad
{
private:
    vector<Hero> heros {};
public:
    Squad (Hero h1, Hero h2, Hero h3, Hero h4);
    
    Hero* getHero (int id);

    vector<Hero> getHeros ();

    ~Squad ();

};

#endif