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

// Test Case 3: Valid setCurrentVolume
TEST(TankTest, ValidSetCurrentVolume) {
    Tank tank(500.0, DIESEL);
    EXPECT_NO_THROW(tank.setCurrentVolume(50.0));
    EXPECT_DOUBLE_EQ(tank.getCurrentVolume(), 50.0);
}

// Test Case 4: Negative Volume
TEST(TankTest, NegativeVolume) {
    Tank tank(500.0, DIESEL);
    EXPECT_THROW(tank.setCurrentVolume(-1.0), std::invalid_argument);
}

// Test Case 5: Exceed Capacity
TEST(TankTest, ExceedCapacity) {
    Tank tank(500.0, DIESEL);
    EXPECT_THROW(tank.setCurrentVolume(1500.0), std::invalid_argument);
}