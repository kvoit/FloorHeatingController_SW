#include <BangBangController.h>

void BangBangController::handle() {
    if(vd.getState() && t.getTemp()>switch_temp) {
        vd.setState(0);
    } else if(!vd.getState() && t.getTemp()<switch_temp-hysteresis) {
        vd.setState(1);
    }
}