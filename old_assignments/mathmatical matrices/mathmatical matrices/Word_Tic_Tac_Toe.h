//describtion for "Game Four" is an engaging and interactive word-based strategy game
// that challenges players to think critically and plan their moves carefully. 
// Played on a 3x3 grid, the objective is to form valid three-letter words using 
// entries from a preloaded dictionary. At least two players are required, with the 
// option to add more for a competitive multiplayer experience. During each turn, 
// a player selects a position on the board, places a letter, and attempts to create 
// a valid word in a row, column, or diagonal. The game rewards both quick thinking 
// and strategic planning, as players must anticipate their opponents? moves while
// forming their own winning combinations. Victory is declared when a player successfully 
// forms a valid word, while a full board with no winners results in a draw. "Game Four" 
// combines the thrill of wordplay with the excitement of a competitive strategy game,
// making it a fun and intellectually stimulating experience for players of all ages and 
// skill levels.





//this is what int main for game four looks like ->
//
//#include "BoardGame_Classes4.h";
//
//int main() {
//    loadDictionary();
//
//    GameManager game;
//    game.play();
//
//    return 0;
//}



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// --- Global Variables ---
vector<string> threecharwords; // Stores valid 3-character words
vector<vector<char>> board{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// --- Dictionary Loader ---
void loadDictionary() {
    ifstream file("dic.txt");
    string word;

    if (file.is_open()) {
        while (file >> word) {
            if (word.length() == 3) {
                threecharwords.push_back(word);
            }
        }
        file.close();
    }
    else {
        cerr << "Unable to open the dictionary file.\n";
    }
}

// --- Game Manager ---
class GameManager {
private:
    vector<string> players; // List of player names
    size_t currentPlayerIndex = 0; // Current player's turn

public:
    GameManager() {
        // Initialize players dynamically
        string playerName;
        cout << "Enter player names (type 'done' to finish):\n";
        while (true) {
            cout << "Player " << players.size() + 1 << ": ";
            cin >> playerName;
            if (playerName == "done") {
                if (players.size() < 2) {
                    cout << "At least 2 players are required.\n";
                    continue;
                }
                break;
            }
            players.push_back(playerName);
        }
    }

    void displayBoard() const {
        for (const auto& row : board) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    bool makeMove(const string& player) {
        int position;
        cout << player << "'s turn. Enter position (1-9): ";
        cin >> position;

        if (position < 1 || position > 9) {
            cout << "Invalid position. Please choose a number between 1 and 9.\n";
            return false;
        }

        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        // Check if the position is valid
        if (board[row][col] >= '1' && board[row][col] <= '9') {
            char letter;
            cout << "Enter your letter (A-Z): ";
            cin >> letter;

            // Ensure the letter is uppercase
            if (letter < 'A' || letter > 'Z') {
                cout << "Invalid letter. Please enter an uppercase letter between A and Z.\n";
                return false;
            }

            board[row][col] = letter;
            return true;
        }
        else {
            cout << "Spot is already taken. Try again.\n";
            return false;
        }
    }

    bool checkWin() const {
        // Check rows
        for (int i = 0; i < 3; i++) {
            string row = "";
            for (int j = 0; j < 3; j++) {
                row += board[i][j];
            }
            if (find(threecharwords.begin(), threecharwords.end(), row) != threecharwords.end()) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < 3; i++) {
            string col = "";
            for (int j = 0; j < 3; j++) {
                col += board[j][i];
            }
            if (find(threecharwords.begin(), threecharwords.end(), col) != threecharwords.end()) {
                return true;
            }
        }

        // Check diagonals
        string diag1 = "", diag2 = "";
        for (int i = 0; i < 3; i++) {
            diag1 += board[i][i];
            diag2 += board[i][2 - i];
        }
        if (find(threecharwords.begin(), threecharwords.end(), diag1) != threecharwords.end() ||
            find(threecharwords.begin(), threecharwords.end(), diag2) != threecharwords.end()) {
            return true;
        }

        return false;
    }

    bool checkDraw() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell >= '1' && cell <= '9') {
                    return false;
                }
            }
        }
        return true;
    }

    void play() {
        while (true) {
            displayBoard();
            string currentPlayer = players[currentPlayerIndex];

            if (!makeMove(currentPlayer)) {
                continue;
            }

            if (checkWin()) {
                displayBoard();
                cout << currentPlayer << " wins!\n";
                break;
            }

            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            // Switch to the next player
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }
};




