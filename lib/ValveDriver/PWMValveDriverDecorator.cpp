#include<PWMValveDriverDecorator.hpp>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void PWMValveDriverDecorator::handle() {
    vd.handle();
    
    uint32_t calc_peri = pwm_period;
    uint32_t now = millis();
    // If valve is on and has been on for longer than PWM duty cycle
    if(vd.getState() && now-last_on > calc_peri*pwm_level/MAX_PWM_LEVEL) {
        debugD("Ending PWM on phase");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tpwm_level: %d",pwm_level);
        debugD("\toff_level: %d",off_level);
        debugD("\tvd_state: %d",vd.getState());
        debugD("\tPWM on peri: %d",calc_peri*pwm_level/MAX_PWM_LEVEL);
        debugD("\tState: %d",vd.getState());
        vd.setState(0);
    // If valve is off and has been on for longer than PWM period
    } else if(!vd.getState() && now-last_on > pwm_period) {
        debugD("Starting PWM period");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tpwm_level: %d",pwm_level);
        debugD("\toff_level: %d",off_level);
        debugD("\tvd_state: %d",vd.getState());
        debugD("\tPWM peri: %d",pwm_period);
        debugD("\tState: %d",vd.getState());
        vd.setState(1);
        last_on = now;
    // If valve is off but should be on according to duty cycle (not sure when that can happen)
    } else if(!vd.getState() && now-last_on <= calc_peri*pwm_level/MAX_PWM_LEVEL) { 
        debugD("Enabling within PWM on phase");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tPWM peri: %d",pwm_period);
        debugD("\tState: %d",vd.getState());
        vd.setState(1);
    } else { 
        // debugV("Doing nothing");
        // debugV("\tMillis: %d",now);
        // debugV("\tlast_on: %d",last_on);
        // debugV("\tPWM peri: %d",pwm_period);
        // debugV("\tState: %d",vd.getState());
        // debugV("\tnow-last_on: %d",now-last_on);
        // debugV("\tpwm_level: %d",pwm_level);
        // debugV("\tOn period: %d",calc_peri*pwm_level/MAX_PWM_LEVEL);
    }
}