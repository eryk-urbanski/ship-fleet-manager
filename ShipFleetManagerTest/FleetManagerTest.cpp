#include "pch.h"
#include "../ShipFleetManager/src/FleetManager.cpp"

//////////
// AddShip

// Test Case 1: Add Valid ContainerShip
TEST(FleetManagerTest, AddValidContainerShip) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens);
    auto ship = shipowner.findShipByIMO("IMO 9321483");
    ASSERT_NE(ship, nullptr);
    auto containerShip = dynamic_cast<ContainerShip*>(ship);
    ASSERT_NE(containerShip, nullptr);

    EXPECT_DOUBLE_EQ(containerShip->getLength(), 397.0);
    EXPECT_DOUBLE_EQ(containerShip->getWidth(), 56.0);
    EXPECT_EQ(containerShip->getMaxContainers(), 15000);
    EXPECT_DOUBLE_EQ(containerShip->getMaxWeight(), 156907.0);
}

// Test Case 2: Add Valid TankerShip TODO

// Test Case 3: Duplicate IMO Number
TEST(FleetManagerTest, DuplicateIMONumber) {
    FleetManager shipowner;
    std::vector<std::string> tokens1 = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    std::vector<std::string> tokens2 = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens1);
    EXPECT_THROW(shipowner.handleCommand(tokens2), std::invalid_argument);
}

// Test Case 4: Invalid Number of Arguments
TEST(FleetManagerTest, InvalidNumberOfArguments) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0" };
    EXPECT_THROW(shipowner.handleCommand(tokens), std::invalid_argument);
}

// Test Case 5: Invalid Argument Types
TEST(FleetManagerTest, InvalidArgumentTypes) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "1234ABC", "Leviathan", "three hundred", "fifty", "ContainerShip", "one thousand", "twenty thousand" };
    EXPECT_THROW(shipowner.handleCommand(tokens), std::invalid_argument);
}