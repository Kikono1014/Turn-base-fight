#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    int timer { };
    int limit { };
public:
    Timer (int lim);

    void update ();
    bool check  ();
    void skip   ();
    void reset  ();

    ~Timer ();

};

#endif