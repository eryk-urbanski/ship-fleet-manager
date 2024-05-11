# Ship Fleet Manager

Ship Fleet Management Application written in C++. 

Each ship has its own global unique IMO number, a name, length and width, current position (longitude and latitude), cargo in a form of containers or tanks and a maximum load. Containers have a sender, an addressee, cargo description and weight. Tanks are permanently installed on ships, each has its own capacity value and can be filled with one of two different types of fuel: Diesel or Heavy Fuel, each of those types being characterized by a different density. 

## Features
 - Basic functionalities enabling ship fleet management
   - adding ships of two types, listed below, to the fleet
     - container ship
     - tanker ship
   - ship position update, maintaining the position history 
   - loading containers onto container ships
   - unloading containers from container ships
   - refueling tanks permanently installed on tanker ships
   - emptying tanks 
 - Unit testing support, through GoogleTest
