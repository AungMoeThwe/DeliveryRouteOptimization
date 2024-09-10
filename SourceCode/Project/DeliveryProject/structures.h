#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdio.h>
#include "mapping.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TRUCKS 3
#define MAX_SHIPMENT_WEIGHT 2500
#define MAX_SHIPMENT_VOLUME 100


struct Shipment{
	double vol;
	double weight;
	struct Point target;
};

struct Truck {
	int id;
	double vol;
	double weight;
	struct Route truckRoute;
	struct Point position;

};

struct Capacity {
	double remainingVolume;
	double remainingWeight;
};

// Milestone 3 Functions

// 1.
int findTruckForShipment(struct Map map, struct Truck trucks[], int numTrucks, struct Shipment shipment);
/*
Description: This Function decides the truck thats best suited to place the package, considering the load of the shipment and the route of the truck.
@param: map – The map of the delivery area.
@param: trucks[] – An array of trucks.
@param: numTrucks – The number of trucks.
@param: shipment – The shipment to be delivered.
Return type: Integer representing the index of the best truck. '-1' if no suitable truck
*/

// 2.
int loadShipment(struct Truck* truck, struct Shipment shipment);
/*
Description: Loads the shipment into truck if there is still available capacity
@param: *truck - Pointer to the truct structure
@param: shipment - Shipment to be loaded
Return Type: '0' is successfully loaded '-1' otherwise
*/

//3.
struct Capacity calculateRemainingCapacity(struct Truck truck);
/*
Description: Calculates the remaining of a truck (parallel array) based on the current load max load.
@param: truck - The truck structure to calculate
Return Type: Structure containing the remaining volume and weight
*/

//4.
int isTruckOverload(struct Truck truck);
/*
	Description: Checks if a truck is overloaded based on its current weight and maximum capacity.
	@param: truck The truck to check.
	Return type:  return 1 if the truck is overloaded, 0 otherwise.
*/

//5 
void updatePosition(struct Truck* truck, struct Point newCooridnate);
/*
Description: Function updates the position of the truck after it is delivered
@param: truck - Pointer to the truck structure
@param: newCoordinate - new position of the truck
*/

//6
int validatePackage(int weight, int size);
/**
 * Validates the weight and size of a package.
 *
 * @param weight - The weight of the package in kilograms.
 * @param size - The size of the package in cubic meters.
 * @return - Returns 1 if the package is valid, 0 otherwise.
 */

//7
void processPackage(struct Map* map, struct Truck trucks[], int numTrucks, struct Shipment shipment);
/**
 * Processes a package by finding the best truck, checking capacity,
 * and updating the truck's position and load if the package is valid.
 *
 * @param map - The map of the delivery area.
 * @param trucks - Array of trucks available for delivery.
 * @param numTrucks - The number of trucks.
 * @param shipment - The shipment to be processed.
 */

#ifdef __cplusplus
}
#endif


#endif // STRUCTURES_H






