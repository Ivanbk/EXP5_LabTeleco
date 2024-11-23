#include "timer.hpp"

hw_timer_t* my_timer = nullptr;
bool timer_fired = false;

void IRAM_ATTR onTimer(){
    timer_fired = true;
}

void setupTimer(){
    my_timer = timerBegin(1, 800, true);
    timerAttachInterrupt(my_timer, &onTimer, true);
    timerAlarmWrite(my_timer, 1000000, true);
    timerAlarmEnable(my_timer);
}