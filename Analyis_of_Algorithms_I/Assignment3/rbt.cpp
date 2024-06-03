// EB
// Implementing Red-Black Tree in C++

#include <iostream>

namespace RBT {
  struct Node {
    int data;
    std::string name;
    Node *parent;
    Node *left; 
    Node *right;
    int color; // 0 -> Black, 1 -> Red
  };
}

class RedBlackTree {
private:

  RBT::Node *root; // This is the root of the tree
  RBT::Node *nil;  // This is the nil node of the tree 

  void preorderHelper(RBT::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for preorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in preorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then we will store the data in the array and traverse the left and right subtree.
      population[dataLength++] = std::make_pair(node->name, node->data);
      preorderHelper(node->left,population,dataLength);
      preorderHelper(node->right,population,dataLength);
      }
  }

  void inorderHelper(RBT::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for inorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in inorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then we will traverse the left subtree, store the data in the array and traverse the right subtree.
      inorderHelper(node->left,population,dataLength);
      population[dataLength++] = std::make_pair(node->name, node->data);
      inorderHelper(node->right,population,dataLength);
    }
  }

  void postorderHelper(RBT::Node *node, std::pair<std::string,int> population[], int& dataLength){ // this is a helper function for postorder traversal. It is a recursive function that takes in a node and an array named population and dataLength. It will traverse the tree in postorder and store the data in the given array.
    if(node != this->nil){ // if the node is not nil, then we will traverse the left and right subtree and store the data in the array.
      postorderHelper(node->left,population,dataLength);
      postorderHelper(node->right,population,dataLength);
      population[dataLength++] = std::make_pair(node->name, node->data);
    }
  }

  RBT::Node* searchTreeHelper(RBT::Node *node, int population){ // this is a helper function for searching the tree. It is a recursive function that takes in a node which is the root of a subtree and the population we are searching for. It will traverse the tree and return the node if it is found. If it is not found, it will return the nil node.
    if(node == this->nil || population == node->data) return node; // if the node is nil or the population is found, then we will return the node.
    else if(population < node->data) return searchTreeHelper(node->left,population); // if the population is less than the node's data, then we will traverse the left subtree.
    else return searchTreeHelper(node->right,population); // if the population is greater than the node's data, then we will traverse the right subtree.
  }

  void insertFix(RBT::Node *z){ // this is a helper function for insertion. It will fix the tree after insertion. 
    RBT::Node * y; // this is a node that will be used to store the aunt/uncle of the node z. I will say uncle for simplicity.
    while (z->parent->color == 1) { // while the parent of the node z is red, we will fix the tree.
      if (z->parent == z->parent->parent->right) { // if the parent of the node z is the right child of the grandparent of the node z, then we will store the uncle of the node z in y.
        y = z->parent->parent->left;
        if (y->color == 1){ // if the uncle of the node z is red, then we will change the color of the parent of the node z, the uncle of the node z and the grandparent of the node z to black and change the color of the grandparent of the node z to red. Then we will set the node z to the grandparent of the node z.
          y->color = 0;
          z->parent->color = 0;
          z->parent->parent->color = 1;
          z = z->parent->parent;
        }
        else{ // if the uncle of the node z is black, then we will check if the node z is the left child of the parent of the node z. If it is, then we will set the node z to the parent of the node z and perform a right rotation on the node z. Then we will change the color of the parent of the node z to black and the color of the grandparent of the node z to red. Then we will perform a left rotation on the grandparent of the node z.
          if(z == z->parent->left){
            z = z->parent;
            rightRotate(z);
          }

          z->parent->color = 0;
          z->parent->parent->color = 1;
          leftRotate(z->parent->parent); 
        }
    }

    else{ // if the parent of the node z is the left child of the grandparent of the node z, then we will store the uncle of the node z in y.
      y = z->parent->parent->right;

      if (y->color == 1){ // if the uncle of the node z is red, then we will change the color of the parent of the node z, the uncle of the node z and the grandparent of the node z to black and change the color of the grandparent of the node z to red. Then we will set the node z to the grandparent of the node z.
        y->color = 0;
        z->parent->color = 0;
        z->parent->parent->color = 1;
        z = z->parent->parent;
      }
      else{ // if the uncle of the node z is black, then we will check if the node z is the right child of the parent of the node z. If it is, then we will set the node z to the parent of the node z and perform a left rotation on the node z. Then we will change the color of the parent of the node z to black and the color of the grandparent of the node z to red. Then we will perform a right rotation on the grandparent of the node z.
        if(z == z->parent->right){
          z = z->parent;
          leftRotate(z);
        }
        z->parent->color = 0;
        z->parent->parent->color = 1;
        rightRotate(z->parent->parent);
      }
    }
    if (z == root) { // if the node z is the root we will break out of the loop.
      break;
    }
  }
  root->color = 0; // we will change the color of the root to black.
  }

  void leftRotate(RBT::Node *x) { // this is a helper function for left rotation. It will perform a left rotation on the node x.
    RBT::Node *y = x->right;
    x->right = y->left;
    if (y->left != this->nil) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(RBT::Node *x) { // this is a helper function for right rotation. It will perform a right rotation on the node x.
    RBT::Node *y = x->left;
    x->left = y->right;
    if (y->right != this->nil) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void deleteFix(RBT::Node *x) { // this is a helper function for deletion. It will fix the tree after deletion.
    RBT::Node *w;
    while(x != root && x->color == 0){ // while the node x is not the root and the color of the node x is black, we will fix the tree.
      if(x == x->parent->left){
        w = x->parent->right;
        if (w->color == 1){ // if the color of the node w is red, then we will change the color of the node w to black and the color of the parent of the node x to red. Then we will perform a left rotation on the parent of the node x and set the node w to the right child of the parent of the node x.
          w->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          w = x->parent->right;
        }

        if(w->left->color == 0 && w->right->color == 0){ // if the left and right child of the node w is black, then we will change the color of the node w to red and set the node x to the parent of the node x.
          w->color = 1;
          x = x->parent;
        }

        else{ // if the left and right child of the node w is not black
          if (w->right->color == 0) { // if the right child of the node w is black, then we will change the color of the node w to red and the color of the left child of the node w to black. Then we will perform a right rotation on the node w and set the node w to the right child of the parent of the node x.
            w->left->color = 0;
            w->color = 1;
            rightRotate(w);
            w = x->parent->right;
          }

          w->color = x->parent->color; // we will set the color of the node w to the color of the parent of the node x.
          x->parent->color = 0; // we will set the color of the parent of the node x to black.
          w->right->color = 0; // we will set the color of the right child of the node w to black.
          leftRotate(x->parent); // we will perform a left rotation on the parent of the node x.
          x = root; // we will set the node x to the root.
        }
      }

      else{ // if the node x is the right child of the parent of the node x, then we will set the node w to the left child of the parent of the node x.
        w = x->parent->left; 
        if(w->color == 1){ // if the color of the node w is red, then we will change the color of the node w to black and the color of the parent of the node x to red. Then we will perform a right rotation on the parent of the node x and set the node w to the left child of the parent of the node x.
          w->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          w = x->parent->left;
        }

        if(w->right->color == 0 && w->right->color == 0){ // if the left and right child of the node w is black, then we will change the color of the node w to red and set the node x to the parent of the node x.
          w->color = 1;
          x = x->parent;
        } 
        else{ // if the left and right child of the node w is not black
          if (w->left->color == 0) { // if the left child of the node w is black, then we will change the color of the node w to red and the color of the right child of the node w to black. Then we will perform a left rotation on the node w and set the node w to the left child of the parent of the node x.
            w->right->color = 0;
            w->color = 1;
            leftRotate(w);
            w = x->parent->left;
          }
          w->color = x->parent->color; // we will set the color of the node w to the color of the parent of the node x.
          x->parent->color = 0; // we will set the color of the parent of the node x to black.
          w->left->color = 0; // we will set the color of the left child of the node w to black.
          rightRotate(x->parent); // we will perform a right rotation on the parent of the node x.
          x = root; // we will set the node x to the root.
        }
      }
    }
    x->color = 0; // we will set the color of the node x to black.
  }

  void transplant(RBT::Node *u, RBT::Node *v){ // THis function will replace the subtree rooted at node u with the subtree rooted at node v.
    if(u->parent == this->nil){ // if the parent of the node u is nil, then we will set the root to the node v.
      root = v; 
    } 
    else if(u == u->parent->left){ // if the node u is the left child of the parent of the node u, then we will set the left child of the parent of the node u to the node v.
      u->parent->left = v;
    } 
    else{ // if the node u is the right child of the parent of the node u, then we will set the right child of the parent of the node u to the node v.
      u->parent->right = v;
    }
    v->parent = u->parent; // we will set the parent of the node v to the parent of the node u.
  }

  void deleteGivenNode(RBT::Node *node){
    RBT::Node *z = node; // we will store the node in z.
    RBT::Node *x, *y; // we will create two nodes x and y.

    y = z; 
    int y_original_color = y->color;  // we will store the color of the node y in y_original_color.
    
    if(z->left == this->nil){ // if the left child of the node z is nil, then we will set the node x to the right child of the node z and call the transplant function to replace the subtree rooted at node z with the subtree rooted at node x.
      x = z->right;
      transplant(z, z->right);
    }
    else if(z->right == this->nil){ // if the right child of the node z is nil, then we will set the node x to the left child of the node z and call the transplant function to replace the subtree rooted at node z with the subtree rooted at node x.
      x = z->left;
      transplant(z, z->left);
    } 
    else{ // if the left and right child of the node z is not nil
      y = findMinimum(z->right);  // we will set the node y to the minimum node in the right subtree of the node z.
      y_original_color = y->color; // we will store the color of the node y in y_original_color.
      x = y->right; // we will set the node x to the right child of the node y.
      if(y->parent == z){ // if the parent of the node y is the node z, then we will set the parent of the node x to the node y.
        x->parent = y;
      } 
      else{ // if the parent of the node y is not the node z, then we will call the transplant function to replace the subtree rooted at node y with the subtree rooted at node x.
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      transplant(z, y); // we will call the transplant function to replace the subtree rooted at node z with the subtree rooted at node y.
      y->left = z->left; // we will set the left child of the node y to the left child of the node z. 
      y->left->parent = y; // we will set the parent of the left child of the node y to the node y.
      y->color = z->color; // we will set the color of the node y to the color of the node z.
    }
    delete z; // we will delete the node z.
    if(y_original_color == 0){ // if the color of the node y is black, then we will call the deleteFix function to fix the tree.ddd
      deleteFix(x);
    }
  }

  int findHeight(RBT::Node *node){ // this function takes in a node and the height of the tree. It will return the height of the tree.
    if(node == this->nil){ // if the node is nil, then we will return 0.
      return 0;
    }
    else{
      return 1 + std::max(findHeight(node->left), findHeight(node->right)); // we will return current height + the maximum of the height of the left subtree and the height of the right subtree.
    }
  }

  RBT::Node* findMaximum(RBT::Node *node){ // this function takes in a node and returns the maximum node in the tree.
    while(node->right != this->nil){ // while the right child of the node is not nil, we will set the node to the right child of the node.
      node = node->right;
    }
    return node;
  }

  RBT::Node* findMinimum(RBT::Node *node){ // this function takes in a node and returns the minimum node in the tree.
    while(node->left != this->nil){ // while the left child of the node is not nil, we will set the node to the left child of the node.
      node = node->left;
    }
    return node; 
  }

  int findTotalNodes(RBT::Node *node){ // this function takes in a node and returns the total number of nodes in the tree.
    if(node == this->nil){ // if the node is nil, then we will return 0.
      return 0;
    }
    else{
      return 1 + findTotalNodes(node->left) + findTotalNodes(node->right); // we will return current node + the total number of nodes in the left subtree + the total number of nodes in the right subtree.
    }
  }

public:

  RedBlackTree() { // this is the constructor for the RedBlackTree class. It will initialize the nil node and set the root to the nil node.
    this->nil = new RBT::Node;
    this->nil->color = 0;
    this->nil->left = nullptr;
    this->nil->right = nullptr;
    this->nil->parent = nullptr;
    this->root = this->nil;
  }

  void preorder(std::pair<std::string,int> population[], int size){ // this function takes in an array named population and size. It will call the preorderHelper function to traverse the tree in preorder and store the data in the given array.
    preorderHelper(this->root,population,size);
  }

  void inorder(std::pair<std::string,int> population[], int size){ // this function takes in an array named population and size. It will call the inorderHelper function to traverse the tree in inorder and store the data in the given array.
    inorderHelper(this->root,population,size);
  }
  
  void postorder(std::pair<std::string,int> population[], int size){ // this function takes in an array named population and size. It will call the postorderHelper function to traverse the tree in postorder and store the data in the given array.
    postorderHelper(this->root, population, size);
  }

  RBT::Node* searchTree(int population){ // this function takes in a population and returns the node with the given population.
    return searchTreeHelper(this->root, population);
  }

  RBT::Node* successor(RBT::Node *x){ // this function takes in a node and returns the successor of the node.
    if (x->right != this->nil) { // if the right child of the node is not nil, then we will return the minimum node in the right subtree.
      return findMinimum(x->right);
    }

    RBT::Node *y = x->parent; // we will store the parent of the node in y.
    while (y != this->nil && x == y->right) { // while y is not nil and the node is the right child of y, we will set the node to y and y to the parent of y.
      x = y;
      y = y->parent;
    }
    return y; // return the parent node of the node that is not the right child of the parent node.
  }

  RBT::Node* predecessor(RBT::Node* x){ // this function takes in a node and returns the predecessor of the node.
    if (x->left != this->nil){ // if the left child of the node is not nil, then we will return the maximum node in the left subtree.
      return findMaximum(x->left);
    }

    RBT::Node *y = x->parent; // we will store the parent of the node in y.
    while (y != this->nil && x == y->left){ // while y is not nil and the node is the left child of y, we will set the node to y and y to the parent of y.
      x = y;
      y = y->parent;
    }
    return y; // return the parent node of the node that is not the left child of the parent node.
  }

  void insert(std::string city, int population){ // this function takes in a city and population and inserts the node with the given city and population into the tree.
    RBT::Node *node = new RBT::Node; // we will create a new node.
    node->parent = nullptr;
    node->data = population;
    node->name = city;
    node->left = this->nil;
    node->right = this->nil;
    node->color = 1; // we will set the color of the node to red.

    RBT::Node *y = nullptr; // we will create a node y and set it to nullptr.
    RBT::Node *x = this->root; // we will create a node x and set it to the root of the tree.

    while (x != this->nil) { 
      y = x; // we will set y to x.
      if (node->data < x->data) { // if the population of the node is less than the population of x, then we will set x to the left child of x.
        x = x->left;
      } else {
        x = x->right; // if the population of the node is greater than the population of x, then we will set x to the right child of x.
      }
    }
    // after while operation we get y as the parent of the node.

    node->parent = y; // we will set the parent of the node to y.
    if(y == nullptr){ // if y is nullptr, then we will set the root to the node.
      root = node;
    } 
    else if(node->data < y->data){ // if the population of the node is less than the population of y, then we will set the left child of y to the node.
      y->left = node;
    } 
    else{ // if the population of the node is greater than the population of y, then we will set the right child of y to the node.
      y->right = node;
    }

    if (node->parent == nullptr){ // if the parent of the node is nullptr, then we will set the color of the node to black and return.
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) { // if the grandparent of the node is nullptr, then we will return.
      return;
    }

    insertFix(node); // we will call the insertFix function to fix the tree.
  }

  void deleteNode(int population){ // this function takes in a population and deletes the node with the given population.
    RBT::Node *node = searchTree(population); // we will search for the node with the given population.
    deleteGivenNode(node); // we will delete the node.
  }

  int getHeight(){ // this function returns the height of the tree.
    return findHeight(this->root) - 1; // we will return the height of the tree - 1 because the height of the tree is the number of edges from the root to the deepest leaf node.
  }

  RBT::Node* getMaximum(){ // this function returns the maximum node in the tree.
    return findMaximum(this->root);
  }

  RBT::Node* getMinimum(){ // this function returns the minimum node in the tree.
    return findMinimum(this->root);
  }

  int getTotalNodes(){ // this function returns the total number of nodes in the tree.
    return findTotalNodes(this->root);
  }
};