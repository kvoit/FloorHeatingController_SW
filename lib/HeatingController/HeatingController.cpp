#include <HeatingController.h>

#include<RemoteDebug.h>
extern RemoteDebug Debug;

void HeatingController::handle() { 
    if(enabled) {
        t.handle(); 
        // debugV("[Heating controller] Handle valve controller");
        vd.handle();    
    } 
    for (HeatingControllerListener* hcl : listener)
    {
        hcl->handle();
    }
}

void HeatingController::setEnabled(boolean enabled) { 
    if (this->enabled != enabled) {
        debugD("Setting heating controller status to %d",enabled);
        vd.setState(0);

        this->enabled = enabled; 

        for (HeatingControllerListener* hcl : listener)
        {
            hcl->setEnabled(enabled);
        }
    }
}

void HeatingController::setTemp(float temp, boolean silent) {
    if (this->temp != temp) {
        this->temp = temp; 

        if(!silent) {
            debugD("Notifying listeners of temperature change");
            for (HeatingControllerListener* hcl : listener)
            {
                debugD("Notifying listener");
                hcl->setTemp(temp);
            }
        }
    }
}

void HeatingController::setValveLevel(uint8_t valve_level) {
    if (this->getValveDriver().getLevel() != valve_level) {
        this->getValveDriver().setLevel(valve_level);
        debugD("Notifying listeners of level change from %d to %d",this->getValveDriver().getLevel(),valve_level);
        for (HeatingControllerListener* hcl : listener)
        {
            debugD("Notifying listener");
            hcl->setValveLevel(valve_level);
        }
    } else {
        debugD("Ignoring change of level since %d is already %d",this->getValveDriver().getLevel(),valve_level);
    }
}

void HeatingController::addListener(HeatingControllerListener *l) {
    listener.push_back(l); 

    l->setEnabled(this->isEnabled(),false);
    l->setValveLevel(vd.getLevel(),false);
    l->setValveState(vd.getState(),false);
};