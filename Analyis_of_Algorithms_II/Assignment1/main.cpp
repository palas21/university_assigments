/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 1
 * Şafak Özkan Pala
 * 150210016
*/

/* * * * * * * * * * * * * * * * * *
 * DO NOT MODIFY UNLESS REQUESTED  *
* * * * * * * * * * * * * * * * * */

#include <iostream>         
#include <vector>
#include <fstream>
#include <sstream>       
#include <stack>
#include <queue>
#include <chrono>       // For time measurement

/* INCLUDE ANY OTHER NECESSARY LIBRARIES HERE */
/* START YOUR CODE HERE */

/* END YOUR CODE HERE */

using namespace std;
using namespace std::chrono;

/* USE HERE IF YOU NEED TO DEFINE EXTRA FUNCTIONS */
/* START YOUR CODE HERE */

/**
 * It orders the top-k elements in the array.
 * 
 * @param arr The array of pairs to be ordered.
 * @param k The number of top elements to be ordered
 * 
 * @return void
*/
void arange_top_k_elements(std::vector<std::pair<int, int>>& arr, size_t k) { // we use selection sort to order the top-k elements. This function runs in O(n * k) time complexity.
    for(size_t i = 0; i < k; i++) { // we choose top k elements.
        int maks = -1; // we initialize the maximum value as -1 to compare the elements since the elements are positive.
        for(size_t j = i; j < arr.size(); j++){ // we iterate over the array.
            if(arr[j].first > maks) { // if the current element is greater than the maximum value we update the maximum value and swap the elements.
                maks = arr[j].first;
                std::swap(arr[i], arr[j]);
            }
            else if(arr[j].first == maks && arr[j].second < arr[i].second) { // if the current element is equal to the maximum value but the resource type is smaller we update the maximum value and swap the elements.
                maks = arr[j].first;
                std::swap(arr[i], arr[j]);
            }
        }
    }
    arr.resize(k < arr.size() ? k : arr.size()); // we resize the array for top-k elements if k is smaller than the size of the array we take k elements otherwise we take all elements.
}

/* END YOUR CODE HERE */

/**
 * Perform Depth-First Search (DFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the DFS traversal.
 * @param col The starting column index for the DFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the DFS traversal.
 */
int dfs(vector<vector<int>>& map, int row, int col, int resource) {
    /* START YOUR CODE HERE */
    std::stack<std::pair<int, int>> stack_; // we use stack for DFS
    stack_.push(std::make_pair(row, col)); // we push the starting point to the stack.
    int size = 0; // we initialize the size of the colony.
    while (!stack_.empty()) {
        size_t c_row = stack_.top().first; // we get the current cell.
        size_t c_col = stack_.top().second; // we get the current cell.
        stack_.pop(); // we pop the current cell make necessary operations.
        if (map[c_row][c_col] != resource) { // if the current cell is not the source we are looking for or visited before, we continue to the next cell.
            continue;
        }
        size++; // we increase the size of the current colony.
        map[c_row][c_col] = -1; // we mark the cell as visited.
        stack_.push(std::make_pair((c_row - 1 + map.size()) % map.size(), c_col)); // we push upper cell to the stack. Since the map is circular we use modulo operation and olso add the size of the map to handle negative values.
        stack_.push(std::make_pair((c_row + 1) % map.size(), c_col)); // we push lower cell to the stack. Since the map is circular we use modulo operation to handle overflow.
        stack_.push(std::make_pair(c_row, (c_col - 1 + map[c_row].size()) % map[c_row].size())); // we push left cell to the stack. Since the map is circular we use modulo operation and olso add the size of the map to handle negative values.
        stack_.push(std::make_pair(c_row, (c_col + 1) % map[c_row].size())); // we push right cell to the stack. Since the map is circular we use modulo operation to handle overflow.
    }

    return size; // we return the size of the colony.
    /* END YOUR CODE HERE */
}


/**
 * Perform Breadth-First Search (BFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the BFS traversal.
 * @param col The starting column index for the BFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the BFS traversal.
 */
