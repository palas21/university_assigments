/*
    @Author
    Name: Şafak Özkan Pala
    ID: 150210016
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

unsigned long long int comparisons = 0; // number of comparisons


/*
    This struct is used to store the data of a city
    name: name of the city
    population: population of the city
*/
struct City{
    std::string name;
    int population;
};

// custom functions
void takeDataFromCsvFile(std::vector<City>&, std::string);
void customSwap(City&, City&);
void printCities(std::vector<City>);
void writeToAFile(std::vector<City>, std::string);

// heap functions
void max_heapify(std::vector<City>&, int, int);
void build_max_heap(std::vector<City>&, int);
void heapsort(std::vector<City>&, int);

// priority queue functions
void max_heap_insert(std::vector<City>&, City, int);
City heap_extract_max(std::vector<City>&, int);
void heap_increase_key(std::vector<City>&, int, int, int);
City heap_maximum(std::vector<City>&, int);

// dary heap functions
void dary_max_heapify(std::vector<City>&, int, int, int);
void dary_build_max_heap(std::vector<City>&, int, int);
int dary_calculate_height(std::vector<City>&, int);
City dary_extract_max(std::vector<City>&, int, int);
void dary_insert_element(std::vector<City>&, City, int, int);
void dary_increase_key(std::vector<City>&, int, int, int, int);
void dary_heapsort(std::vector<City>&, int, int);

int main(int argc, char* argv[]){


    std::string fileName = "Data/";
    fileName += argv[1];

    std::string functionType = argv[2];

    std::string outputFileName = argv[3];

    std::string d_string, i_string, k_string;

    int d,i,key_number;
    City key_city;

    std::cout << "Şu an buradayız.";

    for(int j = 4; j < argc; j++){
        if(argv[j][0] == 'd'){
            d_string = argv[j];
            d = std::stoi(d_string.substr(1, d_string.length()));
        }
        else if(argv[j][0] == 'i'){
            i_string = argv[j];
            i = std::stoi(i_string.substr(1, i_string.length()));
            i--; // converting index to array index
        }
        else if(argv[j][0] == 'k'){
            
            k_string = argv[j];

            if(functionType == "dary_increase_key" || functionType == "heap_increase_key"){
                
                k_string.erase(0,1);

                key_number = std::stoi(k_string);
            }
            else{
                int index0 = 0;
                int index1 = 0;
                int index = 0;
                while(index < k_string.size() && k_string[i] != '_'){
                    index0++;
                    index1++;
                    index++;
                }
                index++;
                while(index < k_string.size() && k_string[i] != '_'){
                    index1++;
                    index++;
                }
                key_city.name = k_string.substr(index0 + 1,index1 - 1);
                key_city.population = std::stoi(k_string.substr(index1 + 2, k_string.size() - 1));                    
            }     
        }
    }

    std::vector<City> cities;
    takeDataFromCsvFile(cities, fileName);
    
    if(functionType == "max_heapify"){
        max_heapify(cities, i, cities.size());
    }
    else if(functionType == "build_max_heap"){
        build_max_heap(cities, cities.size());
    }
    else if(functionType == "heapsort"){
        //starting time
        auto start = std::chrono::high_resolution_clock::now();
        heapsort(cities, cities.size());
        //ending time
        auto end = std::chrono::high_resolution_clock::now();
        // print time taken
        std::cout << "Time taken by heapsort: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds" << std::endl;
    }
    else if(functionType == "max_heap_insert"){
        build_max_heap(cities, cities.size());
        max_heap_insert(cities,  key_city, cities.size());
    }
    else if(functionType == "heap_extract_max"){
        build_max_heap(cities, cities.size());
        City max = heap_extract_max(cities, cities.size());
        std::cout << max.name << " " << max.population << std::endl;
    }
    else if(functionType == "heap_increase_key"){
        build_max_heap(cities, cities.size());
        heap_increase_key(cities, i, key_number, cities.size());
    }
    else if(functionType == "heap_maximum"){
        build_max_heap(cities, cities.size());
        City max = heap_maximum(cities, cities.size());
        std::cout << max.name << " " << max.population << std::endl;
    }
    else if(functionType == "dary_calculate_height"){
        std::cout << dary_calculate_height(cities, d) << std::endl;
    }
    else if(functionType == "dary_extract_max"){
        dary_build_max_heap(cities, cities.size(), d);
        City max = dary_extract_max(cities, cities.size(), d);
        std::cout << max.name << " " << max.population << std::endl;
    }
    else if(functionType == "dary_insert_element"){
        dary_build_max_heap(cities, cities.size(), d);
        City city;
        city.name = argv[4];
        city.population = std::stoi(argv[5]);
        dary_insert_element(cities, city, cities.size(), d);
    }
    else if(functionType == "dary_increase_key"){
        dary_build_max_heap(cities, cities.size(), d);
        dary_increase_key(cities, i, key_number, cities.size(), d);
    }
    else if(functionType == "dary_heapsort"){
        // start time
        auto start = std::chrono::high_resolution_clock::now();
        dary_heapsort(cities, cities.size(), d);
        // end time
        auto end = std::chrono::high_resolution_clock::now();
        // print time taken
        std::cout << "Time taken by dary_heapsort: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " nanoseconds" << std::endl;
    }
    else{
        std::cout << "Wrong function type" << std::endl;
    }

    writeToAFile(cities, outputFileName);
    std::cout << "Number of comparisons: " << comparisons << std::endl;
    return 0;
}

