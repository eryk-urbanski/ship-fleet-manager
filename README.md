# Ship Fleet Manager

Ship Fleet Management Application written in C++. 

Each ship has its own global unique IMO number, name, length and width, current position (latitude and longitude), cargo in the form of containers or tanks and maximum load. Containers have information about the sender, addressee, cargo description and weight. Tanks are permanently installed on ships, each has its capacity and can be filled with one of two different types of fuel: Diesel or Heavy Fuel, each of those types being characterized by a different density. 

## Features
 - **Basic functionalities enabling ship fleet management**:
   - **Adding ships of two types to the fleet**:
     - **Container Ship**: Allows containers management
     - **Tanker Ship**: Supports operations on permanently installed tanks
   - **Ship position update**: Maintains the position history 
   - **Loading containers onto container ships**: Facilitates cargo management
   - **Unloading containers from container ships**: Manages cargo offloading
   - **Refueling tanks on tanker ships**: Ensures fuel management of tanks permanently installed on tanker ships 
   - **Emptying tanks**: Manages the emptying process of fuel tanks 
 - **REPL Console Interface**: Provides an interactive command-line interface that lets users execute commands in a read-eval-print loop
 - **Unit Testing Support**: Implemented through GoogleTest to ensure the reliability and correctness of the software