//
//
//
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <algorithm>
//#include <ctime>
//#include <cstdlib>
//
//using namespace std;
//
//// --- Global Variables ---
//vector<string> threecharwords; // Stores valid 3-character words
//vector<vector<char>> board{
//    {'1', '2', '3'},
//    {'4', '5', '6'},
//    {'7', '8', '9'}
//};
//
//// --- Dictionary Loader ---
//void loadDictionary() {
//    ifstream file("dic.txt");
//    string word;
//
//    if (file.is_open()) {
//        while (file >> word) {
//            if (word.length() == 3) {
//                threecharwords.push_back(word);
//            }
//        }
//        file.close();
//    }
//    else {
//        cerr << "Unable to open the dictionary file.\n";
//    }
//}
//
//// --- Abstract Board Class ---
//template<typename T>
//class Board {
//protected:
//    int rows;
//    int columns;
//    vector<vector<T>> board;
//    int n_moves;
//public:
//    Board(int r, int c) : rows(r), columns(c), n_moves(0) {
//        board.resize(rows, vector<T>(columns));
//    }
//
//    virtual bool update_board(int x, int y, T symbol) = 0;
//    virtual void display_board() = 0;
//    virtual bool is_win() = 0;
//    virtual bool is_draw() = 0;
//    virtual bool game_is_over() = 0;
//};
//
//// --- Abstract Player Class ---
//template<typename T>
//class Player {
//protected:
//    string name;
//    T symbol;
//    Board<T>* boardPtr;
//public:
//    Player(string n, T s) : name(n), symbol(s), boardPtr(nullptr) {}
//
//    virtual void getmove(int& x, int& y) = 0;
//    T getsymbol() { return symbol; }
//    string getname() { return name; }
//    void setBoard(Board<T>* b) { boardPtr = b; }
//};
//
//// --- Random Player Class ---
//template<typename T>
//class RandomPlayer : public Player<T> {
//private:
//    int dimension;
//public:
//    RandomPlayer(string n, T s, int dim) : Player<T>(n, s), dimension(dim) {}
//
//    void getmove(int& x, int& y) override {
//        x = rand() % dimension;
//        y = rand() % dimension;
//    }
//};
//
//// --- GameManager Class ---
//class GameManager {
//private:
//    vector<string> players; // List of player names
//    size_t currentPlayerIndex = 0; // Current player's turn
//
//public:
//    GameManager() {
//        // Initialize players dynamically
//        string playerName;
//        cout << "Enter player names (type 'done' to finish):\n";
//        while (true) {
//            cout << "Player " << players.size() + 1 << ": ";
//            cin >> playerName;
//            if (playerName == "done") {
//                if (players.size() < 2) {
//                    cout << "At least 2 players are required.\n";
//                    continue;
//                }
//                break;
//            }
//            players.push_back(playerName);
//        }
//    }
//
//    void displayBoard() const {
//        for (const auto& row : board) {
//            for (char cell : row) {
//                cout << cell << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    bool makeMove(const string& player) {
//        int position;
//        cout << player << "'s turn. Enter position (1-9): ";
//        cin >> position;
//
//        if (position < 1 || position > 9) {
//            cout << "Invalid position. Please choose a number between 1 and 9.\n";
//            return false;
//        }
//
//        int row = (position - 1) / 3;
//        int col = (position - 1) % 3;
//
//        // Check if the position is valid
//        if (board[row][col] >= '1' && board[row][col] <= '9') {
//            char letter;
//            cout << "Enter your letter (A-Z): ";
//            cin >> letter;
//
//            // Ensure the letter is uppercase
//            if (letter < 'A' || letter > 'Z') {
//                cout << "Invalid letter. Please enter an uppercase letter between A and Z.\n";
//                return false;
//            }
//
//            board[row][col] = letter;
//            return true;
//        }
//        else {
//            cout << "Spot is already taken. Try again.\n";
//            return false;
//        }
//    }
//
//    bool checkWin() const {
//        // Check rows
//        for (int i = 0; i < 3; i++) {
//            string row = "";
//            for (int j = 0; j < 3; j++) {
//                row += board[i][j];
//            }
//            if (find(threecharwords.begin(), threecharwords.end(), row) != threecharwords.end()) {
//                return true;
//            }
//        }
//
//        // Check columns
//        for (int i = 0; i < 3; i++) {
//            string col = "";
//            for (int j = 0; j < 3; j++) {
//                col += board[j][i];
//            }
//            if (find(threecharwords.begin(), threecharwords.end(), col) != threecharwords.end()) {
//                return true;
//            }
//        }
//
//        // Check diagonals
//        string diag1 = "", diag2 = "";
//        for (int i = 0; i < 3; i++) {
//            diag1 += board[i][i];
//            diag2 += board[i][2 - i];
//        }
//        if (find(threecharwords.begin(), threecharwords.end(), diag1) != threecharwords.end() ||
//            find(threecharwords.begin(), threecharwords.end(), diag2) != threecharwords.end()) {
//            return true;
//        }
//
//        return false;
//    }
//
//    bool checkDraw() const {
//        for (const auto& row : board) {
//            for (char cell : row) {
//                if (cell >= '1' && cell <= '9') {
//                    return false;
//                }
//            }
//        }
//        return true;
//    }
//
//    void play() {
//        while (true) {
//            displayBoard();
//            string currentPlayer = players[currentPlayerIndex];
//
//            if (!makeMove(currentPlayer)) {
//                continue;
//            }
//
//            if (checkWin()) {
//                displayBoard();
//                cout << currentPlayer << " wins!\n";
//                break;
//            }
//
//            if (checkDraw()) {
//                displayBoard();
//                cout << "It's a draw!\n";
//                break;
//            }
//
//            // Switch to the next player
//            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
//        }
//    }
//};
//
//int main() {
//    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
//
//    loadDictionary();
//
//    GameManager game;
//    game.play();
//
//    return 0;
//}
//

