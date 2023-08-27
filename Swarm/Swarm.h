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
    Swarm (vector<Enemy> enemies = {});
    
    Enemy* getEnemy (int id);

    vector<Enemy> getEnemies ();

    ~Swarm ();

};

#endif