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
    Squad (Hero hero1 = Hero(), 
           Hero hero2 = Hero(),
           Hero hero3 = Hero(), 
           Hero hero4 = Hero());
    
    Hero* getHero (int id);

    vector<Hero> getHeros ();

    ~Squad ();

};

#endif