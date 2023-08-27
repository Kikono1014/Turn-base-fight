#ifndef SWARM_H
#define SWARM_H

#include <iostream>
#include <vector>
#include "../Enemy/Enemy.h"

using std::vector;

class Swarm
{
private:
    vector<Enemy> enemies {};
public:
    Swarm (Enemy enemy1 = Enemy(), 
           Enemy enemy2 = Enemy(),
           Enemy enemy3 = Enemy(), 
           Enemy enemy4 = Enemy(),
           Enemy enemy5 = Enemy(), 
           Enemy enemy6 = Enemy(),
           Enemy enemy7 = Enemy(), 
           Enemy enemy8 = Enemy(),
           Enemy enemy9 = Enemy());
    
    Enemy* getEnemy (int id);

    vector<Enemy> getEnemies ();

    ~Swarm ();

};

#endif