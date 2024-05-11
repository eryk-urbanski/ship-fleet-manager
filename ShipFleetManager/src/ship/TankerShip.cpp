// TankerShip.cpp

#include "TankerShip.h"

TankerShip::TankerShip(
    const std::string& imo,
    const std::string& name,
    double length,
    double width,
    int numDieselTanks,
    const std::vector<double>& capacitiesDiesel,
    int numHeavyFuelTanks,
    const std::vector<double>& capacitiesHeavyFuel,
    double maxWeight)
    : Ship(imo, name, length, width), numDieselTanks(numDieselTanks), numHeavyFuelTanks(numHeavyFuelTanks), maxWeight(maxWeight), currentWeight(0) {
    // Check for negative number of tanks
    if (numDieselTanks < 0 || numHeavyFuelTanks < 0) {
        throw std::invalid_argument("Invalid Diesel or Heavy Fuel tank number");
    }
    // Check for zero tanks in total
    if (numDieselTanks <= 0 && numHeavyFuelTanks <= 0) {
        throw std::invalid_argument("There should be at least one tank permanently installed on the ship");
    }
    // Check for capacities lists validity
    if (static_cast<int>(capacitiesDiesel.size()) != numDieselTanks || static_cast<int>(capacitiesHeavyFuel.size()) != numHeavyFuelTanks) {
        throw std::invalid_argument("Diesel or Heavy Fuel capacities list length does not match the number of tanks");
    }
    // Create Diesel tanks
    for (auto capacity : capacitiesDiesel) {
        if (capacity <= 0) {
            throw std::invalid_argument("Invalid capacity value in Diesel tank capacities");
        }
        tanks.emplace_back(capacity, DIESEL);
    }
    // Create Heavy Fuel tanks
    for (auto capacity : capacitiesHeavyFuel) {
        if (capacity <= 0) {
            throw std::invalid_argument("Invalid capacity value in Heavy Fuel tank capacities");
        }
        tanks.emplace_back(capacity, HEAVY_FUEL);
    }

    std::cout << "Diesel tanks 1 to " << numDieselTanks
        << " and Heavy fuel tanks " << numDieselTanks + 1 << " to "
        << numDieselTanks + numHeavyFuelTanks << " successfully created." << std::endl;
}

void TankerShip::refuelTank(int tankID) {
    verifyTankID(tankID);

    Tank& tank = tanks[tankID - 1];
    double refillAmount = tank.getCapacity() - tank.getCurrentVolume();
    refuelTank(tankID, refillAmount);
}

void TankerShip::refuelTank(int tankID, double volume) {
    verifyTankID(tankID);
    Tank& tank = tanks[tankID - 1];
    FuelType fuelType = tank.getFuelType();
    if (currentWeight + volume * fuelDensity.at(fuelType) > maxWeight) {
        throw std::invalid_argument("Exceeds ship's maximum total weight");
    }

    tank.setCurrentVolume(tank.getCurrentVolume() + volume);
    currentWeight += volume * fuelDensity.at(fuelType);
    std::cout << "Tank " << tankID << " refueled with " << volume << " liters of " << fuelType << std::endl;
}

void TankerShip::emptyTank(int tankID) {
    verifyTankID(tankID);

    Tank& tank = tanks[tankID - 1];
    double volume = tank.getCurrentVolume();
    emptyTank(tankID, volume);
}

void TankerShip::emptyTank(int tankID, double volume) {
    verifyTankID(tankID);
    if (volume > tanks[tankID - 1].getCurrentVolume()) {
        throw std::invalid_argument("Provided volume is larger than the tank's current volume");
    }

    Tank& tank = tanks[tankID - 1];
    tank.setCurrentVolume(tank.getCurrentVolume() - volume);
    currentWeight -= volume * fuelDensity.at(tank.getFuelType());
    std::cout << "Tank " << tankID << " emptied to " << tank.getCurrentVolume() << " litres" << std::endl;
}

void TankerShip::verifyTankID(int tankID) const
{
    if (!isValidTankID(tankID)) {
        throw std::invalid_argument("Invalid tank ID");
    }
}

bool TankerShip::isValidTankID(int tankID) const {
    return tankID > 0 && tankID <= static_cast<int>(tanks.size());
}
