#include "pch.h"
#include "../ShipFleetManager/src/ship/ContainerShip.cpp"
#include "../ShipFleetManager/src/utils/Container.h"

// Test Case 1: Valid Constructor Inputs
TEST(ContainerShipTest, ValidConstructorInputs) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    double length = 397.0;
    double width = 56.0;
    int maxContainers = 15000;
    double maxWeight = 156907.0;

    ContainerShip ship(imo, name, length, width, maxContainers, maxWeight);

    EXPECT_EQ(ship.getMaxContainers(), maxContainers);
    EXPECT_DOUBLE_EQ(ship.getMaxWeight(), maxWeight);
    EXPECT_DOUBLE_EQ(ship.getCurrentWeight(), 0);
    EXPECT_TRUE(ship.getContainers().empty());
}

// Test Case 2: Invalid Constructor Inputs
TEST(ContainerShipTest, InvalidConstructorInputs) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";

    // Invalid max containers
    EXPECT_THROW(ContainerShip(imo, name, 397.0, 56.0, 0, 156907.0), std::invalid_argument); // Zero maxContainers
    EXPECT_THROW(ContainerShip(imo, name, 397.0, 56.0, -1, 156907.0), std::invalid_argument); // Negative maxContainers

    // Invalid max weight
    EXPECT_THROW(ContainerShip(imo, name, 397.0, 56.0, 100, 0.0), std::invalid_argument); // Zero maxWeight
    EXPECT_THROW(ContainerShip(imo, name, 397.0, 56.0, 100, -100.0), std::invalid_argument); // Negative maxWeight
}

// Test Case 3: Valid Load Container
TEST(ContainerShipTest, ValidLoadContainer) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    ContainerShip ship(imo, name, 397.0, 56.0, 15000, 156907.0);

    Container container("Sender", "Receiver", "Electronics", 1000.0);

    ship.loadContainer(container);

    EXPECT_EQ(ship.getContainers().size(), 1);
    EXPECT_DOUBLE_EQ(ship.getCurrentWeight(), 1000.0);
}

// Test Case 4: Exceed Max Containers
TEST(ContainerShipTest, ExceedMaxContainers) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    ContainerShip ship(imo, name, 397.0, 56.0, 1, 156907.0);

    Container container1("Sender1", "Receiver1", "Electronics", 1000.0);
    Container container2("Sender2", "Receiver2", "Electronics", 1000.0);

    ship.loadContainer(container1);
    EXPECT_THROW(ship.loadContainer(container2), std::invalid_argument); // Should fail to load

    EXPECT_EQ(ship.getContainers().size(), 1); // Only one should be loaded
    EXPECT_DOUBLE_EQ(ship.getCurrentWeight(), 1000.0);
}

// Test Case 5: Exceed Max Weight
TEST(ContainerShipTest, ExceedMaxWeight) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    ContainerShip ship(imo, name, 397.0, 56.0, 15000, 1500.0);

    Container container1("Sender1", "Receiver1", "Electronics", 1000.0);
    Container container2("Sender2", "Receiver2", "Electronics", 600.0);

    ship.loadContainer(container1);
    EXPECT_THROW(ship.loadContainer(container2), std::invalid_argument); // Should fail to load

    EXPECT_EQ(ship.getContainers().size(), 1); // Only one should be loaded
    EXPECT_DOUBLE_EQ(ship.getCurrentWeight(), 1000.0);
}

// Test Case 6: Valid Unload Container
TEST(ContainerShipTest, ValidUnloadContainer) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    ContainerShip ship(imo, name, 397.0, 56.0, 15000, 156907.0);

    Container container("Sender", "Receiver", "Electronics", 1000.0);

    ship.loadContainer(container);
    ship.unloadContainer(1);

    EXPECT_TRUE(ship.getContainers().empty());
    EXPECT_DOUBLE_EQ(ship.getCurrentWeight(), 0.0);
}

// Test Case 7: Invalid Unload Container
TEST(ContainerShipTest, InvalidUnloadContainer) {
    std::string imo = "IMO 9321483";
    std::string name = "Emma Maersk";
    ContainerShip ship(imo, name, 397.0, 56.0, 15000, 156907.0);

    Container container("Sender", "Receiver", "Electronics", 1000.0);

    ship.loadContainer(container);

    // Invalid ID: negative or zero
    EXPECT_THROW(ship.unloadContainer(0), std::invalid_argument);
    EXPECT_EQ(ship.getContainers().size(), 1);
    EXPECT_THROW(ship.unloadContainer(-1), std::invalid_argument);
    EXPECT_EQ(ship.getContainers().size(), 1);

    // Invalid ID: exceeding the total number of containers
    EXPECT_THROW(ship.unloadContainer(2), std::invalid_argument);
    EXPECT_EQ(ship.getContainers().size(), 1);
}