int bfs(vector<vector<int>>& map, int row, int col, int resource) {
    
    /* START YOUR CODE HERE */
    std::queue<std::pair<int, int>> queue_; // we use queue for BFS
    queue_.push(std::make_pair(row, col)); // we push the starting point to the queue.
    int size = 0; // we initialize the size of the colony.
    while (!queue_.empty()) {
        size_t c_row = queue_.front().first; // we get the current cell.
        size_t c_col = queue_.front().second; // we get the current cell.
        queue_.pop(); // we pop the current cell make necessary operations.
        if (map[c_row][c_col] != resource) { // if the current cell is not the source we are looking for or visited before, we continue to the next cell.
            continue;
        }
        size++; // we increase the size of the current colony.
        map[c_row][c_col] = -1; // we mark the cell as visited.
        queue_.push(std::make_pair((c_row - 1 + map.size()) % map.size(), c_col)); // we push upper cell to the queue. Since the map is circular we use modulo operation and olso add the size of the map to handle negative values.
        queue_.push(std::make_pair((c_row + 1) % map.size(), c_col)); // we push lower cell to the queue. Since the map is circular we use modulo operation to handle overflow.
        queue_.push(std::make_pair(c_row, (c_col - 1 + map[c_row].size()) % map[c_row].size())); // we push left cell to the queue. Since the map is circular we use modulo operation and olso add the size of the map to handle negative values.
        queue_.push(std::make_pair(c_row, (c_col + 1) % map[c_row].size())); // we push right cell to the queue. Since the map is circular we use modulo operation to handle overflow.
    }

    return size; // we return the size of the colony.
}

/**
 * Finds the top-k largest colonies in a given map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param useDFS A boolean flag indicating whether to use Depth-First Search (DFS) or Breadth-First Search (BFS) algorithm.
 * @param k The number of top colonies to find.
 * @return A vector of pairs representing the size and resource type of the top-k largest colonies.
 */
vector<pair<int, int>> top_k_largest_colonies(vector<vector<int>>& map, bool useDFS, unsigned int k) {

    auto start = high_resolution_clock::now();      // Start measuring time
    
    /* START YOUR CODE HERE */
    std::vector<std::pair<int, int>> result; // we use vector of pairs to store the size and resource type of the colonies.

    if(useDFS){ // if the algorithm is DFS
        for(size_t i = 0; i < map.size(); i++) { // we iterate over the map.
            for(size_t j = 0; j < map[i].size(); j++) { // we iterate over the map.
                if(map[i][j] == -1) { // if the cell is visited before we continue to the next cell.
                    continue;
                }
                int resource = map[i][j]; // we get the resource type of the colony since it becomes -1 after the first visit we store it in a variable.
                int size = dfs(map, i, j, map[i][j]); // we get the size of the colony using DFS.                
                result.push_back(std::make_pair(size, resource)); // we push the size and resource type of the colony to the result vector.
            }
        }
    }
    else { // if the algorithm is BFS
        for(size_t i = 0; i < map.size(); i++) { // we iterate over the map.
            for(size_t j = 0; j < map[i].size(); j++) { // we iterate over the map.
                if(map[i][j] == -1) { // if the cell is visited before we continue to the next cell.
                    continue;
                }
                int resource = map[i][j]; // we get the resource type of the colony since it becomes -1 after the first visit we store it in a variable.
                int size = bfs(map, i, j, map[i][j]); // we get the size of the colony using BFS.
                result.push_back(std::make_pair(size, resource)); // we push the size and resource type of the colony to the result vector.
            }
        }
    }
    /* END YOUR CODE HERE */

    auto stop = high_resolution_clock::now();                       // Stop measuring time
    auto duration = duration_cast<nanoseconds>(stop - start);       // Calculate the duration
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

    /* START YOUR CODE HERE */
    
    // sort without using build-in functions
    
    arange_top_k_elements(result, k); // we order the top-k elements in the result vector.

    return result; // we return the result vector.
    /* END YOUR CODE HERE */
}

// Main function
int main(int argc, char* argv[]) {

    // Check the command line arguments
    if (argc != 4) {

        // It should be: <1 or 0> <k> <filename.txt>
        cerr << "Usage: " << argv[0] << " <1 or 0> <k> <filename.txt>" << endl;
        return 1;
    }

    // Get the arguments
    bool useDFS = (atoi(argv[1]) == 1);
    int k = atoi(argv[2]);

    // Read the map from the text file
    string filename = argv[3];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<vector<int>> sector_map;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;
        while (iss >> num) {
            row.push_back(num);
        }
        sector_map.push_back(row);
    }
    file.close();   

    // Find the largest colony
    vector<pair<int, int>> result = top_k_largest_colonies(sector_map, useDFS, k);

    // Print the result
    cout << "Algorithm: " << (useDFS ? "DFS" : "BFS") << endl;
    cout << "Map: " << filename << endl;

    // If no colonies are found
    if (result.empty()) {
        cout << "No colonies found." << endl;
        return 0;
    }

    // Print the top-k colonies
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "Colony " << i + 1 << ": Size = " << result[i].first << ", Resource Type = " << result[i].second << endl;
    }

    return 0;
}