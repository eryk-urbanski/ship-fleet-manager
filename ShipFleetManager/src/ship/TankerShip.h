// TankerShip.h

#ifndef TANKERSHIP_H
#define TANKERSHIP_H

#include "Ship.h"
#include "../utils/Tank.h"
#include <vector>
#include <stdexcept>
#include <iostream>

class TankerShip : public Ship {
public:
	//Constructor
	TankerShip(
		const std::string& imo, 
		const std::string& name, 
		double length, 
		double width,
		int numDieselTanks, 
		const std::vector<double>& capacitiesDiesel, 
		int numHeavyFuelTanks, 
		const std::vector<double>& capacitiesHeavyFuel, 
		double maxWeight);

	// Refuel tank
	void refuelTank(int tankID, FuelType fuelType);
	void refuelTank(int tankID, FuelType fuelType, double volume);

	// Empty tank
	void emptyTank(int tankID);
	void emptyTank(int tankID, double volume);

	// Getters
	int getNumDieselTanks() const { return numDieselTanks; }
	int getNumHeavyFuelTanks() const { return numHeavyFuelTanks; }
	double getMaxWeight() const { return maxWeight; }
	double getCurrentWeight() const { return currentWeight; }
	const std::vector<Tank>& getTanks() const { return tanks; }

private:
	int numDieselTanks;		// Total number of permanently installed Diesel tanks
	int numHeavyFuelTanks;	// Total number of permanently installed Heavy Fuel tanks
	double maxWeight;		// Max total weight in tons
	double currentWeight;	// Current weight in tons
	std::vector<Tank> tanks;

	void verifyTankID(int tankID) const;
	bool isValidTankID(int tankID) const;
};

#endif // TANKERSHIP_H
