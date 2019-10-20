#include<PWMValveDriverDecorator.hpp>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void PWMValveDriverDecorator::handle() {
    vd.handle();
    
    uint32_t calc_peri = pwm_period;
    uint32_t now = millis();
    if(vd.getState() && now-last_on > calc_peri*pwm_level/MAX_PWM_LEVEL) {
        debugD("Ending PWM on phase");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tPWM on peri: %d",calc_peri*pwm_level/MAX_PWM_LEVEL);
        debugD("\tState: %d",vd.getState());
        vd.setState(0);
    } else if(!vd.getState() && pwm_level>0 && millis()-last_on > pwm_period) {
        debugD("Starting PWM period");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tPWM peri: %d",pwm_period);
        debugD("\tState: %d",vd.getState());
        vd.setState(1);
        last_on = millis();
    } else if(!vd.getState() && now-last_on <= calc_peri*pwm_level/MAX_PWM_LEVEL) { 
        debugD("Enabling within PWM on phase"); // this should not happen on a regular basis
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tPWM peri: %d",pwm_period);
        debugD("\tState: %d",vd.getState());
        vd.setState(1);
    } else { 
        debugV("Doing nothing");
        debugV("\tMillis: %d",now);
        debugV("\tlast_on: %d",last_on);
        debugV("\tPWM peri: %d",pwm_period);
        debugV("\tState: %d",vd.getState());
        debugV("\tnow-last_on: %d",now-last_on);
        debugV("\tpwm_level: %d",pwm_level);
        debugV("\tOn period: %d",calc_peri*pwm_level/MAX_PWM_LEVEL);
    }
}