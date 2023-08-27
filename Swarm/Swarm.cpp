#include "Swarm.h"

Swarm::Swarm (vector<Enemy> enemies)
{
    this->enemies = enemies;
}

Enemy*        Swarm::getEnemy   (int id) { return &enemies[id]; }
vector<Enemy> Swarm::getEnemies ()       { return enemies;      }

Swarm::~Swarm ()
{

}