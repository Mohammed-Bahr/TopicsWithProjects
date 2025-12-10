////describe Pyramid Tic-Tac-Toe is a two-player strategy game played on a uniquely designed 
//// pyramid-shaped board consisting of 9 cells arranged across three rows. Players alternate 
//// turns, marking cells with their respective symbols ('X' or 'O'), aiming to create a winning 
//// pattern through diagonal, horizontal, or vertical alignment of their symbols. The game dynamically 
//// updates the board after every move and ensures valid gameplay by checking for valid indices and 
//// preventing overwrites. It concludes when one player achieves a winning pattern or all cells are 
//// filled, resulting in a draw. With its engaging mechanics and visual representation, the game offers 
//// a refreshing twist on traditional Tic-Tac-Toe.
//
//
//
////this is what main function looks like 
////#include "PyramidTicTacToe.h"
////
////int main() {
////    PyramidTicTacToe game;
////    game.start();
////    return 0;
////}
//
//
//
//#ifndef PYRAMIDTICTACTOE_H
//#define PYRAMIDTICTACTOE_H
//
//#include <iostream>
//#include <vector>
//#include <iomanip>
//
//using namespace std;
//
//// Base class for the game board
//class Board {
//protected:
//    vector<vector<char>> board;
//
//public:
//    Board() {
//        board = {
//            {'1'},
//            {'2', '3', '4'},
//            {'5', '6', '7', '8', '9'}
//        };
//    }
//
//    void printBoard() const {
//        int rows = board.size();
//        for (int i = 0; i < rows; ++i) {
//            cout << string((rows - i - 1) * 2, ' ');
//            for (char c : board[i]) {
//                cout << c << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    vector<vector<char>>& getBoard() {
//        return board;
//    }
//};
//
//// Derived class for handling game logic
//class GameLogic : public Board {
//protected:
//    bool checkWin(char player) {
//        auto& b = board;
//
//        if ((b[0][0] == player && b[1][1] == player && b[2][2] == player) ||
//            (b[2][0] == player && b[2][1] == player && b[2][2] == player) ||
//            (b[1][0] == player && b[1][1] == player && b[1][2] == player) ||
//            (b[2][1] == player && b[2][2] == player && b[2][3] == player) ||
//            (b[2][2] == player && b[2][3] == player && b[2][4] == player) ||
//            (b[0][0] == player && b[1][0] == player && b[2][0] == player) ||
//            (b[0][0] == player && b[1][2] == player && b[2][4] == player)) {
//            return true;
//        }
//        return false;
//    }
//
//    pair<int, int> getCoordinates(int index) {
//        if (index == 1) return { 0, 0 };
//        if (index >= 2 && index <= 4) return { 1, index - 2 };
//        if (index >= 5 && index <= 9) return { 2, index - 5 };
//        return { -1, -1 };
//    }
//};
//
//// Final class for managing the game
//class PyramidTicTacToe : public GameLogic {
//public:
//    void start() {
//        char currentPlayer = 'X';
//        int moves = 0;
//
//        cout << "Welcome to Pyramid Tic-Tac-Toe!\n";
//
//        while (true) {
//            printBoard();
//
//            cout << "Player " << currentPlayer << ", enter your move (index): ";
//            int index;
//            cin >> index;
//
//            pair<int, int> coords = getCoordinates(index);
//            int row = coords.first;
//            int col = coords.second;
//
//            if (row == -1 || col == -1 || board[row][col] == 'X' || board[row][col] == 'O') {
//                cout << "Invalid move. Try again.\n";
//                continue;
//            }
//
//            board[row][col] = currentPlayer;
//            moves++;
//
//            if (checkWin(currentPlayer)) {
//                printBoard();
//                cout << "Player " << currentPlayer << " wins the game!\n";
//                break;
//            }
//
//            if (moves == 9) {
//                printBoard();
//                cout << "The game is a draw!\n";
//                break;
//            }
//
//            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
//        }
//    }
//};
//
//#endif // PYRAMIDTICTACTOE_H











//describe Pyramid Tic-Tac-Toe is a two-player strategy game played on a uniquely designed 
// pyramid-shaped board consisting of 9 cells arranged across three rows. Players alternate 
// turns, marking cells with their respective symbols ('X' or 'O'), aiming to create a winning 
// pattern through diagonal, horizontal, or vertical alignment of their symbols. The game dynamically 
// updates the board after every move and ensures valid gameplay by checking for valid indices and 
// preventing overwrites. It concludes when one player achieves a winning pattern or all cells are 
// filled, resulting in a draw. With its engaging mechanics and visual representation, the game offers 
// a refreshing twist on traditional Tic-Tac-Toe.



//this is what int main looks like -> 

