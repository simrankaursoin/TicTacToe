
#ifndef Board_h
#define Board_h
#include <iostream>
#include <vector>
#include <string>
namespace TicTacBoard{

    class Board{
    public:
        Board();
        
        void checkIfBoardFull();
        
        void checkIfSomeoneWon();
        
        bool userMove(const int& row, const int& col);
        
        void myMove();
            
        int getGamewinner() const;
        
        void printBoard() const;
        
    private:
        std::vector<std::vector<int> > board;
        int gamewinner;
        // Gamewinner:
            // 0 = no one won
            // 1 = user won
            // 2 = computer won
            // 3 = board full but no one won
    };
}
#endif /* Board_h */
