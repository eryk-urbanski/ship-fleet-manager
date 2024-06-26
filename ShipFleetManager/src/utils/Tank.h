// Tank.h

#ifndef TANK_H
#define TANK_H

#include "Fuel.h"
#include <stdexcept>

class Tank {
public:
	// Constructor
	Tank(double capacity, FuelType fuelType)
		: capacity(capacity), fuelType(fuelType), currentVolume(0) {
		if (capacity <= 0) {
			throw std::invalid_argument("Invalid capacity");
		}
	}

	// Set current volume
	void setCurrentVolume(double volume) {
		if (volume < 0) {
			throw std::invalid_argument("Volume must not be negative");
		}
		if (volume > capacity) {
			throw std::invalid_argument("Volume exceeds tank capacity");
		}
		currentVolume = volume;
	}

	// Getters
	double getCapacity() const { return capacity; }
	double getCurrentVolume() const { return currentVolume; }
	FuelType getFuelType() const { return fuelType; }

private:
	double capacity; // Capacity in litres
	double currentVolume; // Current volume in litres
	FuelType fuelType; // Designated fuel type
};

#endif // TANK_H