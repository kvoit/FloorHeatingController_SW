#pragma once

#include<Arduino.h>
#include<HeatingController.h>
#include<HeatingControllerListener.hpp>
#include<globalTimeinfo.h>
#include<INTERVAL.h>

using namespace std;

struct TimeControllerCommand {
    int8_t dow;
    uint8_t hour;
    uint8_t minute;

    bool run = false;

    bool do_enable = false;
    bool enable = true;

    bool do_temp = false;
    float temp = 18.0;

    bool do_valve_level = false;
    uint8_t valve_level = 128;

    friend bool operator==(TimeControllerCommand& com1, TimeControllerCommand&& com2);
    friend TimeControllerCommand& operator+(TimeControllerCommand& com1, TimeControllerCommand&& com2);
};

bool operator==(TimeControllerCommand& com1, TimeControllerCommand&& com2);
TimeControllerCommand& operator+(TimeControllerCommand& com1, TimeControllerCommand&& com2);

class TimerControllerInterface : public HeatingControllerListener {
    public:
    TimerControllerInterface(HeatingController& hc)
    : hc(hc) {
        hc.addListener(this);
    };

    virtual void handle(void);
    virtual void add(TimeControllerCommand*);

    protected:
    HeatingController& hc;
    std::vector<TimeControllerCommand*> commands;
};

