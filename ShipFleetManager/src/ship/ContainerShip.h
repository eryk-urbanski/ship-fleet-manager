// ContainerShip.h

#ifndef CONTAINERSHIP_H
#define CONTAINERSHIP_H

#include "Ship.h"
#include "../utils/Container.h"
#include <vector>
#include <iostream>
#include <stdexcept>

class ContainerShip : public Ship {
public:
    // Constructor
    ContainerShip(
        const std::string& imo, 
        const std::string& name, 
        double length, 
        double width,
        int maxContainers, 
        double maxWeight);

    // Load container
    void loadContainer(const Container& container);

    // Unload container
    void unloadContainer(int containerID);

    // Getters
    int getMaxContainers() const { return maxContainers; }
    double getMaxWeight() const { return maxWeight; }
    double getCurrentWeight() const { return currentWeight; }
    std::vector<Container> getContainers() const { return containers; }

private:
    int maxContainers;
    double maxWeight; // Max weight in tons
    double currentWeight; // Current weight in tons
    std::vector<Container> containers;
};

#endif // CONTAINERSHIP_H
