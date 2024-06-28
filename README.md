# assembly-line-cpp

## Project Overview

The assembly line in the solution comprises multiple workstations, each holding specific stock items. A line manager moves customer orders along the line, with each station filling the orders if the requested item is in stock. The process continues until all orders have been processed, resulting in either completed or incomplete orders based on inventory availability. The simulator then lists both completed and incomplete orders.

The main purpose of this project is develop an assembly line management system using C++ Object Oriented Programming concepts.

## Milestone 1 (MS1)
 Implementation and Testing of Utilities and Station Classes
- `Utilities`: Supports the parsing of input files that contain information used to set up and configure the assembly line.
- `Station`: Manages information about a specific station on the assembly line.

## Milestone 2 (MS2)
 Implementing CustomerOrder Class
- `CustomerOrder`: Contains all the functionality needed to process customer orders as they move from station to station along the assembly line.

## Milestone 3 (MS3)
 Implementation and Testing of Workstation and LineManager Classes
- `Workstation`: A specialized `Station` that the `LineManager` activates based on user input.
- `LineManager`: Configures the assembly line and moves `CustomerOrders` along it from start to finish.
