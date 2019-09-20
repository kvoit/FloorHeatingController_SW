#include <OnOffTheromostat.h>

float OnOffTheromostat::getTemp() {
    if(ifd.digitalRead())
        return this->on_temp;
    else
        return this->off_temp;
};

void OnOffTheromostat::handle(void) {
    ifd.handle();
};