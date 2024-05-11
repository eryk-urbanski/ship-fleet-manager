#ifndef FLEETMANAGER_H
#define FLEETMANAGER_H

#include "../src/ship/Ship.h"
#include "../src/ship/ContainerShip.h"
#include "../src/ship/TankerShip.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Enum for user commands
enum class CommandType {
    AddShip,
    UpdatePosition,
    LoadContainer,
    UnloadContainer,
    RefuelTank,
    EmptyTank
};

class FleetManager {
public:
    FleetManager();

    // Command interface method
    void handleCommand(const std::vector<std::string>& tokens);
    void showHelp() const;
    void showFleet() const;

    Ship* findShipByIMO(const std::string& imo) const;

private:
    std::unordered_map<std::string, Ship*> fleet;
    std::unordered_map<std::string, CommandType> commandMap;

    void initializeCommands();
    // Command handlers
    void addShip(const std::vector<std::string>& tokens);
    void updatePosition(const std::vector<std::string>& tokens);
    void loadContainer(const std::vector<std::string>& tokens);
    void unloadContainer(const std::vector<std::string>& tokens);
    void refuelTank(const std::vector<std::string>& tokens);
    void emptyTank(const std::vector<std::string>& tokens);
};

#endif // FLEETMANAGER_H
