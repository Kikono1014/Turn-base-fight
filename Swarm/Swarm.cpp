#include "Swarm.h"

Swarm::Swarm (Enemy enemy1, Enemy enemy2, Enemy enemy3,
              Enemy enemy4, Enemy enemy5, Enemy enemy6,
              Enemy enemy7, Enemy enemy8, Enemy enemy9)
{
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);
    enemies.push_back(enemy5);
    enemies.push_back(enemy6);
    enemies.push_back(enemy7);
    enemies.push_back(enemy8);
    enemies.push_back(enemy9);
}

Enemy*        Swarm::getEnemy   (int id) { return &enemies[id]; }
vector<Enemy> Swarm::getEnemies ()       { return enemies;      }

Swarm::~Swarm ()
{

}