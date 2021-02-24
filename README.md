# ato
Airplane Tickets Office

## 1. Introduction

The developed software product is designed for storing and processing data in the transport sector: it creates a database of aircraft and flights between cities and has the following functionality: storing, adding, deleting and changing information about flights; selecting a route from one city to another with the lowest cost; selecting a route that takes the least time to transfer.
The program is designed for the Windows operating system. Despite the fact that the size of the required memory depends on the amount of information stored in the database, it does not require large amounts of memory for its operation, since one unit of information (record) in the database occupies 576 bytes (with 10 flights entered). With a large margin, you can set limits of 100 MB of RAM and disk space.

## 2. Course design assignment

* Replenishment of the database
* Edit the database
* Delete records
* Selection of the route with the shortest waiting time for a transfer
* Selection of the route with the lowest cost

## 3. Technical specifications and application limitations

Input information from the user is expected only in text format. The selection in the menu is organized using a list of numbers, one of which must be entered to activate the corresponding functionality. In this section, the program handles possible input errors, such as characters, invalid numbers. If you enter an error, you will be prompted to make a selection again.
When filling in the database, the user must follow the instructions that indicate the input format. The program allows you to add several entries to the database at once, for example, to add a record about an airplane and its departure point, you need to list the names of cities separated by a space, tab, or a new line character. A mismatch of the entered data should not cause an error (one exception: entering a value that must be an integer), but will result in a meaningless display of the information. Important requirement: The input must end with the EOF file (Cntr + Z), which is also indicated in the instructions while the program is running.

## 4. Data structure

The data structure used is a dynamic array of pointers to the structure containing information about the departure point of the aircraft, the number of flights to different cities. This structure also contains a nested array of pointers to another structure, which stores the name of the destination, the time of departure and arrival, as well as the cost of the flight.
Thus, the program uses a graph model (each name is its node, each pointer in the array in the nested structure is its edge), which is necessary for the implementation of route selection.
The size of the names is determined by a constant and is equal to 40 bytes, therefore, it is assumed that the name of the city does not exceed 40 characters.
Both arrays of pointers are dynamic, the memory for the array is reallocated, thereby increasing it in portions: when overflowing, memory for 5 pointers is added, the number 5 is defined by a constant.

## 5. Algorithm diagram

To solve the problem, algorithms were developed for searching through an array of pointers and checking the structures they point to by their contents; writing to a file and reading from a file in which all the database data is stored in the same non-empty blocks when memory is freed during the program shutdown.
The main task was to implement route selection, and for this purpose, the well-known Dijkstra and breadth-first search algorithms were used.
Dijkstra's algorithm allows you to find the path from one node to another with the lowest total weight in a weighted graph.
General view of the algorithm:
1. Find the node with the lowest cost
2. Update the values of its neighboring nodes
3. Repeat steps 1 and 2 until all the nodes of the graph are processed
4. Calculate the final path
The algorithm has limitations that may affect the correctness of the program:
1. The algorithm works only with directed acyclic graphs
2. The algorithm does not work with negative weight
If any of the flight costs are negative in the database, or, for example, flights from A to B and from B to A are recorded in it at the same time, the algorithm will not work, and the behavior of the program will be undefined.
The breadth-first search algorithm finds the path from node to node with the fewest other nodes between them, and also lets you know if there is even a path between two nodes. If we formalize the problem by assuming that the waiting time for transfers is always the same, then the least waiting time will be for the least number of transfers, so this algorithm is suitable for selecting such a route.
General view of the algorithm:
1. Create a queue, place the departure point in it
2. Remove an item from the queue
3. Check the item for the destination
4. If the destination is complete, otherwise add all adjacent items to the queue
5. Repeat steps 2-4 until the queue is empty
6. If the queue is empty, the route does not exist
Unlike Dijkstra's algorithm, the breadth-first search algorithm has no restrictions on the types of graphs on which it is implemented.

## 6. Instructions for use

The user needs to run the module being used with the name ato.exe, then select the menu items by entering the number displayed next to the item of interest. The database is edited in accordance with the instructions displayed on the console screen. When selecting a route, the user also needs to follow the instructions on the screen: enter the names of cities. The input during editing must match the specified format. Exit with saving is possible only in the main menu, in the nested menus, exit from the program does not provide for saving all changes in the file.

## 7. Specification of the program

Compiled files

header.h 

- The header file contains preprocessor directives, function declarations, external variables, and select structures. h Includes declarations of structures and functions necessary for implementing the ato route selection algorithms

ato.c 

- The main file with the main()

start.c

- Reading the file and the main menu

manage.c 

- Database editing menu

add_rec.c 

- Adding data to the database

chg_rec.c 

- Changing data in the database

del_rec.c 

- Deleting data in the database

select.c 

- Route selection menu

select_cost.c 

- Implementation of the Dijkstra algorithm, selection at the lowest cost

select_time.c 

- Implementation of the algorithm for breadth-first search, selection by the shortest waiting time when transferring

select_func.c 

- Contains auxiliary functions for implementing the algorithms for route selection

end.c 

- Writing to a file and freeing memory

## 8. Conclusion

The developed software product implements a simple database, takes into account the restrictions, correctly processes the data, solves the tasks of finding routes between cities, presenting the data in the computer memory as an abstract graph model.