//#include <iostream>
//#include "PyramidTicTacToe.h"
//
//int main() {
//    int choice;
//    Player<char>* players[2];
//    PyramidBoard<char>* board = new PyramidBoard<char>();
//    string playerXName, playerOName;
//
//    cout << "Welcome to Pyramid Tic-Tac-Toe!\n";
//
//    // Setup Player X
//    cout << "Enter Player X name: ";
//    cin >> playerXName;
//    cout << "Choose Player X type:\n1. Human\n2. Random Computer\n";
//    cin >> choice;
//
//    if (choice == 1) {
//        players[0] = new HumanPlayer<char>(playerXName, 'X');
//    }
//    else {
//        players[0] = new RandomPlayer<char>(playerXName, 'X');
//    }
//
//    // Setup Player O
//    cout << "Enter Player O name: ";
//    cin >> playerOName;
//    cout << "Choose Player O type:\n1. Human\n2. Random Computer\n";
//    cin >> choice;
//
//    if (choice == 1) {
//        players[1] = new HumanPlayer<char>(playerOName, 'O');
//    }
//    else {
//        players[1] = new RandomPlayer<char>(playerOName, 'O');
//    }
//
//    // Run the game
//    GameManager<char> game(board, players[0], players[1]);
//    game.run();
//
//    return 0;
//}



#ifndef PYRAMIDTICTACTOE_H
#define PYRAMIDTICTACTOE_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Template-based board class
template<typename T>
class PyramidBoard {
private:
    vector<vector<T>> board;
    int n_moves;
    const int total_moves = 9;

public:
    PyramidBoard() : n_moves(0) {
        board = {
            {'1'},
            {'2', '3', '4'},
            {'5', '6', '7', '8', '9'}
        };
    }

    bool update_board(int x, int y, T symbol) {
        if (x < 0 || y < 0 || x >= board.size() || y >= board[x].size() || board[x][y] == 'X' || board[x][y] == 'O') {
            return false;
        }
        board[x][y] = symbol;
        ++n_moves;
        return true;
    }

    void display_board() const {
        int rows = board.size();
        for (int i = 0; i < rows; ++i) {
            cout << string((rows - i - 1) * 2, ' ');
            for (const auto& c : board[i]) {
                cout << c << " ";
            }
            cout << endl;
        }
    }

    bool is_win(T symbol) const {
        const auto& b = board;
        return (
            (b[0][0] == symbol && b[1][1] == symbol && b[2][2] == symbol) ||
            (b[2][0] == symbol && b[2][1] == symbol && b[2][2] == symbol) ||
            (b[1][0] == symbol && b[1][1] == symbol && b[1][2] == symbol) ||
            (b[2][1] == symbol && b[2][2] == symbol && b[2][3] == symbol) ||
            (b[2][2] == symbol && b[2][3] == symbol && b[2][4] == symbol) ||
            (b[0][0] == symbol && b[1][0] == symbol && b[2][0] == symbol) ||
            (b[0][0] == symbol && b[1][2] == symbol && b[2][4] == symbol)
            );
    }

    bool is_draw() const {
        return n_moves == total_moves;
    }

    bool game_is_over() const {
        return is_draw();
    }

    bool is_cell_empty(int x, int y) const {
        if (x < 0 || y < 0 || x >= board.size() || y >= board[x].size()) {
            return false;
        }
        return board[x][y] != 'X' && board[x][y] != 'O';
    }

};

// Template-based player class
template<typename T>
class Player {
protected:
    string name;
    T symbol;

public:
    Player(string name, T symbol) : name(name), symbol(symbol) {}
    virtual void get_move(int& x, int& y, PyramidBoard<T>& board) const = 0;
    T get_symbol() const { return symbol; }
    string get_name() const { return name; }
    virtual ~Player() = default;
};

// Human player class
template<typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void get_move(int& x, int& y, PyramidBoard<T>& board) const override {
        int index;
        cout << this->name << " (" << this->symbol << "), enter your move (index): ";
        cin >> index;

        if (index == 1) {
            x = 0; y = 0;
        }
        else if (index >= 2 && index <= 4) {
            x = 1; y = index - 2;
        }
        else if (index >= 5 && index <= 9) {
            x = 2; y = index - 5;
        }
        else {
            x = -1; y = -1;
        }
    }
};

// Random player class
template<typename T>
class RandomPlayer : public Player<T> {
public:
    RandomPlayer(string name, T symbol) : Player<T>(name, symbol) {
        srand(time(0));
    }

    void get_move(int& x, int& y, PyramidBoard<T>& board) const override {
        while (true) {
            x = rand() % 3; // Pyramid board has 3 rows
            y = rand() % (x + 1); // Each row has x+1 columns

            // Check for an empty cell without updating the board
            if (board.is_cell_empty(x, y)) {
                break;
            }
        }
    }
};


// Game manager class
template<typename T>
class GameManager {
private:
    PyramidBoard<T>* board;
    Player<T>* players[2];

public:
    GameManager(PyramidBoard<T>* board, Player<T>* player1, Player<T>* player2) : board(board) {
        players[0] = player1;
        players[1] = player2;
    }

    void run() {
        int current_player = 0;
        T winner_symbol = '\0';

        while (true) {
            board->display_board();
            int x, y;
            players[current_player]->get_move(x, y, *board);

            if (!board->update_board(x, y, players[current_player]->get_symbol())) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            if (board->is_win(players[current_player]->get_symbol())) {
                winner_symbol = players[current_player]->get_symbol();
                break;
            }

            if (board->is_draw()) {
                break;
            }

            current_player = 1 - current_player;
        }

        board->display_board();
        if (winner_symbol != '\0') {
            cout << "Player " << players[current_player]->get_name() << " (" << winner_symbol << ") wins!\n";
        }
        else {
            cout << "The game is a draw!\n";
        }
    }

    ~GameManager() {
        delete board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }
};

#endif // PYRAMIDTICTACTOE_H







