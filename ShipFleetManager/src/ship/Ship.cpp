// Ship.cpp

#include "Ship.h"
#include <stdexcept>
#include <regex>

// Constructor implementation
Ship::Ship(const std::string& imo, const std::string& name, double length, double width)
    : name(name), length(length), width(width) {
    if (!isValidIMO(imo)) {
        throw std::invalid_argument("Invalid IMO number");
    }
    if (!isValidDimensions(length, width)) {
        throw std::invalid_argument("Invalid ship width or length (both should be positive)");
    }
    imoNumber = imo;
}

// Update Position
void Ship::updatePosition(const Position& position) {
    if (position.latitude < -90 || position.latitude > 90) {
        throw std::invalid_argument("Invalid latitude, should be within the <-90, 90> range");
    }
    if (position.longitude < -180 || position.longitude > 180) {
        throw std::invalid_argument("Invalid longitude, should be within the <-180, 180> range");
    }
    positionHistory.push_back(position);
}

// Validate IMO number format and checksum
bool Ship::isValidIMO(const std::string& imo) const {
    // Validate format
    std::regex imoPattern(R"(^IMO \d{7}$)");
    if (!std::regex_match(imo, imoPattern)) return false;

    // Validate checksum
    int sum = 0;
    for (int i = 4; i < 10; ++i) {
        sum += (imo[i] - '0') * (7 - (i - 4));
    }
    return sum % 10 == (imo[10] - '0');
}

// Validate ship dimensions
bool Ship::isValidDimensions(double length, double width) const {
    return length > 0 && width > 0;
}
