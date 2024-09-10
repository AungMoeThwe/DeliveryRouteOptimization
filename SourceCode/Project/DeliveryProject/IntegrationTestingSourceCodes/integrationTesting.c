#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "structures.h"

// Have to integrate this into main.c by giving an instruction to run all tests 

// Dummy function to initialize a truck
void initializeTruck(struct Truck* truck, int id, double vol, double weight, struct Route route, struct Point position) {
    truck->id = id;
    truck->vol = vol;
    truck->weight = weight;
    truck->truckRoute = route;
    truck->position = position;
}

// Function to simulate a delivery
void simulateDelivery(double weight, double vol, char* target, struct Map* map, struct Truck trucks[], int numTrucks) {
    struct Shipment shipment;
    shipment.weight = weight;
    shipment.vol = vol;

    // Assuming target is in format "rowColumn" (e.g., "12L")
    int row;
    char col;
    sscanf(target, "%d%c", &row, &col);
    shipment.target.row = row;
    shipment.target.col = col - 'A';  // Convert letter to column index

    processPackage(map, trucks, numTrucks, shipment);
}

int main() {
    printf("=================\n");
    printf("Seneca Polytechnic Deliveries\n");
    printf("=================\n");

    struct Map map = populateMap(); // Use populateMap to initialize the map

    struct Truck trucks[3];
    initializeTruck(&trucks[0], 0, 100, 2500, getBlueRoute(), (struct Point) { 0, 0 });
    initializeTruck(&trucks[1], 1, 100, 2500, getGreenRoute(), (struct Point) { 0, 0 });
    initializeTruck(&trucks[2], 2, 100, 2500, getYellowRoute(), (struct Point) { 0, 0 });

    // Test Case 1: Valid Input, No Diversion
    printf("Test Case 1: ");
    simulateDelivery(20, 5, "12L", &map, trucks, 3);

    // Test Case 2: Valid Input, Minimal Diversion
    printf("Test Case 2: ");
    simulateDelivery(1000, 1, "8Y", &map, trucks, 3);

    // Test Case 3: Valid Input, Significant Diversion
    printf("Test Case 3: ");
    simulateDelivery(1000, 1, "8Y", &map, trucks, 3);

    // Test Case 4: Invalid Destination
    printf("Test Case 4: ");
    simulateDelivery(20, 5, "28X", &map, trucks, 3);

    // Test Case 5: Invalid Box Size
    printf("Test Case 5: ");
    simulateDelivery(20, 4, "12L", &map, trucks, 3);

    // Test Case 6: Invalid Weight
    printf("Test Case 6: ");
    simulateDelivery(2600, 5, "12L", &map, trucks, 3);

    // Test Case 7: Multiple Packages Filling Truck
    printf("Test Case 7: ");
    simulateDelivery(1500, 50, "12L", &map, trucks, 3);
    simulateDelivery(1000, 60, "12L", &map, trucks, 3);

    // Test Case 8: Equal Distance Trucks
    printf("Test Case 8: ");
    simulateDelivery(500, 3, "7F", &map, trucks, 3);

    // Test Case 9: Multiple Deliveries with Weight Constraints
    printf("Test Case 9: ");
    simulateDelivery(1200, 20, "5B", &map, trucks, 3);
    simulateDelivery(1300, 30, "9H", &map, trucks, 3);

    // Test Case 10: Truck Route Optimization
    printf("Test Case 10: ");
    simulateDelivery(500, 10, "6C", &map, trucks, 3);
    simulateDelivery(700, 15, "3D", &map, trucks, 3);
    simulateDelivery(800, 25, "2E", &map, trucks, 3);

    printf("Thanks for shipping with Seneca Polytechnic!\n");
    return 0;
}
