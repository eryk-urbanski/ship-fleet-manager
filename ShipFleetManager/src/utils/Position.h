// Position.h

#ifndef POSITION_H
#define POSITION_H

#include <ctime>

struct Position {
    // Latitude in range [-90, 90], positive values indicate northern hemisphere (north of the Equator), negative - southern
    double latitude;
    // Longitude in range [-180, 180], positive values indicate positions east of the Prime Meridian (eastern hemisphere), negative - west
    double longitude;
    time_t timestamp; // Time of the position update
};

#endif // POSITION_H
