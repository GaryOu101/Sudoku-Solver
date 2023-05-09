#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <queue>
#include "operators.h"
#include "node.h"

using namespace std;

class algorithms {
  public:
    // Class Members
    vector < vector<int> > goalState;

    // Class Methods
    void solve(vector< vector<int> >, int);
    int misplacedTileCost(vector< vector<int> >);
    int euclideanDistanceCost(vector< vector<int> >);
    void printPuzzle(vector< vector<int> >);
    bool checkTraversed(vector< vector<int> >, vector<node> expanded);
};

// Solve puzzle
void algorithms::solve(vector< vector<int> >puzzle, int algChoice) {
  // Initialize goal state
  goalState.resize(3);
  goalState.at(0).push_back(1);
  goalState.at(0).push_back(2);
  goalState.at(0).push_back(3);
  goalState.at(1).push_back(4);
  goalState.at(1).push_back(5);
  goalState.at(1).push_back(6);
  goalState.at(2).push_back(7);
  goalState.at(2).push_back(8);
  goalState.at(2).push_back(0);

  // Initialize start node
  node curr(puzzle);

  // Initialize frontier queue
  priority_queue<node, vector<node>, node::increasing> frontier;
  frontier.push(curr);
  
  // Initialize expanded set
  vector<node> expanded;
  expanded.push_back(curr);
  
  while(!frontier.empty()){
    cout << "Board at the top of frontier" << endl;
    node* n;
    n = new node(frontier.top());
    
    printPuzzle(frontier.top().puzzle);

    if(goalState == frontier.top().puzzle){
      cout << "Found goal state!" << endl;
      printPuzzle(frontier.top().puzzle);
      return; 
    }
    frontier.pop();
    expanded.push_back(*n);

    // Move the puzzle in all 4 directions
    node* node_d = new node(moveDown(n->puzzle), n->g_n++); 
    node* node_u = new node(moveUp(n->puzzle), n->g_n++);
    node* node_l = new node(moveLeft(n->puzzle), n->g_n++);
    node* node_r = new node(moveRight(n->puzzle), n->g_n++);

    // Check if we are using heuristic functions
    if (algChoice == 2) { // Using misplaced tile
      node_d->h_n = misplacedTileCost(node_d->puzzle);
      node_u->h_n = misplacedTileCost(node_u->puzzle);
      node_l->h_n = misplacedTileCost(node_l->puzzle);
      node_r->h_n = misplacedTileCost(node_r->puzzle);
    }
    else if (algChoice == 3) { // Using euclidean distance
      node_d->h_n = euclideanDistanceCost(node_d->puzzle);
      node_u->h_n = euclideanDistanceCost(node_u->puzzle);
      node_l->h_n = euclideanDistanceCost(node_l->puzzle);
      node_r->h_n = euclideanDistanceCost(node_r->puzzle);
    }

    // We now check if we already visited each of these nodes and push to queue if not
    if(!checkTraversed(node_d->puzzle, expanded)){  
      node_d->parent = n; 
      n->downChild = node_d;
      frontier.push(*node_d);

      cout <<"Pushed a board to queue: down" << endl;
      printPuzzle(node_d->puzzle);
    }
    if(!checkTraversed(node_u->puzzle, expanded)){
      node_u->parent = n;
      n->upChild = node_u;
      frontier.push(*node_u);

      cout <<"Pushed a board to queue: up" << endl;
      printPuzzle(node_u->puzzle);
    }
    if(!checkTraversed(node_r->puzzle, expanded)){
      node_r->parent = n;
      n->rightChild = node_r;
      frontier.push(*node_r);

      cout <<"Pushed a board to queue: right" << endl;
      printPuzzle(node_r->puzzle);
    }
    if(!checkTraversed(node_l->puzzle, expanded)){
      node_l->parent = n;
      n->leftChild = node_l;
      frontier.push(*node_l);

      cout <<"Pushed a board to queue: left" << endl;
      printPuzzle(node_l->puzzle);
    }
  }
}

// Calculate heuristic cost using misplaced tile heuristic
int algorithms::misplacedTileCost(vector< vector<int> > puzzle) {
  int missed_tiles = 0;
  int count = 1;
  for (int i =0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(puzzle[i][j] == 0){
        //do nothing
      }
      else if (puzzle[i][j] != count){
        missed_tiles++;
      }
      count++;
    }
  }
  return missed_tiles;
}

// Calculate heuristic cost using euclidean distance heuristic
int algorithms::euclideanDistanceCost(vector< vector<int> > puzzle) {
  int distance_cost = 0;
  int horizontal = 0;
  int vertical = 0;
  for (unsigned i = 0; i < 3; ++i) {
    for (unsigned j = 0; j < 3; ++j) {
      // Calculate horizontal distance needed to travel to correct spot
      if (puzzle.at(i).at(j) % 3 == 1) { // Current piece belongs in column 1
        if (j == 0) horizontal = 0;
        else if (j == 1) horizontal = 1;
        else horizontal = 2;
      }
      else if (puzzle.at(i).at(j) % 3 == 2) { // Current piece belongs in column 2
        if (j == 0) horizontal = 1;
        else if (j == 1) horizontal = 0;
        else horizontal = 1;
      }
      else { // Current piece belongs in column 3
        if (j == 0) horizontal = 2;
        else if (j == 1) horizontal = 1;
        else horizontal = 0;
      }
      // Calculate vertical distance needed to travel to correct spot
      if (puzzle.at(i).at(j) >= 1 && puzzle.at(i).at(j) <= 3) { // Current piece belongs in row 1
        if (i == 0) vertical = 0;
        else if (i == 1) vertical = 1;
        else vertical = 2;
      }
      else if (puzzle.at(i).at(j) >= 4 && puzzle.at(i).at(j) <= 6) { // Current piece belongs in row 2
        if (i == 0) vertical = 1;
        else if (i == 1) vertical = 0;
        else vertical = 1;
      }
      else { // Current piece belongs in row 3
        if (i == 0) vertical = 2;
        else if (i == 1) vertical = 1;
        else vertical = 0;
      }
      distance_cost += (horizontal + vertical);
    }
  }

  return distance_cost;
}

// Output current puzzle
void algorithms::printPuzzle(vector< vector<int> > puzzle) {
  for (unsigned i = 0; i < 3; i++) {
    for (unsigned j = 0; j < 3; j++) {
      cout << puzzle.at(i).at(j) << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

// Check if current node is in the expanded set
bool algorithms::checkTraversed(vector< vector<int> > puzzle, vector<node> expanded){
  for(int i = 0; i < expanded.size();i++){
    printPuzzle(expanded[i].puzzle);
    if(expanded[i].puzzle == puzzle){
        return true;
    }
  } 
  return false;

}

#endif
