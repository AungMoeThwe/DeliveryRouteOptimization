#include "pch.h"  // Precompiled header
#include "CppUnitTest.h"

// Include the C headers for your project
extern "C" {
#include "mapping.h"
#include "structures.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTests
{
    // Custom assertion function to compare two Point structs
    void AssertAreEqualPoints(const Point& expected, const Point& actual)
    {
        Assert::AreEqual(expected.row, actual.row, L"Row mismatch");
        Assert::AreEqual(expected.col, actual.col, L"Column mismatch");
    }

    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(Test_SimpleShipmentProcessing)
        {
            // Initialize the map and routes
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            // Create trucks
            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            // Create a shipment
            struct Shipment shipment = { 20.0, 200.0, {6, 3} };

            // Process the shipment
            processPackage(&routeMap, trucks, 3, shipment);

            // Check that the shipment was assigned to the correct truck and the truck's capacity was updated
            Assert::AreEqual(20.0, trucks[0].vol, 0.0001);
            Assert::AreEqual(200.0, trucks[0].weight, 0.0001);

            // Use the custom assertion to compare Points
            Point expectedPosition = { 6, 3 };
            AssertAreEqualPoints(expectedPosition, trucks[0].position);
        }

        TEST_METHOD(Test_MultipleShipmentsProcessing)
        {
            // Initialize the map and routes
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            // Create trucks
            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            // Create multiple shipments
            struct Shipment shipment1 = { 20.0, 200.0, {6, 3} };
            struct Shipment shipment2 = { 30.0, 300.0, {8, 9} };
            struct Shipment shipment3 = { 50.0, 500.0, {9, 1} };

            // Process the shipments
            processPackage(&routeMap, trucks, 3, shipment1);
            processPackage(&routeMap, trucks, 3, shipment2);
            processPackage(&routeMap, trucks, 3, shipment3);

            // Check that each truck's capacity is updated correctly
            Assert::AreEqual(20.0, trucks[0].vol, 0.0001);  // First truck gets shipment1
            Assert::AreEqual(200.0, trucks[0].weight, 0.0001);
            Point expectedPosition1 = { 6, 3 };
            AssertAreEqualPoints(expectedPosition1, trucks[0].position);

            Assert::AreEqual(50.0, trucks[0].vol, 0.0001);  // First truck also gets shipment2
            Assert::AreEqual(500.0, trucks[0].weight, 0.0001);
            Point expectedPosition2 = { 8, 9 };
            AssertAreEqualPoints(expectedPosition2, trucks[0].position);

            Assert::AreEqual(50.0, trucks[1].vol, 0.0001);  // Second truck gets shipment3
            Assert::AreEqual(500.0, trucks[1].weight, 0.0001);
            Point expectedPosition3 = { 9, 1 };
            AssertAreEqualPoints(expectedPosition3, trucks[1].position);
        }

        TEST_METHOD(Test_ShipmentOverflow)
        {
            // Initialize the map and routes
            struct Map baseMap = populateMap();
            struct Route blueRoute = getBlueRoute();
            struct Route greenRoute = getGreenRoute();
            struct Route yellowRoute = getYellowRoute();

            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            // Create trucks
            struct Truck trucks[] = {
                {1, 0.0, 0.0, blueRoute, {0, 0}},
                {2, 0.0, 0.0, greenRoute, {0, 0}},
                {3, 0.0, 0.0, yellowRoute, {0, 0}}
            };

            // Create a shipment that is too large
            struct Shipment shipment = { 100.0, 3000.0, {5, 5} };

            // Process the shipment
            processPackage(&routeMap, trucks, 3, shipment);

            // Check that the shipment is not loaded onto any truck
            Assert::AreEqual(0.0, trucks[0].vol, 0.0001);
            Assert::AreEqual(0.0, trucks[0].weight, 0.0001);
            Assert::AreEqual(0.0, trucks[1].vol, 0.0001);
            Assert::AreEqual(0.0, trucks[1].weight, 0.0001);
            Assert::AreEqual(0.0, trucks[2].vol, 0.0001);
            Assert::AreEqual(0.0, trucks[2].weight, 0.0001);
        }
    };
}
