#include "FleetManager.h"
#include <iostream>
#include <stdexcept>

FleetManager::FleetManager() {}

void FleetManager::handleCommand(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        std::cerr << "No command provided" << std::endl;
        return;
    }

    CommandType command;
    try {
        command = static_cast<CommandType>(std::stoi(tokens[0]));
    }
    catch (const std::exception& e) {
        std::cerr << "Invalid command type" << std::endl;
        return;
    }

    switch (command) {
    case CommandType::AddShip:
        addShip(tokens);
        break;
    case CommandType::UpdatePosition:
        updatePosition(tokens);
        break;
    case CommandType::LoadContainer:
        loadContainer(tokens);
        break;
    case CommandType::UnloadContainer:
        unloadContainer(tokens);
        break;
    case CommandType::RefuelTank:
        refuelTank(tokens);
        break;
    case CommandType::EmptyTank:
        emptyTank(tokens);
        break;
    default:
        std::cerr << "Unknown command" << std::endl;
        break;
    }
}

// Implementations for each command handling method would follow...

