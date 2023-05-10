#ifndef NODE_H
#define NODE_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <queue>
#include "operators.h"

class node {
	public:
      // Parent
      node *parent;
      // Children
      node *downChild;
      node *upChild;
      node *rightChild;
      node *leftChild;
      // Costs
      int g_n;
      int h_n;
      // Puzzle
      vector< vector<int> > puzzle;

      // This helping struct allows us to store nodes in the priority queue in increasing g(n) + h(n) value
      struct increasing {
        bool operator()(node x, node y) {
         return (x.g_n + x.h_n) > (y.g_n + y.h_n);
        }
      };

      // Constructors
      node(vector< vector<int> > puzzle) { // Called for initial node
      	parent = nullptr;
      	downChild = nullptr;
      	upChild = nullptr;
      	rightChild = nullptr;
      	leftChild = nullptr;
      	g_n = 0;
      	h_n = 0;
      	this->puzzle = puzzle;
      }


      node(vector< vector<int> > puzzle, node* parent, int g_n){ // Creating child node
        this->puzzle = puzzle;
        this->parent = parent;
        this->g_n = g_n;
        h_n = 0; // Set this in case we are using uniform cost search, so h(n) doesn't get a junk value
      }
};

#endif