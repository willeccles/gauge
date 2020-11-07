#ifndef GAUGE_OLED_H_
#define GAUGE_OLED_H_

#include "obd.h"

namespace OLED {
    void init();

    void dim(bool dim);

    void displayLogo();
    void displayLogo(const char* status);

    void update(OBD::VehicleData& data);
};

#endif /* GAUGE_OLED_H_ */
