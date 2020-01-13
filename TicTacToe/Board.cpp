#include <iostream>
#include <vector>
#include <string>
#include "Board.h"
using namespace TicTacBoard;
using namespace std;

Board::Board(): board(3), gamewinner(0) {
    for (int i = 0; i<3; ++i){
        board[i] = {0, 0, 0};
    }
}


void Board::checkIfBoardFull(){
    //check if board full (but no one won)
    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            if (board[i][j] == 0){
                return;
            }
        }
    }
    gamewinner = 3;
    return;
}

void Board::checkIfSomeoneWon(){
    // check rows
    bool someone_won = false;
    int winner = 0;
    
    for (vector<int> row : board){
        bool won = true;
        winner = row[0];
        for (int i=0; i<3; ++i){
            if (row[i] != winner){
                won = false;
                break;
            }
        }
        if (won){
            someone_won = true;
        }
    }
    
    // check cols
    if (!someone_won){
        for (int col=0; col<3; ++col){
            winner = board[0][col];
            bool won = true;
            for (int row=0; row<3; ++row){
                if (board[row][col] != winner){
                    won = false;
                    break;
                }
            }
            if (won){
                someone_won = true;
            }
        }
    }
    // check diagonals
    if (!someone_won){
        //check L->R diagonal
        winner = board[0][0];
        bool won = true;
        for (int i=0; i<3; ++i){
            if (board[i][i] != winner){
                won = false;
                break;
            }
        }
        if (won){
            someone_won = true;
        }
    }
    if (!someone_won){
        //check R->L diagonal
        winner = board[0][2];
        bool won = true;
        for (int i=0; i<3; ++i){
            if (board[i][2-i] != winner){
                won = false;
                break;
            }
        }
        if (won){
            someone_won = true;
        }
    }
    
    if (someone_won){
        gamewinner = winner;
        return;
    }
}

bool Board::userMove(const int& row, const int& col){
    if (board[row][col] != 0){
        return false;
    }
    board[row][col] = 1;
    return true;
}


void Board::myMove(){
    // insert in any row/col/diagonal in which 2 slots are the same
        // either user is going to win, in which case I must be block
        // or I'm about to win
    
    // check rows
    for (vector<int> row : board){
        int zero_count = 0;
        int zero_index = 0;
        int one_count = 0;
        int two_count = 0;
        for (int i=0; i<3; ++i){
            if (row[i] == 0){
                ++zero_count;
                zero_index = i;
            }
            else if (row[i] == 1) ++one_count;
            else if (row[i] == 2) ++two_count;
        }
        if (zero_count == 1 && (one_count ==2 || two_count ==2)){
            row[zero_index] = 2;
            return;
        }
    }
    // check cols
    for (int col=0; col<3; ++col){
        int zero_count = 0;
        int zero_index = 0;
        int one_count = 0;
        int two_count = 0;
        for (int row=0; row<3; ++row){
            if(board[row][col] == 0){
                ++zero_count;
                zero_index = row;
            }
            else if (board[row][col] == 1) ++one_count;
            else if (board[row][col] == 2) ++two_count;
        }
        if (zero_count == 1 && (one_count == 2 || two_count == 2)){
            board[zero_index][col] = 2;
            return;
        }
    }
    
    // check L->R diagonal
    int zero_count = 0;
    int zero_index = 0;
    int one_count = 0;
    int two_count = 0;
    for (int i=0; i<3; ++i){
        if (board[i][i] == 0){
            ++zero_count;
            zero_index = i;
        }
        else if (board[i][i] == 1) ++one_count;
        else if (board[i][i] == 1) ++two_count;
    }
    if (zero_count == 1 && (one_count == 2 || two_count == 2)){
        board[zero_index][zero_index] = 2;
        return;
    }
    
    // check R->L diagonal
    zero_count = 0;
    zero_index = 0;
    one_count = 0;
    two_count = 0;
    for (int i=0; i<3; ++i){
        if (board[i][2-i] == 0){
            ++zero_count;
            zero_index = i;
        }
        else if (board[i][2-i] == 1) ++one_count;
        else if (board[i][2-i] == 1) ++two_count;
    }
    if (zero_count == 1 && (one_count == 2 || two_count == 2)){
        board[zero_index][2-zero_index] = 2;
        return;
    }
    
    //if theres no obvious win, just fill in the first empty slot
    for (int row=0; row<3; ++row){
        for (int col=0; col<3; ++col){
            if (board[row][col] == 0){
                board[row][col] = 2;
                return;
            }
        }
    }
}

int Board::getGamewinner() const{
    return gamewinner;
}

void Board::printBoard() const{
    for (int row=0; row<3; ++row){
        for (int col=0; col<3; ++col){
            if (board[row][col] == 1){
                cout << "O";
            }
            else if (board[row][col] == 2){
                cout << "X";
            }
            else if (board[row][col] == 0){
                cout << "-";
            }
            if (col != 2){
                cout << " | ";
            }
        }
        cout << endl;
    }
}
int main() {
    Board game = Board();
    game.printBoard();
    while (game.getGamewinner() == 0){
        bool move_made = false;
        while (!move_made){
            int row;
            cout << "Enter row number(1-3) for your move: ";
            cin >> row;
            --row;
            int col;
            cout << "Enter column number(1-3) for your move: ";
            cin >> col;
            --col;
            if (game.userMove(row, col) == false){
                cout << "Invalid row/column number. Try again, sorry." << endl;
            }
            else{
                move_made = true;
            }
        }
        game.printBoard();
        
        game.checkIfBoardFull();
        game.checkIfSomeoneWon();
        
        cout << "Computer Turn:" << endl;
        game.myMove();
        game.printBoard();
        game.checkIfBoardFull();
        game.checkIfSomeoneWon();
    }
    
    if (game.getGamewinner() == 1){
        cout << "Congrats! You won" << endl;
    }
    
    else if (game.getGamewinner() == 2){
        cout << ":( Computer won. Try again next time!" << endl;
    }
    
    else if (game.getGamewinner() == 3){
        cout << "Board full with no winner." << endl;
    }
}
