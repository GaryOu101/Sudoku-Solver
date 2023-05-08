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
int algorithms::euclideanDistanceCost(vector< vector<int> >) {
  return 0;
}

#endif
