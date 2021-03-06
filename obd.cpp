#include <OBD2UART.h>

#include "obd.h"

static COBD obd;

bool OBD::init() {
    if (!obd.begin()) {
        return false;
    }

    obd.setBaudRate(115200UL);

    if (!obd.init()) {
        return false;
    }

    return true;
}

bool OBD::getData(OBD::VehicleData& data_out) {
    static int manifold, barom;
    static int speed;

    if (!obd.readPID(PID_INTAKE_MAP, manifold)) {
        return false;
    }

    if (!obd.readPID(PID_BAROMETRIC, barom)) {
        return false;
    }

    data_out.boost = (float)(manifold - barom) * 0.14503774f;

    if (!obd.readPID(PID_COOLANT_TEMP, data_out.temp)) {
        return false;
    }

    if (!obd.readPID(PID_SPEED, speed)) {
        return false;
    }

    if (speed > data_out.maxspeedkmh) {
        data_out.maxspeedkmh = speed;
        data_out.maxspeedmph = (int)((float)speed * 0.6213711922f);
    }

    return true;
}
