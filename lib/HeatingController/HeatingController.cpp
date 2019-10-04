#include <HeatingController.h>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void HeatingController::handle() { 
    if(enabled) {
        t->handle(); 
        debugV("[Heating controller] Handle valve controller");
        vd->handle();
    } 
}

void HeatingController::setEnabled(boolean enabled) { 
    debugD("Setting heating controller status to %d",enabled);
    vd->setState(0);
    this->enabled = enabled; 
}