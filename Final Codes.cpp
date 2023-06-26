#include <iostream>
#include <fstream>
using namespace std;

// Function to draw the tic-tac-toe board
void draw_board(char board[][4], int size) {
    // Draw top border
    cout << "_";
    for (int j = 0; j < size; j++) {
        cout << "____";
    }
    cout << endl;

    // Draw rows
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|" << endl;

        // Draw row separator
        cout << "_";
        for (int j = 0; j < size; j++) {
            cout << "____";
        }
        cout << endl;
    }
}


// Function to check if the game is over and return the winner
char check_winner(char board[][4], int size) {
    // Check rows
    for (int i = 0; i < size; i++) {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (size == 4 && board[i][1] != '-' && board[i][1] == board[i][2] && board[i][2] == board[i][3]) {
            return board[i][1];
        }
    }

    // Check columns
    for (int j = 0; j < size; j++) {
        if (board[0][j] != '-' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
        if (size == 4 && board[1][j] != '-' && board[1][j] == board[2][j] && board[2][j] == board[3][j]) {
            return board[1][j];
        }
    }

    // Check diagonals
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (size == 4 && board[1][1] != '-' && board[1][1] == board[2][2] && board[2][2] == board[3][3]) {
        return board[1][1];
    }
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    if (size == 4 && board[1][2] != '-' && board[1][2] == board[2][1] && board[2][1] == board[3][0]) {
        return board[1][2];
    }

    // Check for a tie
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') {
                return '-';
            }
        }
    }

    return 'T';
}

// Function to get the next move from the player
void get_move(char board[][4], int size, char player) {
    int row, col;

    cout << "Player " << player << "'s turn." << endl;
    while (true) {
        cout << "Enter row and column (e.g. 1 2): ";
        cin >> row >> col;

	        // Check if the input is valid
        if (row < 1 || row > size || col < 1 || col > size) {
            cout << "Invalid input. Try again." << endl;
        } else if (board[row-1][col-1] != '-') {
            cout << "Cell is already occupied. Try again." << endl;
        } else {
            board[row-1][col-1] = player;
            break;
        }
    }
}

// Function to suggest the next recommended move that will likely win
void suggest_move(char board[][4], int size) {
    // Check all possible moves and see which one leads to a win
    char player = 'X';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-') {
                board[i][j] = player;
                if (check_winner(board, size) == player) {
                    cout << "Suggested move: " << i+1 << " " << j+1 << endl;
                    board[i][j] = '-';
                    return;
                }
                board[i][j] = '-';
            }
        }
    }

    cout << "No suggested move." << endl;
}

// Function to save the game to a file
void save_game(char board[][4], int size, char player) {
    ofstream file;
    file.open("tictactoe_save.txt");
    file << size << endl;
    file << player << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file << board[i][j];
        }
        file << endl;
    }
    file.close();
}

// Function to load a saved game from a file
void load_game(char board[][4], int& size, char& player) {
    ifstream file;
    file.open("tictactoe_save.txt");
    file >> size;
    file >> player;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> board[i][j];
        }
    }
    file.close();
}

int main() {
    int size;
    char board[4][4];
    char player = 'X';
    char winner = '-';
char choice;
string name_1, name_2 ;

//Get players’ names
cout<<"======"<<"Welcome to Tic Tac Toe!"<<"======"<<endl;
cout<< "Please enter player 1 name:"<<endl;
cin>> name_1;
cout<<"Hi"<<" "<<name_1<<" "<<"! you are player X"<<endl;
cout<< "Please enter player 2 name:"<<endl;
cin>>name_2;
cout<<"Hi"<<" "<<name_2<<" "<<"! you are player O"<<endl;;

    // Get the board size from the user
    cout << "Select board size (3 or 4): ";
    cin >> size;

    // Check if a saved game exists
    ifstream file("tictactoecpp_save.txt");
    if (file.good()) {
        cout << "Do you want to load the saved game? (y/n): ";
        cin >> choice;
        if (choice == 'y') {
            load_game(board, size, player);
            winner = check_winner(board, size);
        }
    }

    // Initialize the board with empty cells
    if (winner == '-') {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = '-';
            }
        }
    }

    // Loop until there's a winner or the board is full
    while (winner == '-') {
        // Draw the board
        draw_board(board, size);

        // Get the player's move
        get_move(board, size, player);
        
        // Suggest the next move
    suggest_move(board, size);

        // Check for a winner
        winner = check_winner(board, size);

        // Switch to the other player
       if (player == 'X') {
            player = 'O';
        } else {
            player = 'X';
        }
    }

    // Print the winner or tie message	
    draw_board(board, size);
    if (winner == 'X' || winner == 'O') {
        cout << "Congrats! Player " << winner << " wins!" << endl;
    }
    else{
        cout << "It's a tie!" << endl;
    }
    

    

    // Ask if the player wants to save the game
    cout << "Do you want to save the game? (y/n): ";
    cin >> choice;
    if (choice == 'y') {
        save_game(board, size, player);
    }
        else 
        cout<<"Hope you had a good game!";
    

    return 0;
}