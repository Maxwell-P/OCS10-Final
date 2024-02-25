/*
File: TicTacToe.cpp
Author: Maxwell Palance
Last updated: 5/26/23
Description: This program is a tic-tac-toe game where a player can play against
a computer opponent, with options for two different difficulty modes, and the
game continues until there is a winner or a tie.
*/

#include <iostream>
using namespace std;

// Function to display the tic-tac-toe board.
void displayBoard(char board[3][3]) {
  cout << "-------------" << endl;
  for (int i = 0; i < 3; i++) {
    cout << "| ";
    for (int j = 0; j < 3; j++) {
      cout << board[i][j] << " | ";
    }
    cout << endl;
    cout << "-------------" << endl;
  }
}

// Function to check if any player has won.
bool checkWin(char board[3][3], char player) {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
      return true;
  }

  // Check columns.
  for (int j = 0; j < 3; j++) {
    if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
      return true;
  }

  // Check diagonals.
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    return true;

  if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    return true;

  return false;
}

// Function to make a move for the computer.
void makeComputerMove(char board[3][3], int mode) {
  // Check if the computer can win in the next move.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = 'O';
        if (checkWin(board, 'O'))
          return;
        else
          board[i][j] = ' ';
      }
    }
  }

  // Check if the user can win in the next move and block it.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        board[i][j] = 'X';
        if (checkWin(board, 'X')) {
          board[i][j] = 'O';
          return;
        } else {
          board[i][j] = ' ';
        }
      }
    }
  }
  // If the play mode is 1 (computer cannot lose), prioritize certain moves.
  // The computer will try to win if possible, otherwise, it will block the
  // user's winning move. Additionally, a specific strategy is employed when the
  // user selects the center position as their first move.
  if (mode == 1) {
    if (board[1][1] == 'X') {
      if (board[0][2] == ' ') {
        board[0][2] = 'O';
        return;
      }
      if (board[2][2] == ' ') {
        board[2][2] = 'O';
        return;
      }
      if (board[2][0] == ' ') {
        board[2][0] = 'O';
        return;
      }
      if (board[0][0] == ' ') {
        board[0][0] = 'O';
        return;
      }
    }
  }

  // If no winning move is possible, make a random move.
  int row, col;
  do {
    row = rand() % 3;
    col = rand() % 3;
  } while (board[row][col] != ' ');

  board[row][col] = 'O';
}

// Function to make a move for the user.
void makeUserMove(char board[3][3]) {
  int row, col;
  do {
    cout << "Enter the row and column (0-2) for your move (separate your "
            "inputted row and column by a space.): ";
    cin >> row >> col;
  } while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ');

  board[row][col] = 'X';
}

int main() {
  char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

  cout << "Tic-Tac-Toe Game" << endl;
  cout << "Player (X) - Computer (O)" << endl;
  cout << "Enter the play mode '1' for computer cannot lose and '0' for "
          "computer can lose: "
       << endl;
  int mode;
  cin >> mode;

  int moves = 0;
  bool gameOver = false;

  displayBoard(board);

  while (moves < 9 && !gameOver) {
    if (moves % 2 == 0)
      makeUserMove(board);
    else
      makeComputerMove(board, mode);

    displayBoard(board);

    if (checkWin(board, 'X')) {
      cout << "Congratulations! You won!" << endl;
      gameOver = true;
    } else if (checkWin(board, 'O')) {
      cout << "Sorry, the computer won!" << endl;
      gameOver = true;
    }

    moves++;
  }

  if (!gameOver)
    cout << "It's a tie!" << endl;

  return 0;
}