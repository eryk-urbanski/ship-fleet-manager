#include "pch.h"
#include "../ShipFleetManager/src/utils/Container.h"

// Test Case 1: Valid Constructor Inputs
TEST(ContainerTest, ConstructorValidInput) {
    Container container("John Doe", "Jane Smith", "Electronics", 10.0);
    ASSERT_EQ(container.getSender(), "John Doe");
    ASSERT_EQ(container.getAddressee(), "Jane Smith");
    ASSERT_EQ(container.getCargoDescription(), "Electronics");
    ASSERT_DOUBLE_EQ(container.getWeight(), 10.0);
}

TEST(ContainerTest, ConstructorInvalidWeight) {
    EXPECT_THROW(Container("John Doe", "Jane Smith", "Electronics", -10.0), std::invalid_argument);
    EXPECT_THROW(Container("John Doe", "Jane Smith", "Electronics", 0.0), std::invalid_argument);
}

TEST(ContainerTest, ConstructorEmptyStrings) {
    Container container("", "", "", 10.0);
    ASSERT_EQ(container.getSender(), "");
    ASSERT_EQ(container.getAddressee(), "");
    ASSERT_EQ(container.getCargoDescription(), "");
}