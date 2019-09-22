#include <BangBangController.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void BangBangController::handle() {
    HeatingController::handle();

    if(!enabled)
        return;

    float temp = t->getTemp();
    if(vd->getState() && temp>switch_temp) {
        vd->setState(0);
        debugD("Set valve change to 0 because temp changed to %.1f",temp);
    } else if(!vd->getState() && temp<switch_temp-hysteresis) {
        vd->setState(1);
        debugD("Set valve change to 1 because temp changed to %.1f",temp);
    } else {
        // debugV("No valve change, temp at %.1f",temp);
    }
}