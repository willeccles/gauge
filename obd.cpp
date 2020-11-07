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

    if (!obd.readPID(PID_INTAKE_MAP, manifold)) {
        return false;
    }

    if (!obd.readPID(PID_BAROMETRIC, barom)) {
        return false;
    }

    data_out.boost = ((float)manifold - (float)barom) * 0.14503774f;

    if (!obd.readPID(PID_COOLANT_TEMP, data_out.temp)) {
        return false;
    }

    return true;
}
