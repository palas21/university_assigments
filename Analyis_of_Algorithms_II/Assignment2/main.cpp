/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 2
 * Şafak Özkan Pala 
 * 150210016
*/

#include <iostream>   // For input/output
#include <cmath>      // For distance calculations
#include <vector>     // For vector operations
#include <algorithm>  // For sorting operations
#include <limits>     // For min(), max() functions
#include <fstream>    // To read/write files
#include <chrono>     // For time measurement

//(These libraries are sufficient for this assignment.)

using namespace std;

// Structure to represent a point in 2D space
struct Point {
    double x, y;
};

// Helper function to calculate distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)); // Euclidean distance
    // return abs(p1.x - p2.x) + abs(p1.y - p2.y); // Manhattan distance
}

// Helper function to compare points based on x-coordinate, can use this for sorting.
bool compareX(Point p1, Point p2) {
    return p1.x < p2.x;
}

// Helper function to compare points based on y-coordinate, can use this for sorting.
bool compareY(Point p1, Point p2) {
    if(p1.y == p2.y){
        return compareX(p1, p2);
    }
    return p1.y < p2.y;
}

// Function to find the closest pair of points using brute force.
pair<Point, Point> bruteForceClosestPair(vector<Point>& points, int start, int end) {
    double minDistance = numeric_limits<double>::max();

    if (points.empty()){ // If the vector is empyt we return empyt points. This is for segmentation fault.
        return make_pair(Point(), Point()); 
    }

    pair<Point, Point> closestPair = make_pair(points[0], points[1]); // We set an initial pair. I encountered some problems if I don't set the initial value like that.

    for (int i = start; i < end; i++) { // we traverse through the vector and using all combinations try to find the shortest distance
        for (int j = i + 1; j < end; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < minDistance) { // if we find the shortest distance we set it our new minDistance and using these points we make a pair. 
                minDistance = dist;
                closestPair = make_pair(points[i], points[j]);
            }
        }
    }

    return closestPair; 
}

// The main objective of the assignment. This is the function to find the closest pair of points recursively using divide and conquer.
pair<Point, Point> closestPair(vector<Point>& points, int start, int end) {
    
    if (end - start <= 4 ) { // There is no longer a need for us to divide the vector in half due to lack of points.
        return bruteForceClosestPair(points, start, end); // using bruteForceClosestPair we can find the closestpoints and return it.
    }
    
    int mid = (start + end) / 2; // We get the middle point's index of the given indexes. 
    Point middle_point = points[mid]; // We get the middle point using index that we previously found.

    // we recursively call left and right part of the middle point and try to find shortest one among them and find their distance to compare them. 
    pair<Point, Point> left = closestPair(points, start, mid); 
    
    pair<Point, Point> right = closestPair(points, mid, end);

    double min_distance;
    pair<Point, Point> closest;

    // we assign shortest one to min_distance and closest pair.
    if(distance(left.first, left.second) < distance(right.first, right.second)){
        min_distance = distance(left.first, left.second);
        closest = left;
    }
    else{
        min_distance = distance(right.first, right.second);
        closest = right;
    }

    // We have a vector that stores the points the middle point's y value difference is shorter than the min distance. Therefore we can get if there is closest pair using both left and right sides.
    vector<Point> both_side; 
    
    // we find and store these points into the both_side vector.
    for (int i = start; i < end; i++) {
        if (abs(middle_point.y - points[i].y) < min_distance) {
            both_side.push_back(points[i]);
        }
    }

    if(both_side.size() > 2){ // we check if there are more than 2 points in the both_side vector. If there are we can find the closest pair using bruteForceClosestPair function.
        pair<Point, Point> both_side_pair = bruteForceClosestPair(both_side, 0, both_side.size()); // we get the pair that is closest amongs them and compare it with the current min_distance if it is smaller we use this pair.
        if (distance(both_side_pair.first, both_side_pair.second) < min_distance) {
            return both_side_pair;
        }
    }

    // if it is not we use current our pair.
    return closest;
}

// Function to remove a pair of points from the point vector. Returns the newly formed vector.
vector<Point> removePairFromVector(vector<Point>& point_vector, pair<Point,Point> point_pair) {
    vector<Point> new_vector;
    for (size_t i = 0; i < point_vector.size(); i++) {
        if(point_pair.first.x == point_vector[i].x && point_pair.first.y == point_vector[i].y){ // check wheter it is point_pair.first
            continue;
        }
        else if(point_pair.second.x == point_vector[i].x && point_pair.second.y == point_vector[i].y){ // check wheter it is point_pair.second
            continue;
        }
        else{ // if it is neiter first or second we can add this in our new vector.
            new_vector.push_back(point_vector[i]);
        }
    }

    return new_vector;
}

// This function should wrap up the entire algorithm. It should:
//    1- Find the closest pair
//    2- Add the pair to the "pairs" vector
//    3- Remove the paired result from the map
// at each iteration.
// Then it should set "unconnected" variable as the final, unconnected city (if it exists).
void findClosestPairOrder(vector<Point> points) {
    vector<pair<Point,Point>> pairs; // We store the pairs in this vector.
    Point unconnected = {-1,-1}; // This is for unconnected point if there is one

    pair<Point, Point> closest; // construct an initial pair for closest. I set it to points[0] and points[1] due to some problems I've encountered.

    sort(points.begin(), points.end(), compareY); // we sort the points according to their y values because our algorithm uses their y values to find the closest pair.

    // Find the closest pairs until there are no more points left
    while (points.size() > 1) {
        closest = closestPair(points, 0, points.size() ); // we find the closest pair using closestPair function.
        // closest = bruteForceClosestPair(points, 0, points.size()); // we find the closest pair using bruteForceClosestPair function.
        if(!compareY(closest.first, closest.second)){ // we sort the pair in order to their y values.
            swap(closest.first, closest.second);
        }
        pairs.push_back(closest); // we add this pair in our vector
        points = removePairFromVector(points, closest); // and remove this pair's point from the points vector
    }

    // Set the unconnected point if it exists
    if (points.size() == 1) {
        unconnected = points[0];
    }

    for(size_t i = 0; i < pairs.size(); i++){
        cout << "Pair " << i+1 << ": " << pairs[i].first.x << ", " << pairs[i].first.y << " - " << pairs[i].second.x << ", " << pairs[i].second.y << endl;
    }
    if (unconnected.x != -1){
        cout << "Unconnected " << unconnected.x << ", " << unconnected.y;
    }
}

//Read the coordinates from the file and convert them to a vector. Return the vector as a "vector<Point>"
vector<Point> readCoordinatesFromFile(const string& filename) {
    vector<Point> points;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File can not be opened!";
        exit(1);
    }

    Point p;
    while (file >> p.x >> p.y) {
        points.push_back(p);
    }

    file.close();

    return points;
}

// Main function. Ideally, you don't need to modify this.
int main(int argc, char* argv[]) {
    vector<Point> points = readCoordinatesFromFile(argv[1]);
    auto start = chrono::high_resolution_clock::now();
    findClosestPairOrder(points);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    // cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
    return 0;
}