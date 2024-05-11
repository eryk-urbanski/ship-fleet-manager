// ContainerShip.cpp

#include "ContainerShip.h"

// Constructor implementation
ContainerShip::ContainerShip(
    const std::string& imo, 
    const std::string& name, 
    double length, double width,
    int maxContainers, 
    double maxWeight)
    : Ship(imo, name, length, width), maxContainers(maxContainers), maxWeight(maxWeight), currentWeight(0) {
    if (maxContainers <= 0) {
        throw std::invalid_argument("Invalid max containers");
    }
    if (maxWeight <= 0) {
        throw std::invalid_argument("Invalid max weight");
    }
}

// Load container
void ContainerShip::loadContainer(const Container& container) {
    if (containers.size() >= maxContainers) {
        throw std::invalid_argument("Cannot load container: Max containers reached");
    }
    if (currentWeight + container.getWeight() > maxWeight) {
        throw std::invalid_argument("Cannot load container: Max weight exceeded");
    }

    containers.push_back(container);
    currentWeight += container.getWeight();
    std::cout << "Successfully loaded container with ID: " << containers.size() << " onto ship " << imoNumber << std::endl;
}

// Unload container
void ContainerShip::unloadContainer(int containerID) {
    if (containerID < 1 || containerID > containers.size()) {
        throw std::invalid_argument("Invalid container ID");
    }

    currentWeight -= containers[containerID - 1].getWeight();
    containers.erase(containers.begin() + (containerID - 1));
    std::cout << "Successfully unloaded container: " << containerID << std::endl;
}
