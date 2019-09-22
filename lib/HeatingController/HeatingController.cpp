#include <HeatingController.h>

void HeatingController::handle() { 
    if(enabled) {
        t->handle(); 
        vd->handle();
    } 
}

void HeatingController::setEnabled(boolean enabled) { 
    vd->setState(0);
    this->enabled = enabled; 
}