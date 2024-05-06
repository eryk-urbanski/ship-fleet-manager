#include "pch.h"
#include "../ShipFleetManager/src/ship/Ship.cpp"
#include "../ShipFleetManager/src/utils/Position.h"

// Test Case 1: Valid Inputs
TEST(ShipTest, ValidInputs) {
    std::string imo = "IMO 9074729";
    std::string name = "Black Pearl";
    double length = 300.5;
    double width = 40.0;

    Ship ship(imo, name, length, width);

    EXPECT_EQ(ship.getIMONumber(), imo);
    EXPECT_EQ(ship.getName(), name);
    EXPECT_DOUBLE_EQ(ship.getLength(), length);
    EXPECT_DOUBLE_EQ(ship.getWidth(), width);
}

// Test Case 2: Invalid IMO Number Format
TEST(ShipTest, InvalidIMONumberFormat) {
    std::string invalidIMO = "12345";
    std::string name = "Black Pearl";
    double length = 300.5;
    double width = 40.0;

    EXPECT_THROW(Ship(invalidIMO, name, length, width), std::invalid_argument);
}

// Test Case 3: Invalid IMO Number Checksum
TEST(ShipTest, InvalidIMONumberChecksum) {
    std::string invalidIMO = "IMO 9074725"; // Fails checksum
    std::string name = "Black Pearl";
    double length = 300.5;
    double width = 40.0;

    EXPECT_THROW(Ship(invalidIMO, name, length, width), std::invalid_argument);
}

// Test Case 4: Negative or Zero Length/Width
TEST(ShipTest, InvalidLengthOrWidth) {
    std::string imo = "IMO 9074729";
    std::string name = "Black Pearl";

    EXPECT_THROW(Ship(imo, name, -300.5, 40.0), std::invalid_argument); // Negative length
    EXPECT_THROW(Ship(imo, name, 300.5, -40.0), std::invalid_argument); // Negative width
    EXPECT_THROW(Ship(imo, name, 0.0, 40.0), std::invalid_argument);    // Zero length
    EXPECT_THROW(Ship(imo, name, 300.5, 0.0), std::invalid_argument);   // Zero width
}

// Test Case 5: Valid Position Update
TEST(ShipTest, ValidPositionUpdate) {
    std::string imo = "IMO 9074729";
    std::string name = "Black Pearl";
    double length = 300.5;
    double width = 40.0;
    Ship ship(imo, name, length, width);

    double lat = 12.34;
    double lon = 56.78;
    Position pos = { lat, lon, time(nullptr) };
    ship.updatePosition(pos);

    ASSERT_EQ(ship.getPositionHistory().size(), 1);
    EXPECT_DOUBLE_EQ(ship.getPositionHistory().back().latitude, lat);
    EXPECT_DOUBLE_EQ(ship.getPositionHistory().back().longitude, lon);
}

// Test Case 6: Invalid Position Update
TEST(ShipTest, InvalidPositionUpdate) {
    std::string imo = "IMO 9074729";
    std::string name = "Black Pearl";
    double length = 300.5;
    double width = 40.0;
    Ship ship(imo, name, length, width);

    Position invalidLat = { 100.0, 56.78, time(nullptr) };
    EXPECT_THROW(ship.updatePosition(invalidLat), std::invalid_argument);

    Position invalidLon = { 12.34, 200.0, time(nullptr) };
    EXPECT_THROW(ship.updatePosition(invalidLon), std::invalid_argument);
}