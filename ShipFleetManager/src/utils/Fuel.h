// Fuel.h

#ifndef FUEL_H
#define FUEL_H

#include <unordered_map>

// Enum to represent different fuel types
enum FuelType { DIESEL, HEAVY_FUEL };

// A map to hold the density of each fuel type in kg/litre
const std::unordered_map<FuelType, double> fuelDensity = {
	{DIESEL, 0.85}, // Diesel density in kg/liter
	{HEAVY_FUEL, 0.96} // Heavy fuel density in kg/litre
};

#endif // FUEL_H