#include <BangBangController.h>

#include <RemoteDebug.h>
extern RemoteDebug Debug;

void BangBangController::handle() {
    HeatingController::handle();

    if(!enabled)
        return;

    float th_temp = t.getTemp();
    if(vd.getState() && th_temp>temp+hysteresis) {
        debugD("[BangBangController] Set valve change to 0 from %d because temp changed to %.1f",vd.getState(),th_temp);
        vd.setState(0);

        if(listener!=0)
            listener->setValveState(true);
            listener->setValveState(false);
    } else if(!vd.getState() && th_temp<temp) {
        debugD("[BangBangController] Set valve change to 1 from %d because temp changed to %.1f",vd.getState(),th_temp);
        vd.setState(1);
        if(listener!=0)
            listener->setValveState(false);
            listener->setValveState(true);
    } else {
        // debugV("No valve change, temp at %.1f",temp);
    }
}