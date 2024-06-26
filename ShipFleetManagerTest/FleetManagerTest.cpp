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

/////////////////
// UpdatePosition

// Test Case 6: Update Valid Position
TEST(FleetManagerTest, UpdateValidPosition) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens);

    std::vector<std::string> updateArgs = { "position", "IMO", "9321483", "34.0522", "-118.2437" };
    EXPECT_NO_THROW(shipowner.handleCommand(updateArgs));
    Ship* ship = shipowner.findShipByIMO("IMO 9321483");
    ASSERT_NE(ship, nullptr);

    auto position = ship->getCurrentPosition();
    EXPECT_DOUBLE_EQ(position.latitude, 34.0522);
    EXPECT_DOUBLE_EQ(position.longitude, -118.2437);
}

// Test Case 7: Ship Not Found
TEST(FleetManagerTest, ShipNotFound) {
    FleetManager shipowner;
    std::vector<std::string> updateArgs = { "position", "IMO", "9321483", "34.0522", "-118.2437" };
    EXPECT_THROW(shipowner.handleCommand(updateArgs), std::invalid_argument);
}

// Test Case 8: Invalid Number of Arguments
TEST(FleetManagerTest, UpdatePositionInvalidNumberOfArguments) {
    FleetManager shipowner;
    std::vector<std::string> updateArgs = { "position", "IMO", "9321483" };
    EXPECT_THROW(shipowner.handleCommand(updateArgs), std::invalid_argument);
}

// Test Case 9: Invalid Argument Types
TEST(FleetManagerTest, UpdatePositionInvalidArgumentTypes) {
    FleetManager shipowner;
    std::vector<std::string> updateArgs = { "position", "IMO", "9321483", "not_a_number", "also_not_a_number" };
    EXPECT_THROW(shipowner.handleCommand(updateArgs), std::invalid_argument);
}

////////////////
// LoadContainer

// Test Case 10: Load Valid Container
TEST(FleetManagerTest, LoadValidContainer) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens);
    EXPECT_NO_THROW(shipowner.handleCommand({ "load", "IMO", "9321483", "Sender", "Receiver", "Electronics", "1000" }));
    auto ship = dynamic_cast<ContainerShip*>(shipowner.findShipByIMO("IMO 9321483"));
    ASSERT_NE(ship, nullptr);
    EXPECT_EQ(ship->getCurrentWeight(), 1000);
}

// Test Case 11: Ship Not Found
TEST(FleetManagerTest, LoadShipNotFound) {
    FleetManager shipowner;
    EXPECT_THROW(shipowner.handleCommand({ "load", "IMO", "9321483", "Sender", "Receiver", "Toys", "500" }), std::invalid_argument);
}

// Test Case 12: Exceeding Max Containers
TEST(FleetManagerTest, ExceedingMaxContainers) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "100", "156907.0" };
    shipowner.handleCommand(tokens);
    auto ship = dynamic_cast<ContainerShip*>(shipowner.findShipByIMO("IMO 9321483"));
    for (int i = 0; i < 100; ++i) {
        ship->loadContainer(Container("Sender", "Receiver", "Stuff", 10));
    }
    EXPECT_THROW(ship->loadContainer(Container("Sender", "Receiver", "Extra", 10)), std::invalid_argument);
}

// Test Case 13: Exceeding Max Weight
TEST(FleetManagerTest, LoadExceedingMaxWeight) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "100", "156907.0" };
    shipowner.handleCommand(tokens);
    EXPECT_THROW(shipowner.handleCommand({ "load", "IMO", "1234567", "Sender", "Receiver", "Heavy Stuff", "200000.0" }), std::invalid_argument);
}

//////////////////
// UnloadContainer

// Test Case 14: Unload Valid Container
TEST(FleetManagerTest, UnloadValidContainer) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens);
    shipowner.handleCommand({ "load", "IMO", "9321483", "Sender", "Receiver", "Electronics", "1000" });

    EXPECT_NO_THROW(shipowner.handleCommand({ "unload", "IMO", "9321483", "1" }));
    auto ship = dynamic_cast<ContainerShip*>(shipowner.findShipByIMO("IMO 9321483"));
    ASSERT_NE(ship, nullptr);
    EXPECT_EQ(ship->getContainers().size(), 0);
}

// Test Case 15: Ship Not Found
TEST(FleetManagerTest, UnloadShipNotFound) {
    FleetManager shipowner;
    EXPECT_THROW(shipowner.handleCommand({ "unload", "IMO", "9321483", "1" }), std::invalid_argument);
}

// Test Case 16: Container Not Found
TEST(FleetManagerTest, ContainerNotFound) {
    FleetManager shipowner;
    std::vector<std::string> tokens = { "add", "IMO", "9321483", "Emma Maersk", "397.0", "56.0", "ContainerShip", "15000", "156907.0" };
    shipowner.handleCommand(tokens);
    EXPECT_THROW(shipowner.handleCommand({ "unload", "IMO", "1234567", "3" }), std::invalid_argument);
}

/////////////
// RefuelTank

// Test Case 17: Refuel Valid Tank TODO

// Test Case 18: Ship Not Found
TEST(FleetManagerTest, RefuelShipNotFound) {
    FleetManager shipowner;
    EXPECT_THROW(shipowner.handleCommand({ "refuel", "IMO", "9321483", "1", "500" }), std::invalid_argument);
}

// Test Case 19: Invalid Ship Type TODO

// Test Case 20: Tank Not Found TODO

////////////
// EmptyTank

// Test Case 21: Empty Valid Tank TODO

// Test Case 22: Ship Not Found
TEST(FleetManagerTest, EmptyShipNotFound) {
    FleetManager shipowner;
    EXPECT_THROW(shipowner.handleCommand({ "empty", "IMO", "9321483", "1", "500" }), std::invalid_argument);
}

// Test Case 23: Invalid Ship Type TODO

// Test Case 24: Tank Not Found TODO