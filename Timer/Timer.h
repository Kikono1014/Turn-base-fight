#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    int timer { 0 };
    int limit { 0 };
public:
    Timer ();
    Timer (int lim);

    void update ();
    bool check  ();

    ~Timer ();

};

#endif