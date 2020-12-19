#include<PWMValveDriverDecorator.hpp>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void PWMValveDriverDecorator::handle() {
    vd.handle();
    
    uint32_t calc_peri = pwm_period;
    uint32_t now = millis();
    // If valve is on and has been on for longer than PWM duty cycle
    if(vd.getState() && now-last_on > calc_peri*pwm_level/MAX_PWM_LEVEL) {
        debugV("Ending PWM on phase");
        debugV("\tMillis: %d",now);
        debugV("\tlast_on: %d",last_on);
        debugV("\tpwm_level: %d",pwm_level);
        debugV("\toff_level: %d",off_level);
        debugV("\tvd_state: %d",vd.getState());
        debugV("\tPWM on peri: %d",calc_peri*pwm_level/MAX_PWM_LEVEL);
        debugV("\tState: %d",vd.getState());
        vd.setState(0);
    // If valve is off and has been off for longer than PWM period
    } else if(!vd.getState() && now-last_on > pwm_period && pwm_level>0) {
        debugV("Starting PWM period");
        debugV("\tMillis: %d",now);
        debugV("\tlast_on: %d",last_on);
        debugV("\tpwm_level: %d",pwm_level);
        debugV("\toff_level: %d",off_level);
        debugV("\tvd_state: %d",vd.getState());
        debugV("\tPWM peri: %d",pwm_period);
        debugV("\tState: %d",vd.getState());
        vd.setState(1);
        last_on = now;
    // If valve is off but should be on according to duty cycle (not sure when that can happen)
    } else if(!vd.getState() && now-last_on <= calc_peri*pwm_level/MAX_PWM_LEVEL) { 
        debugD("Enabling within PWM on phase");
        debugD("\tMillis: %d",now);
        debugD("\tlast_on: %d",last_on);
        debugD("\tPWM peri: %d",pwm_period);
        debugD("\tpwm_level: %d",pwm_level);
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

void PWMValveDriverDecorator::setLevel(uint8_t pwm_level)
{
    debugD("Setting valve level from %d to %d",this->pwm_level, pwm_level);
    this->pwm_level = pwm_level; 
};