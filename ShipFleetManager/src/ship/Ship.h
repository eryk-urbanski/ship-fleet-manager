// Ship.h

#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include <stdexcept>
#include "../utils/Position.h"

class Ship {
public:
    // Constructor
    Ship(const std::string& imo, const std::string& name, double length, double width);

    // Destructor
    virtual ~Ship() {}

    // Update Position
    void updatePosition(const Position& position);

    // Getters
    std::string getIMONumber() const { return imoNumber; };
    std::string getName() const { return name; };
    double getLength() const { return length; };
    double getWidth() const { return width; };
    std::vector<Position> getPositionHistory() const { return positionHistory; };
    Position getCurrentPosition() const {
        if (!positionHistory.empty()) {
            return positionHistory.back();
        }
        throw std::runtime_error("No position history available");
    }

protected:
    std::string imoNumber;
    std::string name;
    double length;
    double width;
    std::vector<Position> positionHistory;

private:
    bool isValidIMO(const std::string& imo) const;
    bool isValidDimensions(double length, double width) const;
};

#endif // SHIP_H
