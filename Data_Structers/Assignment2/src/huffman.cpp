//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Şafak Özkan Pala
//---Student Number: 150210016
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS

    int ascii[128] = {0}; // This array represent the ascii table and every character has their frequency in this array. Every charachter have their frequency in nth element of the array. (n = ascii tavle value of the character). For example 'A' has its frequency in ascii[65].
    
    for(int i = 0;this->sortedKey[i] != '\0';i++){
        ascii[(int)this->sortedKey[i]]++;// increasing frequency every time we encounter this character.
    }
    for(int i = 0; i < 128; i++){ // we scan all of the array to find the characters that are used.
        if(ascii[i] != 0){
            Node *temp = new Node(); // creating a new node 
            temp->token.val = ascii[i]; // adding its frequency.
            temp->token.symbol = string(1,i); // i is the ascii table value of the character and we converte it to string and assign it to our symbol.
            queue.enque(temp);// we add this node in to the priority queue.
        }
    }
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    findFrequency(); // we create our priority queue.
    while(queue.head->next != NULL){ // until the there is only one element in the priorty queue we continue these processes.
        Node *leftNode= this->queue.dequeue(); // we get our left node of the tree.
        Node *rightNode = this->queue.dequeue(); // we get our right node of the tree
        queue.enque(huffmanTree.mergeNodes(leftNode,rightNode)); // we create a new node with leftnode and rightnode and add this node into our priority queue.
    }
    huffmanTree.root = queue.head; // root of the tree is the first element of the priority queue.
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){

    string s = ""; // we create a string that is only contain tokenChar
    s += tokenChar;
    int flag;
    while (traverse->token.symbol.length() != 1) // until the only one character remain in the symbol we continue there processes.
    {
        flag = 0; // we set flag 0 for both
        for(int i = 0; traverse->left->token.symbol[i] != '\0';i++){// searching left node if its there we continue from left.
            if(traverse->left->token.symbol[i] == tokenChar){ // if we found it
                traverse = traverse->left; // move to left
                tokenBinary += "0"; // add 0 to binary value
                flag = 1; // set flag to 1 for not moving right.
                break; // we break the loop and continue from next node
            }
        }
        if(flag == 0){ // if we did not encounter our char in the left then it must be on the right.
            traverse = traverse->right; // move to right
            tokenBinary += "1"; // add 1 to binary value
        }
    }

    return tokenBinary;
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    
    for(int i = 0; password[i] != '\0';i++){ // until the every element of the password will be encoded we continue these processes.
        string temp = getTokenBinary(password[i],huffmanTree.root,""); // we create a binary value for the given character.
        this->encodedValPassword += temp.length() + '0'; // to converte the size of the lenght to string we add zero's ascii value and add it to the string as a char after that we add the size of the binary value to this array to if needed to decode this password . 
        this->encodedBinaryPassword += temp; // we add this binary value to full version of the binary password.
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    int size = 0;
    int start = 0;// this value keeps the head of where we left.
    string s;
    for(int i=0; encodedValPassword[i] != '\0';i++){ // size of this string is equal the letter in the password.
        s = ""; // we create an empty string.
        start += size; // we adjust our start.
        size = encodedValPassword[i] - '0';  // we get the size of the binary value by getting it from valpassword. we use - '0' to convert that char to int.
        for(int j = 0; j < size; j++){ 
            s += encodedBinaryPassword[start+j]; // we get the binary value of the letter.
        }
        decodeToken(s); // we send it to this function to find the letter and add it to the decodedPassword.
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){    
        Node* temp = this->huffmanTree.root; // we create a temporary pointer to traverse through tree.
        for(int i = 0; encodedToken[i] != '\0'; i++){ // until the end of the token
            if(encodedToken[i] == '0'){ // if it is zero which means left side of the tree we go that way
                temp = temp->left;
            }
            else{ // if it is not zero so it must be one and it is right side of the tree
                temp = temp->right;
            }
        }
        // we reached the encoded character and add it to the decoded password.
        decodedPassword += temp->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};