/*
BLG 335E Analysis of Algorithms I - Fall 2023 - Project 1

@Author
Şafak Özkan Pala
150210016

To compile: g++ -std=c++20 -Wall -Werror QuickSort.cpp -o QuickSort
To run: ./QuickSort <input_file_name> <pivot_strategy> <threshold> <output_file_name> <verbose_mode>
*/

#include <iostream>
#include <fstream>
#include <sstream>  
#include <vector>
#include <string>
#include <utility>
#include <chrono>
#include <ctime>

unsigned long long int counter = 0; // this is for counting the number of comparisons

void takeDataFromGivenCsvFile(std::vector<std::pair<std::string, int>>&, const std::string&);
int partition(std::vector<std::pair<std::string,int>>&, int, int,char);
void quickSort(std::vector<std::pair<std::string,int>>&, int, int, char,int,char);
void insertionSort(std::vector<std::pair<std::string,int>>&, int, int);
void logger(std::vector<std::pair<std::string,int>>&,int,int);

int main(int argc, char** argv) {

    srand(time(NULL)); // this is for randomness

    std::string filename = argv[1];
    filename = "Data/" + filename;
    char mode = argv[2][0];
    int k = std::stoi(argv[3]);
    std::string outputFilename = argv[4];
    char v = '0';
    if(argc == 6){ 
        v = argv[5][0];
        if(v == 'v'){ // if verbose mode is on we clear the log file
            std::ofstream logFile("log.txt");
            logFile.close();
        }
    }

    std::vector<std::pair<std::string, int>> Population; // vector of pairs (city name, population). I don't want to use structs.
    takeDataFromGivenCsvFile(Population, filename);

    // take start time
    auto start = std::chrono::high_resolution_clock::now();

    quickSort(Population, 0, Population.size()-1, mode,k,v); // this is our main function
    
    // take end time
    auto end = std::chrono::high_resolution_clock::now();
    // calculate the time passed
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout  << "Time taken by QuickSort with pivot strategy '" << mode << "' and threshold " << k << ": " << elapsed.count() << " ns." << std::endl;


    // we write the sorted data to the output file
    std::ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        std::cout << "Failed to open file: " << outputFilename << std::endl;
        return 0;
    }

    for (unsigned int i = 0; i < Population.size(); i++) {
        std::string name = Population[i].first;
        int population = Population[i].second;
        outputFile << name << ";" << population << std::endl;
    }

    
    outputFile.close();
    std::cout << "Number of comparisons: " << counter << std::endl;
    return 0;
}

void takeDataFromGivenCsvFile(std::vector<std::pair<std::string, int>>& data, const std::string& filename) { // this function takes data from csv file and push it into the vector of pairs.
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ';')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 2) {
            std::cout << "Invalid data format in file: " << filename << std::endl;
            continue;
        }

        std::string name = tokens[0];
        int population = std::stoi(tokens[1]);

        data.push_back(std::make_pair(name, population));
    }

    file.close();
}

int partition(std::vector<std::pair<std::string,int>>& arr, int p, int r,char v){ // this is the partition function of quicksort
    if(v == 'v'){ // if verbose mode is on, we record pivot and subarray
        logger(arr,p,r);
    }
    int x = arr[r].second;
    int i = p-1;
    for(int j = p; j < r; j++){
        counter++; // we increase the counter for each comparison
        if(arr[j].second <= x){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[r]);
    return i+1;
}

void quickSort(std::vector<std::pair<std::string,int>>& arr, int p, int r, char mode, int k, char v){ // this is the main part of our quicksort algorithm
    if(r - p <= k && k != 1){ // if k is one or our subarray length is more than k, we dont use insertion sort
        insertionSort(arr, p, r);
        return;
    }
    else{
        if(p < r){ // in this section we choose different pivots according to the mode
            int q;
            if(mode == 'l'){ // if mode is 'l' we use classic quicksort
                q = partition(arr, p, r,v);
            }
            else if(mode == 'r'){ // if mode is 'r' we use quicksort with random pivot
                int random = rand() % (r-p+1) + p;
                std::swap(arr[random], arr[r]);
                q = partition(arr, p, r,v);
            }
            else if(mode == 'm'){// Iif mode is 'm' we use quicksort with median of three random elements as pivot
                int random1 = rand() % (r-p+1) + p;
                int random2 = rand() % (r-p+1) + p;
                int random3 = rand() % (r-p+1) + p;
                
                int median;

                if( (arr[random1].second <= arr[random2].second && arr[random1].second >= arr[random3].second) || (arr[random1].second >= arr[random2].second && arr[random1].second <= arr[random3].second) )
                    median = arr[random1].second;
                else if( (arr[random2].second <= arr[random1].second && arr[random2].second >= arr[random3].second) || (arr[random2].second >= arr[random1].second && arr[random2].second <= arr[random3].second) )
                    median = arr[random2].second;
                else
                    median = arr[random3].second;

                if(median == arr[random1].second)
                    std::swap(arr[random1], arr[r]);
                else if(median == arr[random2].second)
                    std::swap(arr[random2], arr[r]);
                else
                    std::swap(arr[random3], arr[r]);
                q = partition(arr, p, r,v);
            }
            else{ // if different mode is given we print error message and return
                std::cout << "Invalid mode" << std::endl;
                return;
            }
                quickSort(arr, p, q-1,mode,k,v);
                quickSort(arr, q+1, r,mode,k,v);
        }
    }    
}

void insertionSort(std::vector<std::pair<std::string,int>>& arr, int p, int r){ // this is classic insertion sort
    for(int i = p+1; i <= r; i++){
        std::pair<std::string,int> key = arr[i];
        int j = i-1;
        while(j >= p && arr[j].second > key.second){
            std::swap(arr[j+1], arr[j]);
            j--;
        }
        arr[j+1] = key;
    }
}

void logger(std::vector<std::pair<std::string,int>>& arr, int left, int right){ // this is logger function for verbose mode
    
    std::fstream logFile;
    logFile.open("log.txt", std::fstream::app);
    if (logFile.is_open()) {
        logFile << "Pivot: " << arr[right].second << "  Array: [";
        for(int i = left; i < right+1; i++){
            logFile << arr[i].second << ", ";
        }
        logFile << " ] " << std::endl;
        logFile.close();
    }
}