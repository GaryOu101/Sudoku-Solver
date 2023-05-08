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
    bool checkTraversed(vector<vector<int>>, vector<node> expanded);
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
  
  int count2 = 0;
  while(!frontier.empty()){
    count2++;
    cout <<"Board at the top of frontier" << endl;
    node* n;
    n = new node(frontier.top());
    
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
        cout<< frontier.top().puzzle.at(i).at(j);
      }
       cout << endl;
    }

    if(goalState == frontier.top().puzzle){
      cout << "Found goal state!" << endl;
      return; 
    }
    frontier.pop();
    expanded.push_back(*n);

    node* node_d = new node(moveDown(n->puzzle), n->uniform_cost++); //first we move the puzzle in all 4 directions
    node* node_u = new node(moveUp(n->puzzle), n->uniform_cost++);
    node* node_l = new node(moveLeft(n->puzzle), n->uniform_cost++);
    node* node_r = new node(moveRight(n->puzzle), n->uniform_cost++);

    if(!checkTraversed(node_d->puzzle, expanded)){  //we then check if we already visited this node for each 4 children and push to queue if not
      node_d->parent = n; 
      n->downChild = node_d;
      frontier.push(*node_d);
      cout <<"Pushed a board to queue: down" << endl;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          cout<< node_d->puzzle.at(i).at(j);
        }
        cout << endl;
      }
    }
      if(!checkTraversed(node_u->puzzle, expanded)){
      node_u->parent = n;
      n->upChild = node_u;
      frontier.push(*node_u);

      cout <<"Pushed a board to queue: up" << endl;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          cout<< node_u->puzzle.at(i).at(j);
        }
        cout << endl;
      }
    }
      if(!checkTraversed(node_r->puzzle, expanded)){
      node_r->parent = n;
      n->rightChild = node_r;
      frontier.push(*node_r);

      cout <<"Pushed a board to queue: right" << endl;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          cout<< node_r->puzzle.at(i).at(j);
        }
        cout << endl;
      }
    }
      if(!checkTraversed(node_l->puzzle, expanded)){
      node_l->parent = n;
      n->leftChild = node_l;
      frontier.push(*node_l);

      cout <<"Pushed a board to queue: left" << endl;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          cout<< node_l->puzzle.at(i).at(j);
        }
        cout << endl;
      }
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

bool algorithms::checkTraversed(vector<vector<int>> puzzle, vector<node> expanded){
  for(int i = 0; i < expanded.size();i++){
    printPuzzle(expanded[i].puzzle);
    if(expanded[i].puzzle == puzzle){
        return true;
    }
  } 
  return false;

}

#endif
