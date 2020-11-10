#ifndef OBD_H_
#define OBD_H_

namespace OBD {
    struct VehicleData {
        float boost;            // boost pressure in PSI
        int16_t temp;           // coolant temp in C
        int maxspeedmph;    // max speed in mph
        int maxspeedkmh;    // max speed in kmh
    };

    bool init();

    bool getData(VehicleData& data_out);
};

#endif /* OBD_H_ */
