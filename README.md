# Project: Delivery Route Optimization
Professor: Kaveh Eshraghian<br/>
Section: SFT221 ZBB<br/>
Group Assigned: summer24-sft221-zbb-b<br/>
Group: B

Members:
1. Aung Moe Thwe (148396237) amthwe@myseneca.ca
2. Kashish Verma (151579232) kverma45@myseneca.ca
3. Thiri Aung (160234233) taung2@myseneca.ca
4. Jhonatan Lopez (147028237) jlopez-olguin@myseneca.ca

## Learning Outcomes
- Design and build a solution to a small problem.
- Design testing for the problem.

## Project Description
A local delivery company needs a program to optimize the delivery routes for three trucks on a 25x25 city grid. The trucks start at a common point and diverge onto their respective paths (blue, yellow, and green). Buildings (black rectangles) are delivery points, and trucks must navigate around them to deliver packages.

## Truck and Package Specifications
- **Truck Capacity:** 2500 kg or 100 cubic meters
- **Box Sizes:** 1, 3, and 5 cubic meters
- **Customer Specifications:** Weight, box size, destination (row and column)

## Delivery Constraints
- Assign packages to trucks that are closest to the destination.
- Trucks can divert from their paths but cannot go through buildings.
- If distances are equal, choose the truck with more available capacity (based on limiting factor: weight or volume).

## Distance Calculation
- Use Euclidean distance to determine proximity.
- For complex routes, apply the A* algorithm to find the shortest path avoiding buildings.

## A* Algorithm Steps
1. Measure Euclidean distance from the current position to the destination.
2. Move to the nearest square not occupied by a building.
3. Repeat until reaching the destination.
4. If stuck, mark the route as non-eligible.

## Overall Algorithm
1. Follow each truck's route.
2. Calculate Euclidean distances to the destination from each route point.
3. Select the truck with the shortest path to the destination.
4. If the truck is full, try the next closest truck.
5. If no truck can carry the package, mark it as "Ships tomorrow."

## Program Responsibilities
- Determine the truck for each package.
- Print the delivery path and any necessary diversions.
- Run until trucks are full or no more packages arrive.