/*
    This function takes the data from the csv file and stores it in the vector
    cities: vector of cities
    fileName: name of the csv file
*/
void takeDataFromCsvFile(std::vector<City>& cities, std::string fileName){
    std::string line;
    std::ifstream file(fileName);
    if(file.is_open()){
        while(getline(file, line)){
            City city;
            city.name = line.substr(0, line.find(";"));
            city.population = std::stoi(line.substr(line.find(";") + 1, line.length()));
            cities.push_back(city);
        }
        file.close();
    }
    else{
        std::cout << "Unable to open file" << std::endl;
    }
}

/*
    This function swaps two cities
    city1: first city
    city2: second city
*/
void customSwap(City& city1, City& city2){
    City temp = city1;
    city1 = city2;
    city2 = temp;
}

/*
    This function prints the cities in the vector
    cities: vector of cities
*/
void printCities(std::vector<City> cities){
    for(int i = 0; i < cities.size(); i++){
        std::cout << cities[i].name << ";" << cities[i].population << std::endl;
    }
}

/*
    This function writes the cities in the vector to a file
    cities: vector of cities
    fileName: name of the the output file
*/
void writeToAFile(std::vector<City> cities, std::string fileName){
    std::ofstream file(fileName);
    for(int i = 0; i < cities.size(); i++){
        file << cities[i].name << ";" << cities[i].population << std::endl;
    }
    file.close();
}

/*
    This function max heapifies a max heap
    cities: vector of cities
    i: index of the city
    heapSize: size of the heap
*/
void max_heapify(std::vector<City>& cities, int i, int heapSize){
    comparisons++; // we count it for every call of the function to calculate the total number of comparisons
    int largest = i; // index of the parent 
    int left = 2 * i + 1; // index of the left child
    int right = 2 * i + 2; // index of the right child
    if(left < heapSize && cities[left].population > cities[i].population){
        largest = left; // if the left child is bigger than the parent, then the left child is the largest
    }
    if(right < heapSize && cities[right].population > cities[largest].population){
        largest = right; // if the right child is bigger than the parent, then the right child is the largest
    }
    if(largest != i){ 
        customSwap(cities[i], cities[largest]); // if the parent is not the largest, then we swap the parent with the largest child
        max_heapify(cities, largest, heapSize); // and than we call the function again for the largest child
    }
}

/*
    This function builds a max heap
    cities: vector of cities
    heapSize: size of the heap
*/
void build_max_heap(std::vector<City>& cities, int heapSize){
    for(int i = cities.size() / 2; i >= 0; i--){ // we start from the last parent node through the first parent node of the vector.
        max_heapify(cities, i, heapSize); // we call the max_heapify function for every non-leaf node 
    }
}

