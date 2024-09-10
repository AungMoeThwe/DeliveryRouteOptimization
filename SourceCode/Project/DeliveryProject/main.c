#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "structures.h"

int main(void) {
    // Initialize the map and routes
    struct Map baseMap = populateMap();
    struct Route blueRoute = getBlueRoute();
    struct Route greenRoute = getGreenRoute();
    struct Route yellowRoute = getYellowRoute();

    // Create trucks
    struct Truck trucks[MAX_TRUCKS] = {
        {1, 0, 0, blueRoute, {0, 0}},
        {2, 0, 0, greenRoute, {0, 0}},
        {3, 0, 0, yellowRoute, {0, 0}}
    };

    // Add routes to the map
    struct Map routeMap = addRoute(&baseMap, &blueRoute);
    routeMap = addRoute(&routeMap, &greenRoute);
    routeMap = addRoute(&routeMap, &yellowRoute);

    // Print the initial map
    printf("=================\n");
    printf("Seneca Polytechnic Deliveries\n");
    printf("=================\n");
    printMap(&routeMap, 1, 1);

    // Process packages
    int weight, size;
    char col;
    int row;
    char input[20];
    while (1) {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        if (sscanf(input, "%d %d %d%c", &weight, &size, &row, &col) != 4) {
            if (sscanf(input, "%d %d %c", &weight, &size, &col) == 3 && weight == 0 && size == 0 && col == 'x') {
                break;
            }
            else {
                printf("Invalid input format\n");
                continue;
            }
        }

        struct Point destination = { row - 1, col - 'A' };
        if (destination.row < 0 || destination.row >= MAP_ROWS || destination.col < 0 || destination.col >= MAP_COLS) {
            printf("Invalid destination\n");
            continue;
        }

        struct Shipment shipment = { size, weight, destination };
        processPackage(&routeMap, trucks, MAX_TRUCKS, shipment);
    }

    printf("Thanks for shipping with Seneca Polytechnic!\n");
    return 0;
}
