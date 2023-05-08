#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

class algorithms {
  public:
    void solve(vector< vector<int> >, int);
    int misplacedTileCost(vector< vector<int> >);
    int euclideanDistanceCost(vector< vector<int> >);
};

// Solve puzzle
void algorithms::solve(vector< vector<int> >puzzle, int algChoice) {
  cout << "Algorithm Used: " << algChoice << endl;
}

// Calculate heuristic cost using misplaced tile heuristic
int algorithms::misplacedTileCost(vector< vector<int> > puzzle) {
  return 0;
}

// Calculate heuristic cost using euclidean distance heuristic
int algorithms::euclideanDistanceCost(vector< vector<int> >) {
  return 0;
}

#endif
