// UnitTest1.cpp
#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "mapping.h"
#include "structures.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(Distance)
    {
    public:

        TEST_METHOD(Test_distance_SamePoints)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 0, 0 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(0.0, result);
        }

        TEST_METHOD(Test_distance_AdjacentPoints)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 1, 1 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(1.41421356237, result, 0.0001); 
        }

        TEST_METHOD(Test_distance_DistantPoints)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 3, 4 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result, 0.0001);
        }

        TEST_METHOD(Test_distance_SameRow)
        {
            struct Point p1 = { 2, 2 };
            struct Point p2 = { 2, 5 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(3.0, result, 0.0001);
        }

        TEST_METHOD(Test_distance_SameColumn)
        {
            struct Point p1 = { 2, 2 };
            struct Point p2 = { 5, 2 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(3.0, result, 0.0001);
        }
        TEST_METHOD(Distance_between_two_identical_points)
        {
            
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 0, 0 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(0.0, result);  
        }

        TEST_METHOD(Distance_between_points_on_the_same_row)
        {
          
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 0, 3 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(3.0, result);  
        }

        TEST_METHOD(Distance_between_points_on_the_same_column)
        {
       
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 4, 0 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(4.0, result); 
        }

        TEST_METHOD(Distance_between_points_on_different_rows_and_columns)
        {
           
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 3, 4 };
            double result = distance(&p1, &p2);
            Assert::AreEqual(5.0, result); 
        }

    };

    TEST_CLASS(FindTruckForShipment)
    {
    public:

        TEST_METHOD(Test_NoSuitableTruck)
        {
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            int numTrucks = 3;
            struct Shipment shipment = { 30.0, 3000.0, {5, 5} };
            int result = findTruckForShipment(routeMap, trucks, numTrucks, shipment);
            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(Test_BestTruck_FirstBasedOnDistanceAndCapacity)
        {
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            int numTrucks = 3;
            struct Shipment shipment = { 10.0, 500.0, {5, 5} };
            int result = findTruckForShipment(routeMap, trucks, numTrucks, shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_BestTruck_SecondBasedOnDistance)
        {
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            int numTrucks = 3;
            struct Shipment shipment = { 8.0, 700.0, {5, 3} };
            int result = findTruckForShipment(routeMap, trucks, numTrucks, shipment);
            Assert::AreEqual(0, result);
           
        }
        

        TEST_METHOD(Test_BestTruck_ThirdBasedOnDistance)
        {
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            int numTrucks = 3;
            struct Shipment shipment = { 6.0, 650.0, {6, 3} };
            int result = findTruckForShipment(routeMap, trucks, numTrucks, shipment);
            Assert::AreEqual(0, result);

        }

        TEST_METHOD(Test_AllTrucksEquallyGood_FirstOneChosen)
        {
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            int numTrucks = 3;
            struct Shipment shipment = { 10.0, 100.0, {5, 5} };
            int result = findTruckForShipment(routeMap, trucks, numTrucks, shipment);
            Assert::AreEqual(0, result);
        }
    };

    TEST_CLASS(LoadShipment)
    {
    public:

        TEST_METHOD(Test_ShipmentFitsIntoTruck)
        {
            struct Truck truck = { 1, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 10.0, 500.0, {5, 5} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_ShipmentDoesNotFitDueToWeight)
        {
            struct Truck truck = { 1, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 10.0, 2000.0, {5, 5} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(Test_ShipmentDoesNotFitDueToVolume)
        {
            struct Truck truck = { 1, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 100.0, 200.0, {5, 5} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(Test_ShipmentFitsExactly)
        {
            struct Truck truck = { 1, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 50.0, 1500.0, {5, 5} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_ShipmentFitsWithSpaceLeft)
        {
            struct Truck truck = { 1, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 20.0, 400.0, {5, 5} };
            int result = loadShipment(&truck, shipment) ;
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(Test_NormalLoadingWithinCapacity)
        {
            struct Truck truck = { 1, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 30.0, 500.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result);

            Assert::AreEqual(80.0, truck.vol);
            Assert::AreEqual(600.0, truck.weight);;
        }

        TEST_METHOD(Test_LoadingExactlyToFullCapacity)
        {
            struct Truck truck = { 2, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 50.0, 100.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result); 

            Assert::AreEqual(100.0, truck.vol);
            Assert::AreEqual(200.0, truck.weight);
        }

        TEST_METHOD(Test_AttemptingToLoadOverCapacity)
        {
            struct Truck truck = { 3, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 60.0, 120.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(-1, result); 

            Assert::AreEqual(50.0, truck.vol);
            Assert::AreEqual(100.0, truck.weight);
        }

        TEST_METHOD(Test_MinimumBoundaryCase)
        {
            struct Truck truck = { 4, 0.0, 0.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 0.0, 0.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result); 

            Assert::AreEqual(0.0, truck.vol);
            Assert::AreEqual(0.0, truck.weight);
        }
    };
    TEST_CLASS(CalculateRemainingCapacity)
    {
    public:

        TEST_METHOD(Test_EmptyTruck)
        {
            struct Truck truck = { 0, 0.0, 0.0, getBlueRoute(), {0, 0} };
            struct Capacity capacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(100.0, capacity.remainingVolume);
            Assert::AreEqual(2500.0, capacity.remainingWeight);
        }

        TEST_METHOD(Test_PartiallyFilledTruck)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Capacity capacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(50.0, capacity.remainingVolume);
            Assert::AreEqual(1500.0, capacity.remainingWeight);
        }

        TEST_METHOD(Test_AlmostFullByWeight)
        {
            struct Truck truck = { 0, 90.0, 2400.0, getBlueRoute(), {0, 0} };
            struct Capacity capacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(10.0, capacity.remainingVolume);
            Assert::AreEqual(100.0, capacity.remainingWeight);
        }

        TEST_METHOD(Test_FullByWeight)
        {
            struct Truck truck = { 0, 50.0, 2500.0, getBlueRoute(), {0, 0} };
            struct Capacity capacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(50.0, capacity.remainingVolume);
            Assert::AreEqual(0.0, capacity.remainingWeight);
        }

        TEST_METHOD(Test_FullByVolume)
        {
            struct Truck truck = { 0, 100.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Capacity capacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(0.0, capacity.remainingVolume);
            Assert::AreEqual(1500.0, capacity.remainingWeight);
        }
        TEST_METHOD(Test_MinimumValues)
        {
            struct Truck truck = { 1, 0, 0, getBlueRoute(), {0, 0} };
            struct Capacity remainingCapacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(100.0, remainingCapacity.remainingVolume);
            Assert::AreEqual(2500.0, remainingCapacity.remainingWeight);
        }

        TEST_METHOD(Test_HalfLoadValues)
        {
            struct Truck truck = { 2, 50, 1250, getBlueRoute(), {0, 0} };
            struct Capacity remainingCapacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(50.0, remainingCapacity.remainingVolume);
            Assert::AreEqual(1250.0, remainingCapacity.remainingWeight);
        }

        TEST_METHOD(Test_FullLoadValues)
        {
            struct Truck truck = { 3, 100, 2500, getBlueRoute(), {0, 0} };
            struct Capacity remainingCapacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(0.0, remainingCapacity.remainingVolume);
            Assert::AreEqual(0.0, remainingCapacity.remainingWeight);
        }

        TEST_METHOD(Test_OverloadValues)
        {
            struct Truck truck = { 4, 110, 2600, getBlueRoute(), {0, 0} };
            struct Capacity remainingCapacity = calculateRemainingCapacity(truck);
            Assert::AreEqual(-10.0, remainingCapacity.remainingVolume);
            Assert::AreEqual(-100.0, remainingCapacity.remainingWeight);
        }
    };

    TEST_CLASS(IsTruckOverload)
    {
    public:

        TEST_METHOD(Test_EmptyTruck)
        {
            struct Truck truck = { 0, 0.0, 0.0, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_PartiallyFilledTruck)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_AlmostOverloadedByWeight)
        {
            struct Truck truck = { 0, 90.0, 2400.0, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_OverloadedByWeight)
        {
            struct Truck truck = { 0, 50.0, 2600.0, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Test_OverloadedByVolume)
        {
            struct Truck truck = { 0, 110.0, 1000.0, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck);
            Assert::AreEqual(1, result);
        }
        TEST_METHOD(Test_TruckAtMaxCapacity)
        {
            struct Truck truck1 = { 1, 50, 2500, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck1);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_TruckOverMaxCapacity)
        {
            struct Truck truck2 = { 2, 60, 2600, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck2);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Test_TruckJustUnderMaxCapacity)
        {
            struct Truck truck3 = { 3, 70, 2499.99, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck3);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Test_TruckWithDifferentVolumeSameWeight)
        {
            struct Truck truck4 = { 4, 80, 2500, getBlueRoute(), {0, 0} };
            int result = isTruckOverload(truck4);
            Assert::AreEqual(0, result);
        }
    };
    TEST_CLASS(UpdatePosition)
    {
    public:

        TEST_METHOD(Test_UpdateToNewPoint)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Point newCoordinate = { 5, 5 };
            updatePosition(&truck, newCoordinate);
            Assert::AreEqual(newCoordinate.row, truck.position.row);
            Assert::AreEqual(newCoordinate.col, truck.position.col);
        }

        TEST_METHOD(Test_UpdateToSamePoint)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Point newCoordinate = { 0, 0 };
            updatePosition(&truck, newCoordinate);
            Assert::AreEqual(newCoordinate.row, truck.position.row);
            Assert::AreEqual(newCoordinate.col, truck.position.col);
        }

        TEST_METHOD(Test_UpdateToAdjacentPoint)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Point newCoordinate = { 1, 1 };
            updatePosition(&truck, newCoordinate);
            Assert::AreEqual(newCoordinate.row, truck.position.row);
            Assert::AreEqual(newCoordinate.col, truck.position.col);
        }

        TEST_METHOD(Test_UpdateToFarPoint)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Point newCoordinate = { 10, 10 };
            updatePosition(&truck, newCoordinate);
            Assert::AreEqual(newCoordinate.row, truck.position.row);
            Assert::AreEqual(newCoordinate.col, truck.position.col);
        }

        TEST_METHOD(Test_UpdateToMaximumPoint)
        {
            struct Truck truck = { 0, 50.0, 1000.0, getBlueRoute(), {0, 0} };
            struct Point newCoordinate = { 24, 24 };
            updatePosition(&truck, newCoordinate);
            Assert::AreEqual(newCoordinate.row, truck.position.row);
            Assert::AreEqual(newCoordinate.col, truck.position.col);
        }
        //
        TEST_METHOD(Test_NormalLoadingWithinCapacity) //NEED TO FIX THIs
        {
           /* struct Truck truck = {1, 50.0, 100.0, getBlueRoute(), {0, 0}};
            struct Shipment shipment = {50.0,100.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result);


            Assert::AreEqual(100.0, truck.vol);
            Assert::AreEqual(300.0, truck.weight);*/
            struct Truck truck = { 1, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 50.0, 100.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result);


            Assert::AreEqual(100.0, truck.vol);
            Assert::AreEqual(200.0, truck.weight);

        }

        TEST_METHOD(Test_LoadingExactlyToFullCapacity)
        {

            struct Truck truck = { 2, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 50.0, 100.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result); 


            Assert::AreEqual(100.0, truck.vol);
            Assert::AreEqual(200.0, truck.weight);
        }

        TEST_METHOD(Test_AttemptingToLoadOverCapacity)
        {

            struct Truck truck = { 3, 50.0, 100.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 60.0, 120.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(-1, result); 


            Assert::AreEqual(50.0, truck.vol);
            Assert::AreEqual(100.0, truck.weight);
        }

        TEST_METHOD(Test_MinimumBoundaryCase)
        {

            struct Truck truck = { 4, 0.0, 0.0, getBlueRoute(), {0, 0} };
            struct Shipment shipment = { 0.0, 0.0, {1, 1} };
            int result = loadShipment(&truck, shipment);
            Assert::AreEqual(0, result); 


            Assert::AreEqual(0.0, truck.vol);
            Assert::AreEqual(0.0, truck.weight);
        }
    };
    
}