#include "structures.h"
#include "mapping.h"
#include <math.h>

int findTruckForShipment(struct Map map, struct Truck trucks[], int numTrucks, struct Shipment shipment) {
    int bestTruckIndex = -1;
    double minDistance = INFINITY;

    for (int i = 0; i < numTrucks; i++) {
        struct Truck* truck = &trucks[i];
        struct Capacity remainingCapacity = calculateRemainingCapacity(*truck);

        if (shipment.vol <= remainingCapacity.remainingVolume && shipment.weight <= remainingCapacity.remainingWeight) {
            // Calculate the shortest path from the truck's current position to the shipment target
            struct Route diversionRoute = shortestPath(&map, truck->position, shipment.target);
            if (diversionRoute.numPoints > 0) {
                // Calculate the distance along the diversion route
                double dist = distance(&truck->position, &diversionRoute.points[diversionRoute.numPoints - 1]);

                // Check if this truck is a better choice
                if (dist < minDistance) {
                    minDistance = dist;
                    bestTruckIndex = i;
                }
            }
        }
    }

    return bestTruckIndex;
}

int loadShipment(struct Truck* truck, struct Shipment shipment) {
    struct Capacity remainingCapacity = calculateRemainingCapacity(*truck);

    if (shipment.vol <= remainingCapacity.remainingVolume && shipment.weight <= remainingCapacity.remainingWeight) {
        truck->vol += shipment.vol;
        truck->weight += shipment.weight;
        truck->position = shipment.target;
        return 0;
    }
    return -1;
}

struct Capacity calculateRemainingCapacity(struct Truck truck) {
    struct Capacity cap;
    cap.remainingVolume = MAX_SHIPMENT_VOLUME - truck.vol;
    cap.remainingWeight = MAX_SHIPMENT_WEIGHT - truck.weight;
    return cap;
}

int isTruckOverload(struct Truck truck) {
    struct Capacity remainingCapacity = calculateRemainingCapacity(truck);
    return (remainingCapacity.remainingVolume < 0 || remainingCapacity.remainingWeight < 0) ? 1 : 0;
}

void updatePosition(struct Truck* truck, struct Point newCoordinate) {
    truck->position = newCoordinate;
    printf("Truck %d updated its position to (%d, %d)\n", truck->id, truck->position.row + 1, truck->position.col + 'A');
}

int validatePackage(int weight, int size) {
    if (weight <= 0 || weight > 2500) {
        printf("Invalid weight (must be 1-2500 Kg.)\n");
        return 0;
    }
    if (size != 1 && size != 3 && size != 5) {
        printf("Invalid size\n");
        return 0;
    }
    return 1;
}

void processPackage(struct Map* map, struct Truck trucks[], int numTrucks, struct Shipment shipment) {
    if (!validatePackage(shipment.weight, shipment.vol)) return;

    int bestTruckIndex = findTruckForShipment(*map, trucks, numTrucks, shipment);
    if (bestTruckIndex == -1) {
        printf("No suitable truck found. Ships tomorrow\n");
        return;
    }

    struct Truck* truck = &trucks[bestTruckIndex];
    struct Route diversionRoute = shortestPath(map, truck->position, shipment.target);
    if (diversionRoute.numPoints == 0) {
        printf("No valid path found to the destination. Ships tomorrow\n");
        return;
    }

    if (loadShipment(truck, shipment) == 0) {
        printf("Ship on %s LINE", (truck->truckRoute.routeSymbol == BLUE) ? "BLUE" : (truck->truckRoute.routeSymbol == GREEN) ? "GREEN" : "YELLOW");
        if (diversionRoute.numPoints > 1) {
            printf(", divert: ");
            for (int i = 1; i < diversionRoute.numPoints; i++) {
                printf("%d%c", diversionRoute.points[i].row + 1, 'A' + diversionRoute.points[i].col);
                if (i < diversionRoute.numPoints - 1) printf(", ");
            }
        }
        printf("\n");
    }
    else {
        printf("Truck cannot accommodate the package. Ships tomorrow\n");
    }
}
