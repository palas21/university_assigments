#include "rbt.cpp"
#include "bst.cpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cassert>

template <class T> bool nullNodeCheck(T *node) {
    // this is implemented as RBT's null can be implemented as sentinel node
    // which cannot be checked by nullptr
    // definite control for a node being null is checking its parent and both children
    if (node == nullptr) {
        return true;
    }
    if (node->parent == nullptr && node->left == nullptr && node->right == nullptr) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    RedBlackTree rbTree;
    BinarySearchTree bsTree;

    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename> [v]" << std::endl;
        return 1;
    }

    bool verbose = false;
    if (argc == 4 && argv[3][0] == 'v') {
        verbose = true;
    }

    const char* inputFilename = argv[1];
    const char* outputFilename = argv[2];  // New argument for the output file

    // setting test populations for different files
    // remove the extension from inputFilename
    std::string inputFilenameStr = inputFilename;
    std::string inputFilenameWithoutExtension = inputFilenameStr.substr(0, inputFilenameStr.find("."));
    // get the right most char of the inputFilenameWithoutExtension
    char lastChar = inputFilenameWithoutExtension[inputFilenameWithoutExtension.length() - 1];
    // if char is a number, get the number
    int dataNumber = 0;
    if (isdigit(lastChar)) {
        dataNumber = lastChar - '0';
    }
    int testPopulation = 0;

    // setting to-be-searched and to-be-deleted populations for different files
    switch (dataNumber)
    {
    case 1:
        testPopulation = 442;
        break;
    case 2:
        testPopulation = 75938;
        break;
    case 3:
        testPopulation = 9904000;
        break;
    case 4:
        testPopulation = 10061000;
        break;
    default:
        break;
    }

    // color array
    std::string colorArray[2] = {"B", "R"};

    int dataLength = 0; // number of cities in the file initially set to 0
    std::pair<std::string, int> data[20000]; // array of pairs to store the cities and populations

    std::string line;

    // Read data from the file
    std::ifstream file(inputFilename);
    if (!file) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        size_t pos = line.find(';');
        if (pos != std::string::npos) {
            std::string city = line.substr(0, pos);
            for (size_t i = 0; i < city.length(); i++) {
                if (isalpha(city[i]) == false && city[i] != ' ' && city[i] != '\'') {
                    // if the character is not a letter, space or apostrophe, remove it
                    city.erase(i,1);
                    i--;
                    }
                }     
            
            int population = stoi(line.substr(pos + 1));
            data[dataLength++] = std::make_pair(city, population);
        }
    }

    file.close();


    // Insert the data into the trees
    for (int i = 0; i < dataLength; i++) {
        rbTree.insert(data[i].first, data[i].second);
        bsTree.insert(data[i].first, data[i].second);
    }
    
    // open a log file named "log.txt"
    std::string log_fname = "log_pop" + std::to_string(dataNumber) + ".txt";
    std::ofstream logFile(log_fname);
    if (!logFile) {
        std::cerr << "Error opening the log file." << std::endl;
        return 1;
    }
    // get the minimum and maximum values from both trees
    RBT::Node *rbtMin = rbTree.getMinimum();
    RBT::Node *rbtMax = rbTree.getMaximum();
    BST::Node *bstMin = bsTree.getMinimum();
    BST::Node *bstMax = bsTree.getMaximum();

    std::cout << "RBT: " << std::endl;
    logFile << "RBT: " << std::endl;
    // Print the height of the trees
    if (verbose) {
        std::cout << "Height: " << rbTree.getHeight() << std::endl;
        std::cout << "Nodes: " << rbTree.getTotalNodes() << std::endl;
        std::cout << "Min: " << rbtMin->name << std::endl;
        std::cout << "Max: " << rbtMax->name << std::endl;
        
    }
    // write the height of the trees to the log file
    logFile << "Height: " << rbTree.getHeight() << std::endl;
    logFile << "Nodes: " << rbTree.getTotalNodes() << std::endl;
    // write min and max values to the log file
    logFile << "Min: " << rbtMin->name << std::endl;
    logFile << "Max: " << rbtMax->name << std::endl;

    std::cout << "BST: " << std::endl;
    logFile << "BST: " << std::endl;

    // print the number of nodes in the trees
    if (verbose) {
        std::cout << "Height: " << bsTree.getHeight() << std::endl;
        std::cout << "Nodes: " << bsTree.getTotalNodes() << std::endl;
        std::cout << "Min: " << bstMin->name << std::endl;
        std::cout << "Max: " << bstMax->name << std::endl;
    }

    logFile << "Height: " << bsTree.getHeight() << std::endl;
    logFile << "Nodes: " << bsTree.getTotalNodes() << std::endl;
    // write min and max values to the log file
    logFile << "Min: " << bstMin->name << std::endl;
    logFile << "Max: " << bstMax->name << std::endl;

    // call searchTree on the red black tree
    
    RBT::Node *rbtNode = rbTree.searchTree(testPopulation);
    
    std::string randomCity = rbtNode->name;

    if (verbose) {
        std::cout << "Searching for " << randomCity << "(" << colorArray[rbtNode->color] << ")" << " with population " << testPopulation << std::endl;
    }
    // write the minimum and maximum values to the log file
    logFile << "Searching for " << randomCity << "(" << colorArray[rbtNode->color] << ")" << " with population " << testPopulation << std::endl;

    if (nullNodeCheck(rbtNode)) {
        // this is given to you to check whether the node returned by searchTree is nullptr
        // result should be same for both RBT and BST
        // if the searchTree returns nullptr with given population numbers;
        // something is wrong about the implementation
        std::cerr << "Error: RBT.searchTree() returned nullptr." << std::endl;
        return 1;
    }
    // get the parent of the node returned by searchTree
    RBT::Node *rbtParent = rbtNode->parent;
    // get the children of the node returned by searchTree
    RBT::Node *rbtLeft = rbtNode->left;
    RBT::Node *rbtRight = rbtNode->right;
    // get successor of the node returned by searchTree
    RBT::Node *rbtSuccessor = rbTree.successor(rbtNode);
    // get predecessor of the node returned by searchTree
    RBT::Node *rbtPredecessor = rbTree.predecessor(rbtNode);
    // call searchTree on the binary search tree
    BST::Node *bstNode = bsTree.searchTree(testPopulation);
    
    if (nullNodeCheck(bstNode)) {
        // this is given to you to check whether the node returned by searchTree is nullptr
        // result should be same for both RBT and BST
        // if the searchTree returns nullptr with given population numbers;
        // something is wrong about the implementation
        std::cerr << "Error: BST.searchTree() returned nullptr." << std::endl;
        return 1;
    }
    // get the parent of the node returned by searchTree
    BST::Node *bstParent = bstNode->parent;
    // get the children of the node returned by searchTree
    BST::Node *bstLeft = bstNode->left;
    BST::Node *bstRight = bstNode->right;
    // get successor of the node returned by searchTree
    BST::Node *bstSuccessor = bsTree.successor(bstNode);
    // get predecessor of the node returned by searchTree
    BST::Node *bstPredecessor = bsTree.predecessor(bstNode);
    // write the results to the log file return 1;
    
    logFile << "RBT: " << std::endl;
    if (verbose) {
        std::cout << "RBT: " << std::endl;}
    // write city names of parent (P), left (L), right (R), successor (S) and predecessor (Pr) to the log file if they are not nullptr
    if (rbtParent != nullptr) {
        logFile << "P" << "(" <<colorArray[rbtParent->color] << "):" << rbtParent->name<<";";
        if (verbose) {
        std::cout << "P" << "(" <<colorArray[rbtParent->color] << "):" << rbtParent->name<<";";}
        if (rbtParent->color == 1){
            // if the parent is red, its children should be black
            assert(rbtNode->color == 0);
        }
    }
    if (nullNodeCheck(rbtLeft) == false) {
        logFile << "L" << "(" <<colorArray[rbtLeft->color] << "):" << rbtLeft->name << ";";
        if (verbose) {
        std::cout << "L" << "(" <<colorArray[rbtLeft->color] << "):" << rbtLeft->name << ";";}
        if (rbtNode->color == 1){
            // if the left child is red, its children should be black
            assert(rbtLeft->color == 0);
        }
    }
    if (nullNodeCheck(rbtRight) == false) {
        logFile << "R" << "(" <<colorArray[rbtRight->color] << "):" << rbtRight->name<< ";";
        if (verbose) {
        std::cout << "R" << "(" <<colorArray[rbtRight->color] << "):" <<  rbtRight->name<< ";";}
        if (rbtNode->color == 1){
            // if the left child is red, its children should be black
            assert(rbtRight->color == 0);
        }
    }
    // write city name of successor to the log file if it is not nullptr
    if (nullNodeCheck(rbtSuccessor) == false) {
        logFile << "S:" << rbtSuccessor->name << ";";
        if (verbose) {
        std::cout << "S:" << rbtSuccessor->name << ";";}
        assert(rbtSuccessor->data >= rbtNode->data); // successor should be greater than the node
    }
    // write city name of predecessor to the log file if it is not nullptr
    if (nullNodeCheck(rbtPredecessor) == false) {
        logFile << "Pr:" << rbtPredecessor->name << std::endl;
        if (verbose) {
        std::cout << "Pr:" << rbtPredecessor->name << std::endl;}
        assert(rbtPredecessor->data <= rbtNode->data); // predecessor should be smaller than the node
    }
    logFile << "BST: " << std::endl;
    if (verbose) {
        std::cout << "BST: " << std::endl;}
    if (nullNodeCheck(bstParent) == false) {
        logFile << "P:" << bstParent->name<<";";
        if (verbose) {
        std::cout << "P:" << bstParent->name<<";";}
    }
    if (nullNodeCheck(bstLeft) == false) {
        logFile << "L:" << bstLeft->name << ";";
        if (verbose) {
        std::cout << "L:" << bstLeft->name << ";";}
    }
    if (nullNodeCheck(bstRight) == false) {
        logFile << "R:" << bstRight->name << ";";
        if (verbose) {
        std::cout << "R:" << bstRight->name << ";";}
    } 
    // write city name of successor to the log file if it is not nullptr (should be same with red black tree)
    if (nullNodeCheck(bstSuccessor) == false) {
        logFile << "S:" << bstSuccessor->name << ";";
        if (verbose) {
        std::cout << "S:" << bstSuccessor->name << ";";}
        assert(bstSuccessor->data >= bstNode->data);
    }
    // write city name of predecessor to the log file if it is not nullptr (should be same with red black tree)
    if (nullNodeCheck(bstPredecessor) == false) {
        logFile << "Pr:" << bstPredecessor->name << std::endl;
        if (verbose) {
        std::cout << "Pr:" << bstPredecessor->name << std::endl;}
        assert(bstPredecessor->data <= bstNode->data);
    }

    // create a std::pair<std::string, int> array to store the ordered list of cities and populations
    std::pair<std::string, int> orderedDataRB[20000];
    // call inorder on the red black tree, passing in the std::pair<std::string, int> array and the length of the array
    // this will populate the array with the ordered list of cities and populations
    // you can get help about insertion from 98th line above:
    //data[dataLength++] = std::make_pair(city, population);
    //0 is starting index for the pair array of cities sorted according to the population
    rbTree.inorder(orderedDataRB,0);

    // create a std::pair<std::string, int> array to store the ordered list of cities and populations
    std::pair<std::string, int> orderedDataBST[20000];
    // call inorder on the binary search tree, passing in the std::pair<std::string, int> array and the length of the array
    // this will populate the array with the ordered list of cities and populations
    // you can get help about insertion from 98th line above:
    //data[dataLength++] = std::make_pair(city, population);
    //0 is starting index for the pair array of cities sorted according to the population
    bsTree.inorder(orderedDataBST,0);

    // remove the extension of the outputFilename
    std::string outputFilenameStr = outputFilename;
    std::string outputFilenameWithoutExtension = outputFilenameStr.substr(0, outputFilenameStr.find("."));
    // add the extension "_rbt.csv" to the outputFilenameWithoutExtension
    std::string outputFilenameRB = outputFilenameWithoutExtension + "_rbt.csv";
    // add the extension "_bst.csv" to the outputFilenameWithoutExtension
    std::string outputFilenameBST = outputFilenameWithoutExtension + "_bst.csv";

    // Write the sorted data to the output file
    std::ofstream outputFileRB(outputFilenameRB);
    if (!outputFileRB) {
        std::cerr << "Error opening the output file." << std::endl;
        return 1;
    }
    
    dataLength = rbTree.getTotalNodes(); // update the dataLength to the number of nodes in the tree

    for (int i = 0; i < dataLength; i++) {
        outputFileRB << orderedDataRB[i].first << ";" << orderedDataRB[i].second << std::endl;
    }

    outputFileRB.close();

    // Write the sorted data to the output file
    std::ofstream outputFileBST(outputFilenameBST);
    if (!outputFileBST) {
        std::cerr << "Error opening the output file." << std::endl;
        return 1;
    }

    for (int i = 0; i < dataLength; i++) {
        outputFileBST << orderedDataBST[i].first << ";" << orderedDataBST[i].second << std::endl;
    }

    outputFileBST.close();

    // Delete the random value from the trees
    if (verbose) {
        std::cout << "Deleting " << "a city with population " << testPopulation << std::endl;
    }
    // write same line to the log file
    logFile << "Deleting " <<"a city with population " << testPopulation << std::endl;

    // call deleteNode on the red black tree
    rbTree.deleteNode(testPopulation);
    // call deleteNode on the binary search tree
    bsTree.deleteNode(testPopulation);

    // print total number of nodes in the trees
    if (verbose) {
        std::cout << "RBT nodes: " << rbTree.getTotalNodes() << std::endl;
        std::cout << "BST nodes: " << bsTree.getTotalNodes() << std::endl;
    }
    // write total number of nodes in the trees to the log file
    logFile << "RBT nodes: " << rbTree.getTotalNodes() << std::endl;
    logFile << "BST nodes: " << bsTree.getTotalNodes() << std::endl;




    logFile.close();

    return 0;
}