/*
    This function sorts a max heap
    cities: heapified vector of cities
    heapSize: size of the heap
*/
void heapsort(std::vector<City>& cities, int heapSize){
    build_max_heap(cities, cities.size()); // we build the max heap
    for(int i = cities.size() - 1; i >= 1; i--){ // we start from the last element through the first element of the vector.
        customSwap(cities[0], cities[i]); // we swap the first element ,which is the largest, with the last element
        heapSize--; // we decrease the size of the heap because the last element of the vector is already sorted
        max_heapify(cities, 0, heapSize); // we call the max_heapify function for the first element of the vector to make it a max heap again
    }
}

/*
    This function inserts a city into a max heap
    cities: heapified vector of cities
    city: city to be inserted
    heapSize: size of the heap
*/
void max_heap_insert(std::vector<City>& cities, City city, int heapSize){
    heapSize++; // we increase the size of the heap
    cities.push_back(city); // we add the city to the end of the vector
    heap_increase_key(cities, cities.size() - 1, city.population, heapSize); // we call the heap_increase_key function for the city we added
}

/*
    This function extracts the maximum element from a max heap
    cities: heapified vector of cities
    heapSize: size of the heap
    return: City element with maximum population
*/
City heap_extract_max(std::vector<City>& cities, int heapSize){

    if(heapSize < 1){ // if the heap is empty, we return an error
        std::cout << "heap underflow" << std::endl;
    }
    City max = cities[0]; // we store the maximum element
    cities[0] = cities[heapSize - 1]; // we swap the first element with the last element
    heapSize--; // we decrease the size of the heap because the last element of the vector is already sorted
    cities.pop_back(); // we remove the last element of the vector
    max_heapify(cities, 0, heapSize); // we call the max_heapify function for the first element of the vector to make it a max heap again
    return max; // we return the maximum element
}

/*
    This function changes the population of the city in the given index
    cities: heapified vector of cities
    i: index of the city
    key: new key
    heapSize: size of the heap
*/
void heap_increase_key(std::vector<City>& cities, int i, int key, int heapSize){

    if(key < cities[i].population){ // if the new key is smaller than the current key, we return an error
        std::cout << "new key is smaller than current key" << std::endl;
        return;
    }
    cities[i].population = key; // we change the population of the city
    while(i > 0 && cities[(i - 1) / 2].population < cities[i].population){ // we check if the parent is smaller than the child
        customSwap(cities[i], cities[(i - 1) / 2]); // if the parent is smaller than the child, we swap them
        i = (i - 1) / 2; // we change the index to the parent's index
    }
}

/*
    This function returns the maximum element from a max heap
    cities: heapified vector of cities
    heapSize: size of the heap
    return: City element with maximum population
*/
City heap_maximum(std::vector<City>& cities, int heapSize){
    return cities[0]; // we return the first element of the vector
}

/*
    This function calculates the height of a dary heap
    cities: heapified vector of cities
    d: number of children
    return: height of the heap
*/
int dary_calculate_height(std::vector<City>& cities, int d){
    int height = 0; // height of the heap initliazed to 0.
    int i = 0; // index of the heap
    while(i < cities.size()){ // we check if the index is smaller than the size of the vector
        i = d * i + 1; // we calculate the index of the first child and assign it to our index
        height++; // we increase the height
    }
    return height; // we return the height
}

/*
    This function extracts the maximum element from a dary heap
    cities: heapified vector of cities
    heapSize: size of the heap
    d: number of children
    return: City element with maximum population
*/
City dary_extract_max(std::vector<City>& cities, int heapSize, int d){
    if(heapSize < 1){ // if the heap is empty, we return an error
        std::cout << "heap underflow" << std::endl;
        return cities[0];
    }
    City max = cities[0]; // we store the maximum element
    cities[0] = cities[heapSize - 1]; // we swap the first element with the last element
    heapSize--; // we decrease the size of the heap because the last element of the vector is already sorted
    cities.pop_back(); // we remove the last element of the vector
    dary_max_heapify(cities, 0, heapSize, d); // we call the dary_max_heapify function for the first element of the vector to make it a dary max heap again
    return max; // we return the maximum element
}

