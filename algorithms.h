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
}

// Calculate heuristic cost using misplaced tile heuristic
int algorithms::misplacedTileCost(vector< vector<int> > puzzle) {
  return 0;
}

// Calculate heuristic cost using euclidean distance heuristic
int algorithms::euclideanDistanceCost(vector< vector<int> >) {
  return 0;
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

#endif
