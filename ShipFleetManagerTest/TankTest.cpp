#include "pch.h"
#include "../ShipFleetManager/src/utils/Tank.h"

// Test Case 1: Valid Constructor Inputs
TEST(TankTest, ConstructorValidInputs) {
    Tank tank(500.0, DIESEL);
    EXPECT_DOUBLE_EQ(tank.getCapacity(), 500.0);
    EXPECT_DOUBLE_EQ(tank.getCurrentVolume(), 0.0);
    EXPECT_EQ(tank.getFuelType(), DIESEL);
}

// Test Case 2: Invalid Capacity
TEST(TankTest, ConstructorInvalidCapacity) {
    EXPECT_THROW(Tank(-1.0, DIESEL), std::invalid_argument);
    EXPECT_THROW(Tank(0.0, DIESEL), std::invalid_argument);
}
