#include "Timer.h"

Timer::Timer (int lim)
{
    limit = lim;
}

void Timer::update ()
{
    timer++;
}

bool Timer::check ()
{
    if (timer >= limit) {
        timer = 0;
        return 1;
    }
    return 0;
}


void Timer::skip ()
{
    timer = limit;
}

void Timer::reset ()
{
    timer = 0;
}



Timer::~Timer ()
{

}