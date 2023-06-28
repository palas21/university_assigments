//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Şafak Özkan Pala  
//---Student Number: 150210016
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    this->head = NULL;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){ // YAZ
    //if queue is empty
    if(this->head == NULL){ // we make this node the head node.
        this->head = newnode;
        return;
    }
    
    //if queue has one node.
    Node* temp = this->head;
    if(this->head->next == NULL){ // if there is not a node after this node we compare both nodes and choose where newnode should be.
        if(this->head->token.val > newnode->token.val){ // if this node is lesser than the next node we make this node the head node.
            this->head = newnode;
            newnode->next = temp;
        }
        else{ // if this newnode equall or bigger than the head node we make this node second node.
            this->head->next = newnode;
        }
        return;
    }

    // if queue has nore than one node.

    //check for the first node.
    if(this->head->token.val > newnode->token.val){ // if newnode is not equal or bigger than the head node we make this node the head node.
            this->head = newnode;
            newnode->next = temp;
            return;
    }
    //check for the others.
    while(!(newnode->token.val < temp->token.val)){ // if temp newnode is not smaller than the temp node we continue.
        if(temp->next == NULL){ // if there is no next element we add newnode to end of the queue.
            temp->next = newnode;
            return;
        }
        if(temp->next->token.val > newnode->token.val){//if new node is smaller than the next node we add newnode between temp and temp next.
            newnode->next = temp->next;
            temp->next = newnode;
            return;
        }
        else{ // if newnode is bigger than current and next node and the next node is not NULL we continue. 
            temp = temp->next;
        }
    }
};
//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    // if queue is empty.
    if(this->head == NULL) return NULL;

    // if queueu is not empty we get the head node.
    Node* temp = this->head;
    this->head = this->head->next;
    temp->next = NULL;

    return temp;
};

//-------------Initialize Tree-------------//
Tree::Tree(){
    this->root = NULL;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    deleteTree(root);
    this->root = NULL;
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    if(node == NULL) return;
    // I choose postorder reverse call to delete all nodes.
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    // creating a new node and adding two node to this node.
    Node* temp = new Node();

    temp->token.symbol = temp1->token.symbol + temp2->token.symbol;
    temp->token.val = temp1->token.val + temp2->token.val;
    temp->left = temp1;
    temp->right = temp2;
    temp->next = NULL;
   
    return temp;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};