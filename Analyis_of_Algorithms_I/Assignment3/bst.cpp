// EB
// Implementing Binary Search Tree in C++

#include <iostream>

namespace BST {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };
}

class BinarySearchTree {
private:
  BST::Node *root; // this is the root of the three
  BST::Node *nil; // this is the nil node of the tree

  void preorderHelper(BST::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for preorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in preorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then store the data in the array and traverse the left and right subtree
      population[dataLength++] = std::make_pair(node->name, node->data); 
      preorderHelper(node->left,population,dataLength);
      preorderHelper(node->right,population,dataLength);
      }
  }

  void inorderHelper(BST::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for inorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in inorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then traverse the left subtree, store the data in the array, and traverse the right subtree
      inorderHelper(node->left,population,dataLength); 
      population[dataLength++] = std::make_pair(node->name, node->data);
      inorderHelper(node->right,population,dataLength);
    }
  }

  void postorderHelper(BST::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for postorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in postorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then traverse the left and right subtree and store the data in the array
      postorderHelper(node->left,population,dataLength); 
      postorderHelper(node->right,population,dataLength);
      population[dataLength++] = std::make_pair(node->name, node->data);
    }
  }

  BST::Node* searchTreeHelper(BST::Node *node, int population){ // this is a helper function for searchTree. It is a recursive function that takes in a node and an integer population. It will traverse the tree and return the node that contains the given population.
    if(node == this->nil || population == node->data) return node; // if the node is nil or the population is equal to the node's data, then return the node
    else if(population < node->data) return searchTreeHelper(node->left,population); // if the population is less than the node's data, then traverse the left subtree
    else return searchTreeHelper(node->right,population); // if the population is greater than the node's data, then traverse the right subtree
  }

  int findHeight(BST::Node *node){ // this is a helper function for getHeight. It is a recursive function that takes in a node which is the root of the subtree. It will traverse the tree and return the height of the tree.
    if(node == this->nil){ // if the node is nil, then return the height
      return 0;
    }
    else{ // if the node is not nil, then traverse the left and right subtree and return the maximum height of the two subtrees + current node.
      return 1 + std::max(findHeight(node->left), findHeight(node->right));
    }
  }

  BST::Node* findMaximum(BST::Node *node){ // this is a helper function for getMaximum. It iterates through the right subtree and returns the node with the maximum data. 
    while(node->right != this->nil){ // traverse the right subtree until the node is nil
      node = node->right;
    }
    return node;
  }

  BST::Node* findMinimum(BST::Node *node){ // this is a helper function for getMinimum. It iterates through the left subtree and returns the node with the minimum data.
    while(node->left != this->nil){ // traverse the left subtree until the node is nil
      node = node->left;
    }
    return node;
  }

  int findTotalNodes(BST::Node *node){ // this is a helper function for getTotalNodes. It is a recursive function that takes in a node. It will traverse the tree and return the total number of nodes in the tree.
    if(node == this->nil){ // if the node is nil, then return 0
      return 0;
    }
    else{
      return 1 + findTotalNodes(node->left) + findTotalNodes(node->right); // if the node is not nil, then traverse the left and right subtree and return the total number of nodes in the tree + current node.
    }
  }

