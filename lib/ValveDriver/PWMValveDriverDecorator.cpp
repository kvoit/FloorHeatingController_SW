#include<PWMValveDriverDecorator.hpp>

void PWMValveDriverDecorator::handle() {
    vd->handle();
    
    uint32_t calc_peri = pwm_period;
    if(vd->getState() && millis()-last_on > calc_peri*pwm_level/MAX_PWM_LEVEL) {
        vd->setState(0);
    } else if(!vd->getState() && pwm_level>0 && millis()-last_on > pwm_period) {
        vd->setState(1);
        last_on = millis();
    }
}