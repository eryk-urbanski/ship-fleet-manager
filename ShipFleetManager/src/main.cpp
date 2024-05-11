#include "FleetManager.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    FleetManager shipowner;
    std::string input;

    std::cout << "Welcome to the Ship Fleet Management System!" << std::endl;
    shipowner.showHelp();
    std::cout << "Please enter a command to manage your fleet, or type 'help' for command list, or 'exit' to quit:" << std::endl;


    // Process commands until the user decides to exit
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        // Check if user wants to exit
        if (input == "exit") {
            break;
        }

        // Print the commands again if user asks for help
        if (input == "help") {
            shipowner.showHelp();
            continue;
        }

        // Print the commands again if user asks for help
        if (input == "fleet") {
            shipowner.showFleet();
            continue;
        }

        // Split the input into tokens
        std::istringstream iss(input);
        std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

        // Check if there is a command provided
        if (tokens.empty()) {
            std::cerr << "No command provided. Please try again." << std::endl;
            continue;
        }

        // Delegate the command to the FleetManager
        try {
            shipowner.handleCommand(tokens);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "Thank you for using the Ship Fleet Management System. Goodbye!" << std::endl;
    return 0;
}

