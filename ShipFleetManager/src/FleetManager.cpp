#include "FleetManager.h"

FleetManager::FleetManager() {
    initializeCommands();
}

void FleetManager::handleCommand(const std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        throw std::invalid_argument("No command provided");
    }

    std::string command = tokens[0];
    auto it = commandMap.find(command);
    if (it == commandMap.end()) {
        throw std::invalid_argument("Unknown command");
    }

    CommandType commandType = it->second;

    switch (commandType) {
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
        throw std::invalid_argument("Unknown command");
    }
}

void FleetManager::showHelp()
{
    std::cout << "Available Commands:\n";
    std::cout << "  add <IMO> <IMO7digitnumber> <name> <length> <width> <type> <maxnumofcontainers> <maxtotalweight>\n";
    std::cout << "      - Register a new container ship\n";
    std::cout << "  add <IMO> <IMO7digitnumber> <name> <length> <width> <type> <maxnumdieseltanks> <maxnumheavyfueltanks> <maxtotalweight>\n";
    std::cout << "      - Register a new tanker thisp\n";
    std::cout << "  position <IMO> <IMO7digitnumber> <latitude> <longitude>\n";
    std::cout << "      - Update the position of a ship\n";
    std::cout << "  load <IMO> <IMO7digitnumber> <sender> <addressee> <description> <weight>\n";
    std::cout << "      - Load a container onto a ContainerShip\n";
    std::cout << "  unload <IMO> <IMO7digitnumber> <containerID>\n";
    std::cout << "      - Unload a container from a ContainerShip\n";
    std::cout << "  refuel <IMO> <IMO7digitnumber> <tankIndex> <fuelType> [<volume>]\n";
    std::cout << "      - Refuel a tank on a TankerShip, optionally specifying volume\n";
    std::cout << "  empty <IMO> <IMO7digitnumber> <tankIndex> [<volume>]\n";
    std::cout << "      - Empty a tank on a TankerShip, optionally specifying volume to remove\n";
}

void FleetManager::initializeCommands()
{
    commandMap["add"] = CommandType::AddShip;
    commandMap["position"] = CommandType::UpdatePosition;
    commandMap["load"] = CommandType::LoadContainer;
    commandMap["unload"] = CommandType::UnloadContainer;
    commandMap["refuel"] = CommandType::RefuelTank;
    commandMap["empty"] = CommandType::EmptyTank;
}

void FleetManager::addShip(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 9) {
        throw std::invalid_argument("Insufficient parameters to add a ship");
    }

    std::string imoPrefix = tokens[1];
    std::string imoNumber = tokens[2];
    if (imoPrefix != "IMO" || imoNumber.length() != 7) {
        throw std::invalid_argument("Invalid IMO number format");
    }
    std::string imo = imoPrefix + " " + imoNumber;

    if (fleet.find(imo) != fleet.end()) {
        throw std::invalid_argument("Ship with this IMO number already exists");
    }

    std::string name = tokens[3];
    double length = std::stod(tokens[4]);
    double width = std::stod(tokens[5]);
    std::string type = tokens[6];

    if (type == "ContainerShip") {
        if (tokens.size() != 9) {
            throw std::invalid_argument("Invalid number of arguments for a ContainerShip");
        }
        int maxContainers = std::stoi(tokens[7]);
        double maxWeight = std::stod(tokens[8]);

        auto ship = new ContainerShip(imo, name, length, width, maxContainers, maxWeight);
        fleet[imo] = ship;
        std::cout << "ContainerShip added successfully" << std::endl;
    }
    else if (type == "TankerShip") {
        if (tokens.size() != 10) {
            throw std::invalid_argument("Invalid number of arguments for a TankerShip");
        }

        int numDieselTanks = std::stoi(tokens[7]);
        int numHeavyFuelTanks = std::stoi(tokens[8]);
        double maxWeight = std::stod(tokens[9]);

        std::vector<double> dieselCapacities;
        std::vector<double> heavyFuelCapacities;

        std::cout << "Enter capacities for each Diesel tank:" << std::endl;
        for (int i = 0; i < numDieselTanks; ++i) {
            double capacity;
            std::cout << "Diesel tank " << (i + 1) << ": ";
            std::cin >> capacity;
            dieselCapacities.push_back(capacity);
        }

        std::cout << "Enter capacities for each Heavy Fuel tank:" << std::endl;
        for (int i = 0; i < numHeavyFuelTanks; ++i) {
            double capacity;
            std::cout << "Heavy Fuel tank " << (i + 1) << ": ";
            std::cin >> capacity;
            heavyFuelCapacities.push_back(capacity);
        }

        auto ship = new TankerShip(imo, name, length, width, numDieselTanks, dieselCapacities, numHeavyFuelTanks, heavyFuelCapacities, maxWeight);
        fleet[imo] = ship;
        std::cout << "TankerShip added successfully" << std::endl;
    }
    else {
        throw std::invalid_argument("Invalid ship type");
    }
}

void FleetManager::updatePosition(const std::vector<std::string>& tokens)
{
}

void FleetManager::loadContainer(const std::vector<std::string>& tokens)
{
}

void FleetManager::unloadContainer(const std::vector<std::string>& tokens)
{
}

void FleetManager::refuelTank(const std::vector<std::string>& tokens)
{
}

void FleetManager::emptyTank(const std::vector<std::string>& tokens)
{
}

Ship* FleetManager::findShipByIMO(const std::string& imo) const
{
    auto it = fleet.find(imo);
    if (it != fleet.end()) {
        return it->second;
    }
    return nullptr;
}


