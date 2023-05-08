#ifndef OPERATORS_H_
#define OPERATORS_H_

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> board; //3x3 board with 2d vectors


board swapNum(int zero_r, int zero_c, int num2_r, int num2_c, board puzzle){ //swaps pos of zero and number
    puzzle[zero_r][zero_c] = puzzle[num2_r][num2_c];
    puzzle[num2_r][num2_c] = 0;
    return puzzle; 
}

board moveDown(board puzzle){
    int zero_row = 0;
    int zero_col = 0;
    
    //locate where the 0 is on the board
    for(int i = 0; i < 3; i++){
        if(puzzle[0][i] == 0){
                return puzzle; //do nothing bc shifting down does nothing to 0 on top row
        }
    }
    // 0 is not in top row

    for(int i = 1; i < 3; i++){ //now check if middle or bottom row
        for(int j = 0; j < 3; j++){
            if(puzzle[i][j] == 0){
                zero_row = i;
                zero_col = j;
            }
        } 
    }
    return swapNum(zero_row, zero_col, zero_row -1, zero_col, puzzle);
 }

board moveUp(board puzzle){
    int zero_row = 0;
    int zero_col = 0;
    

    for(int i = 0; i < 3; i++){ //check if 0 is in the bottom row
        if(puzzle[2][i] == 0){ 
                return puzzle; // do nothing 
        }
    }
    for(int i = 1; i < 2; i++){ //find where 0 is
        for(int j = 0; j < 3; j++){
            if(puzzle[i][j] == 0){
                zero_row = i;
                zero_col = j;
            }
        } 
    }
    return swapNum(zero_row, zero_col, zero_row + 1, zero_col, puzzle);
}

board moveLeft(board puzzle){
    int zero_row = 0;
    int zero_col = 0;
    
    for(int i = 0; i < 3; i++){ //check if on right
        if(puzzle[i][2] == 0){
                return puzzle; //do nothing bc 
        }
    }

    for(int i = 1; i < 3; i++){ //now check if middle or bottom row
        for(int j = 0; j < 3; j++){
            if(puzzle[i][j] == 0){
                zero_row = i;
                zero_col = j;
            }
        } 
    }
    return swapNum(zero_row, zero_col, zero_row, zero_col + 1, puzzle);
}


board moveRight(board puzzle){
    int zero_row = 0;
    int zero_col = 0;
    

    for(int i = 0; i < 3; i++){
        if(puzzle[i][2] == 0){
                return puzzle; //do nothing 
        }
    }

    for(int i = 1; i < 3; i++){ 
        for(int j = 0; j < 3; j++){
            if(puzzle[i][j] == 0){
                zero_row = i;
                zero_col = j;
            }
        } 
    }
    return swapNum(zero_row, zero_col, zero_row, zero_col - 1, puzzle);
}


#endif 