#include <BangBangController.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void BangBangController::handle() {
    HeatingController::handle();

    if(!enabled)
        return;

    float th_temp = t->getTemp();
    if(vd->getState() && th_temp>temp) {
        vd->setState(0);
        debugD("Set valve change to 0 because temp changed to %.1f",th_temp);
    } else if(!vd->getState() && th_temp<temp-hysteresis) {
        vd->setState(1);
        debugD("Set valve change to 1 because temp changed to %.1f",th_temp);
    } else {
        // debugV("No valve change, temp at %.1f",temp);
    }
}