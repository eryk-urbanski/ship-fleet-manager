// Container.h

#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <stdexcept>

class Container {
public:
    // Constructor
    Container(
        const std::string& sender, 
        const std::string& addressee,
        const std::string& cargoDescription, 
        double weight)
        : sender(sender), addressee(addressee), cargoDescription(cargoDescription), weight(weight) {
        if (weight <= 0) {
            throw std::invalid_argument("Weight cannot be negative or zero");
        }
    }

    // Getters
    std::string getSender() const { return sender; }
    std::string getAddressee() const { return addressee; }
    std::string getCargoDescription() const { return cargoDescription; }
    double getWeight() const { return weight; }

private:
    std::string sender;
    std::string addressee;
    std::string cargoDescription;
    double weight;
};

#endif // CONTAINER_H
