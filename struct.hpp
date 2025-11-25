#ifndef STRUCT_HPP
#define STRUCT_HPP
#include<iostream>
#include<vector>
#include <cstdlib>   // for rand(), srand()
#include <ctime>  
#include <queue>
using namespace std;
struct Node {
    string name;       // player or winner name
    string matchId;    // example: "M1", "M2", etc.
    Node* left;        // left child (player or match)
    Node* right;       // right child (player or match)

    Node(string n = "") {
        name = n;
        matchId = "";
        left = right = nullptr;
    }
};




#endif