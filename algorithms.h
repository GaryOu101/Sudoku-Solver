#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include "operators.h"
#include "node.h"

using namespace std;

class algorithms {
  public:
    // Class Members
    vector < vector<int> > goalState;

    // Class Methods
    void astar(vector< vector<int> >, int);
    int misplacedTileCost(vector< vector<int> >);
    int euclideanDistanceCost(vector< vector<int> >);
    void printPuzzle(vector< vector<int> >);
    bool checkTraversed(vector< vector<int> >, vector<node> expanded);
};

// Solve puzzle
void algorithms::astar(vector< vector<int> >puzzle, int algChoice) {
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

  // If we are using heuristic functions, calculate initial h(n)
  if (algChoice == 2) { // Using misplaced tile
      curr.h_n = misplacedTileCost(curr.puzzle);
    }
  else if (algChoice == 3) { // Using euclidean distance
      curr.h_n = euclideanDistanceCost(curr.puzzle);
  }

  // Initialize frontier queue
  priority_queue<node, vector<node>, node::increasing> frontier;
  frontier.push(curr);
  int maxFrontier = frontier.size(); // Track maximum nodes in frontier at any given time
  
  // Initialize expanded set
  vector<node> expanded;
  expanded.push_back(curr);
  
  while(!frontier.empty()){
    node* n;
    n = new node(frontier.top());

    if (maxFrontier < frontier.size()) {
      maxFrontier = frontier.size();
    }
    
    // Check if next state to be expanded is the goal state
    if(goalState == frontier.top().puzzle){
      // We have reached goal state, now trace back to start node to see optimal path to goal
      stack<node> goal_path;
      node curr = frontier.top();
      while (curr.parent != NULL) {
        curr = *curr.parent;
        goal_path.push(curr);
      }
      int goal_depth = goal_path.size();
      while (!goal_path.empty()) {
        cout << "The best state to expand with g(n) = " << goal_path.top().g_n << " and h(n) = " << goal_path.top().h_n << " is..." << endl;
        printPuzzle(goal_path.top().puzzle);
        goal_path.pop();
      }
      cout << "Found goal state!" << endl;
      printPuzzle(goalState);
      cout << "To solve this problem the search algorithm expanded a total of " << expanded.size() << " nodes." << endl;
      cout << "The maximum number of nodes in the queue at any one time: " << maxFrontier << "." << endl;
      cout << "The depth of the goal node was " << (goal_depth + 1) << "." << endl;
      return; 
    }

    // Not goal state so expand it
    frontier.pop();
    expanded.push_back(*n);

    // Move the puzzle in all 4 directions
    node* node_d = new node(moveDown(n->puzzle), n, (n->g_n + 1)); 
    node* node_u = new node(moveUp(n->puzzle), n, (n->g_n + 1));
    node* node_l = new node(moveLeft(n->puzzle), n, (n->g_n + 1));
    node* node_r = new node(moveRight(n->puzzle), n, (n->g_n + 1));

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
      n->downChild = node_d;
      frontier.push(*node_d);
    }
    if(!checkTraversed(node_u->puzzle, expanded)){
      n->upChild = node_u;
      frontier.push(*node_u);
    }
    if(!checkTraversed(node_r->puzzle, expanded)){
      n->rightChild = node_r;
      frontier.push(*node_r);
    }
    if(!checkTraversed(node_l->puzzle, expanded)){
      n->leftChild = node_l;
      frontier.push(*node_l);
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
    if(expanded[i].puzzle == puzzle){
        return true;
    }
  } 
  return false;

}

#endif