/*
    This function inserts a city into a dary heap
    cities: heapified vector of cities
    city: city to be inserted
    heapSize: size of the heap
    d: number of children
*/
void dary_insert_element(std::vector<City>& cities, City city, int heapSize, int d){
    heapSize++; // we increase the size of the heap
    cities.push_back(city); // we add the city to the end of the vector
    dary_increase_key(cities, cities.size() - 1, city.population, heapSize, d); // we call the dary_increase_key function for the city we added
}

/*
    This function changes the population of the city in the given index
    cities: heapified vector of cities
    i: index of the city
    key: new key
    heapSize: size of the heap
    d: number of children
*/
void dary_increase_key(std::vector<City>& cities, int i, int key, int heapSize, int d){
    if(key < cities[i].population){ // if the new key is smaller than the current key, we return an error
        std::cout << "new key is smaller than current key" << std::endl;
        return;
    }
    cities[i].population = key; // we change the population of the city 
    int height = dary_calculate_height(cities, d); // we calculate the height of the heap
    while(height > 0){ // we check if the height is bigger than 0
        if(i == 0){ // if the index is 0, then we break the loop
            break;
        }
        int parent = (i - 1) / d; // we calculate the index of the parent
        if(cities[parent].population < cities[i].population){ // we check if the parent is smaller than the child
            customSwap(cities[parent], cities[i]); // if the parent is smaller than the child, we swap them
            i = parent; // we change the index to the parent's index
        }
        height--; // we decrease the height 
    }
}

/*
    This function max heapifies a dary heap
    cities: vector of cities
    i: index of the city
    heapSize: size of the heap
    d: number of children
*/
void dary_max_heapify(std::vector<City>& cities, int i, int heapSize, int d){
    comparisons++; // we count it for every call of the function to calculate the total number of comparisons
    int largest = i; // index of the parent
    int firstChild = d * i + 1; // index of the first child
    int lastChild = d * i + d; // index of the last child
    if(firstChild < heapSize && cities[firstChild].population > cities[i].population){
        largest = firstChild; // if the first child is bigger than the parent, then the first child is the largest
    }
    for(int j = firstChild + 1; j <= lastChild; j++){ // we check the other children
        if(j < heapSize && cities[j].population > cities[largest].population){
            largest = j; // if the child is bigger than the parent, then the child is the largest
        }
    }
    if(largest != i){
        customSwap(cities[i], cities[largest]); // if the parent is not the largest, then we swap the parent with the largest child
        dary_max_heapify(cities, largest, heapSize, d); // and than we call the function again for the largest child
    }
}

/*
    This function builds a dary heap
    cities: vector of cities
    heapSize: size of the heap
    d: number of children
*/
void dary_build_max_heap(std::vector<City>& cities, int heapSize, int d){
    for(int i = cities.size() / d; i >= 0; i--){ // we start from the last parent through the first parent of the vector.
        dary_max_heapify(cities, i, heapSize, d); // we call the dary_max_heapify function for every non-leaf node
    }
}

/*
    This function sorts a dary heap
    cities: heapified vector of cities
    heapSize: size of the heap
    d: number of children
*/
void dary_heapsort(std::vector<City>& cities, int heapSize, int d){
    dary_build_max_heap(cities, cities.size(), d);
    for(int i = cities.size() - 1; i >= 1; i--){ // we start from the last element through the first element of the vector.
        customSwap(cities[0], cities[i]); // we swap the first element ,which is the largest, with the last element
        heapSize--; // we decrease the size of the heap because the last part of the vector is already sorted
        dary_max_heapify(cities, 0, heapSize, d); // we call the dary_max_heapify function for the first element of the vector to make it a dary max heap again
    }
}