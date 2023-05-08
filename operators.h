#ifndef OPERATORS_H
#define OPERATORS_H

#include <iostream>
#include <vector>

using namespace std;

// Swaps 0 with another square
vector < vector<int> > swapPos(int zero_r, int zero_c, int num2_r, int num2_c, vector < vector<int> > puzzle) {
    puzzle.at(zero_r).at(zero_c) = puzzle.at(num2_r).at(num2_c);
    puzzle.at(num2_r).at(num2_c) = 0;
    return puzzle;
}

// Swaps 0 with space below it
vector < vector<int> > moveDown(vector < vector<int> > puzzle) {
    int zero_row = -1;
    int zero_col = -1;

    for (unsigned i = 0; i < 2; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (puzzle.at(i).at(j) == 0) {
                zero_row = i;
                zero_col = j;
            }
        }
    }

    // Zero not in valid column
    if (zero_row == -1) {
        return puzzle;
    }
    return swapPos(zero_row, zero_col, zero_row + 1, zero_col, puzzle);
}

// Swaps 0 with space above it
vector < vector<int> > moveUp(vector < vector<int> > puzzle) {
    int zero_row = -1;
    int zero_col = -1;

    for (unsigned i = 1; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (puzzle.at(i).at(j) == 0) {
                zero_row = i;
                zero_col = j;
            }
        }
    }

    // Zero not in valid column
    if (zero_row == -1) {
        return puzzle;
    }
    return swapPos(zero_row, zero_col, zero_row - 1, zero_col, puzzle);
}

// Swaps 0 with space right of it
vector < vector<int> > moveRight(vector <vector<int> > puzzle) {
    int zero_row = -1;
    int zero_col = -1;

    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 2; ++j) {
            if (puzzle.at(i).at(j) == 0) {
                zero_row = i;
                zero_col = j;
            }
        }
    }

    // Zero not in valid column
    if (zero_row == -1) {
        return puzzle;
    }
    return swapPos(zero_row, zero_col, zero_row, zero_col + 1, puzzle);
}

// Swaps 0 with space left of it
vector < vector<int> > moveLeft(vector < vector<int> > puzzle) {
    int zero_row = -1;
    int zero_col = -1;

    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 1; j < 3; ++j) {
            if (puzzle.at(i).at(j) == 0) {
                zero_row = i;
                zero_col = j;
            }
        }
    }

    // Zero not in valid column
    if (zero_row == -1) {
        return puzzle;
    }
    return swapPos(zero_row, zero_col, zero_row, zero_col - 1, puzzle);
}

#endif 