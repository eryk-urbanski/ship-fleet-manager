#include "pch.h"
#include "../ShipFleetManager/src/ship/TankerShip.cpp"
#include "../ShipFleetManager/src/utils/Tank.h"
#include "../ShipFleetManager/src/utils/Fuel.h"

// Test Case 1: Valid Constructor Inputs
TEST(TankerShipTest, ValidConstructorInputs) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    double length = 397.0;
    double width = 56.0;
    int numDieselTanks = 2;
    std::vector<double> dieselCapacities = { 1000.0, 1500.0 };
    int numHeavyFuelTanks = 1;
    std::vector<double> heavyFuelCapacities = { 2000.0 };
    double maxWeight = 5000.0;

    TankerShip ship(imo, name, length, width, numDieselTanks, dieselCapacities, numHeavyFuelTanks, heavyFuelCapacities, maxWeight);

    EXPECT_EQ(numDieselTanks, ship.getNumDieselTanks());
    EXPECT_EQ(numHeavyFuelTanks, ship.getNumHeavyFuelTanks());
    EXPECT_EQ(dieselCapacities.size() + heavyFuelCapacities.size(), ship.getTanks().size());
    EXPECT_DOUBLE_EQ(maxWeight, ship.getMaxWeight());
    EXPECT_DOUBLE_EQ(0, ship.getCurrentWeight());
}

// Test Case 2: Invalid Constructor Inputs
TEST(TankerShipTest, InvalidConstructorInputs) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    double length = 397.0;
    double width = 56.0;
    std::vector<double> emptyDieselCapacities;
    std::vector<double> emptyHeavyFuelCapacities;
    std::vector<double> dieselCapacities = { 2000.0 };
    std::vector<double> heavyFuelCapacities = { 2000.0 };
    double maxWeight = 5000.0;

    // Negative tanks
    EXPECT_THROW(TankerShip(imo, name, length, width, -1, dieselCapacities, 1, heavyFuelCapacities, maxWeight), std::invalid_argument); // Negative Diesel tanks
    EXPECT_THROW(TankerShip(imo, name, length, width, 1, dieselCapacities, -1, heavyFuelCapacities, maxWeight), std::invalid_argument); // Negative heavy fuel tanks

    // Zero tanks
    EXPECT_THROW(TankerShip(imo, name, length, width, 0, emptyDieselCapacities, 0, emptyHeavyFuelCapacities, maxWeight), std::invalid_argument);

    // Capacities length do not match
    EXPECT_THROW(TankerShip(imo, name, length, width, 7, dieselCapacities, 1, heavyFuelCapacities, maxWeight), std::invalid_argument);
}

// Test Case 3: Valid Refuel
TEST(TankerShipTest, ValidRefuel) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    TankerShip ship(imo, name, 397.0, 56.0, 1, { 1000.0 }, 1, { 2000.0 }, 156907.0);

    ship.refuelTank(1, 500.0);
    EXPECT_DOUBLE_EQ(500.0 * fuelDensity.at(DIESEL), ship.getCurrentWeight());
}

// Test Case 4: Refuel Wrong Tank ID
TEST(TankerShipTest, RefuelWrongTankID) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    TankerShip ship(imo, name, 397.0, 56.0, 1, { 1000.0 }, 1, { 2000.0 }, 156907.0);

    EXPECT_THROW(ship.refuelTank(3, 100.0), std::invalid_argument);
}

// Test Case 5: Exceed Max Weight
TEST(TankerShipTest, ExceedMaxWeight) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    TankerShip ship(imo, name, 397.0, 56.0, 1, { 1000.0 }, 1, { 2000.0 }, 156907.0);

    EXPECT_THROW(ship.refuelTank(1, 6000.0), std::invalid_argument);
}

// Test Case 6: Valid Empty Tank
TEST(TankerShipTest, ValidEmptyTank) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    TankerShip ship(imo, name, 397.0, 56.0, 1, { 1000.0 }, 1, { 2000.0 }, 156907.0);

    ship.refuelTank(1, 500.0);
    ship.emptyTank(1);
    EXPECT_DOUBLE_EQ(0.0, ship.getCurrentWeight());
}

// Test Case 7: Empty Invalid Tank ID
TEST(TankerShipTest, EmptyInvalidTankID) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    TankerShip ship(imo, name, 397.0, 56.0, 1, { 1000.0 }, 1, { 2000.0 }, 156907.0);

    ship.refuelTank(1, 500.0);
    EXPECT_THROW(ship.emptyTank(3), std::invalid_argument);
}