public:

  BinarySearchTree() { // this is the constructor of the class. It will initialize the nil node and set the root to nil.
    this->nil = new BST::Node;
    this->nil->left = nullptr;
    this->nil->right = nullptr;
    this->nil->parent = nullptr;
    this->root = this->nil;
  }

  void preorder(std::pair<std::string,int> population[], int size){ // this is a function that takes in an array of population and size. It will call the preorderHelper function to traverse the tree in preorder and store the data in the given array.
    preorderHelper(this->root,population,size);
  }
  
  void inorder(std::pair<std::string,int> population[], int size){ // this is a function that takes in an array of population and size. It will call the inorderHelper function to traverse the tree in inorder and store the data in the given array.
    inorderHelper(this->root,population,size);
  }

  void postorder(std::pair<std::string,int> population[], int size){ // this is a function that takes in an array of population and size. It will call the postorderHelper function to traverse the tree in postorder and store the data in the given array.
    postorderHelper(this->root, population, size);
  }

  BST::Node* searchTree(int population){ // this is a function that takes in an integer population. It will call the searchTreeHelper function to traverse the tree and return the node that contains the given population.
    return searchTreeHelper(this->root, population);
  }

  BST::Node* successor(BST::Node *x) { // this is a function that takes in a node. It will return the successor of the given node.
    if (x->right != this->nil) { // if the right subtree is not nil, then return the minimum node of the right subtree
      return findMinimum(x->right);
    }

    BST::Node *y = x->parent; // if the right subtree is nil, then traverse the parent node until the node is not the right child of the parent node
    while (y != this->nil && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y; // return the parent node of the node that is not the right child of the parent node
  }

  BST::Node* predecessor(BST::Node* x) { // this is a function that takes in a node. It will return the predecessor of the given node. 
    if (x->left != this->nil) { // if the left subtree is not nil, then return the maximum node of the left subtree
      return findMaximum(x->left);
    }

    BST::Node *y = x->parent; // if the left subtree is nil, then traverse the parent node until the node is not the left child of the parent node
    while (y != this->nil && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y; // return the parent node of the node that is not the left child of the parent node
  }

  void insert(std::string city, int population){ // this is a function that takes in a string city and an integer population. It will create a new node and insert it into the tree.
    BST::Node *z = new BST::Node; // create a new node
    z->data = population;
    z->name = city;
    z->left = this->nil;
    z->right = this->nil;
    BST::Node *y = this->nil; 
    BST::Node *x = this->root;

    while(x != this->nil){ // traverse the tree until the node is nil
      y = x; 
      if(z->data < x->data){ // if the population is less than the node's data, then traverse the left subtree
        x = x->left;
      }
      else{ // if the population is greater than the node's data, then traverse the right subtree
        x = x->right;
      }
    }
    z->parent = y; // set the parent of the new node to y
    if(y == this->nil){ // if y is nil, then set the root to z
      root = z;
    }
    else if(z->data < y->data){ // if the population is less than y's data, then set y's left child to z
      y->left = z;
    }
    else{ // if the population is greater than y's data, then set y's right child to z
      y->right = z;
    }
  }

  void deleteNode(int population){ // this is a function that takes in an integer population. It will delete the node that contains the given population.
    BST::Node *z = searchTree(population); // search for the node that contains the given population
    if(z == this->nil){ // if the node is nil, then return
      return;
    }
    BST::Node *y = nullptr; 
    BST::Node *x = nullptr; 

    if(z->left == this->nil || z->right == this->nil){ // if the left or right child is nil, then set y to z
      y = z;
    }
    else{ // if the left and right child is not nil, then set y to the successor of z
      y = successor(z);
    }

    if(y->left != this->nil){ // if y's left child is not nil, then set x to y's left child
      x = y->left;
    }
    else{ // if y's left child is nil, then set x to y's right child
      x = y->right;
    }

    x->parent = y->parent; // set x's parent to y's parent

    if(y->parent == this->nil){ // if y's parent is nil, then set the root to x
      this->root = x;
    }
    else if(y == y->parent->left){ // if y is the left child of y's parent, then set y's parent's left child to x
      y->parent->left = x;
    }
    else{ // if y is the right child of y's parent, then set y's parent's right child to x
      y->parent->right = x; 
    }

    if(y != z){ // if y is not z, then set z's data to y's data
      z->data = y->data;
    }
  }

  int getHeight(){ // this is a function that will call the findHeight function to return the height of the tree.
    return findHeight(this->root) - 1; // subtract 1 from the height because the height of the tree is the number of edges from the root to the deepest leaf node
  }

  BST::Node* getMaximum(){ // this is a function that will call the findMaximum function to return the node with the maximum population.
    return findMaximum(this->root);
  }

  BST::Node* getMinimum() { // this is a function that will call the findMinimum function to return the node with the minimum population.
    return findMinimum(this->root);
  }

  int getTotalNodes() { // this is a function that will call the findTotalNodes function to return the total number of nodes in the tree.
    return findTotalNodes(this->root);
  }
};