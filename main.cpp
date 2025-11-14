#include "game.hpp"
#include <bits/stdc++.h>
#include <iostream>

// Default variables for number of players and win length
//
int P = 2;
int K = 5;

void initBoard(int board[M][N], int M, int N) {
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      board[m][n] = 0;
    }
  }
}

int parseBoard(int board[M][N]) {
  for (int p = 1; p <= P; ++p) {
    // Horizontal
    for (int m = 0; m < M; ++m) {
      for (int n = 0; n <= N - K; ++n) {
        bool win = true;
        for (int k = 0; k < K; ++k) {
          if (board[m][n + k] != p) {
            win = false;
            break;
          }
        }
        if (win)
          return p;
      }
    }
    // Vertical
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m <= M - K; ++m) {
        bool win = true;
        for (int k = 0; k < K; ++k) {
          if (board[m + k][n] != p) {
            win = false;
            break;
          }
        }
        if (win)
          return p;
      }
    }
    // Diagonal down-right
    for (int m = 0; m <= M - K; ++m) {
      for (int n = 0; n <= N - K; ++n) {
        bool win = true;
        for (int k = 0; k < K; ++k) {
          if (board[m + k][n + k] != p) {
            win = false;
            break;
          }
        }
        if (win)
          return p;
      }
    }
    // Diagonal down-left
    for (int m = 0; m <= M - K; ++m) {
      for (int n = K - 1; n < N; ++n) {
        bool win = true;
        for (int k = 0; k < K; ++k) {
          if (board[m + k][n - k] != p) {
            win = false;
            break;
          }
        }
        if (win)
          return p;
      }
    }
  }
  return 0;
}

void gameLoop(int board[M][N], bool cont) {
  int winner;
  int m, n;
  while (cont) {
    for (int p = 1; p <= P; ++p) {
      std::cout << "Player " << p << " place (row col): ";
      std::cin >> m >> n;
      if (m < 0 || m >= M || n < 0 || n >= N) {
        std::cout << "Out of bounds!" << std::endl;
        continue;
      }
      if (board[m][n] == 0) {
        std::cout << p << " at (" << m << ", " << n << ")." << std::endl;
        board[m][n] = p;
      } else {
        std::cout << "Illegal move!" << std::endl;
        continue;
      }
      winner = parseBoard(board);
      if (winner != 0) {
        std::cout << "Player " << winner << " has won!" << std::endl;
        cont = false;
        break;
      }
    }
  }
}

#ifndef CYBERGAME_TESTING
int main(int argc, char *argv[]) {
  if (argc >= 3) {
    P = std::atoi(argv[1]);
    K = std::atoi(argv[2]);
    std::cout << "Players: " << P << ", Win length: " << K << std::endl;
  } else {
    std::cout << "Initialising game... How many players? ";
    std::cin >> P;
    std::cout << "How many in a row to win? ";
    std::cin >> K;
  }

  int board[M][N];
  initBoard(board, M, N);
  gameLoop(board, true);

  return EXIT_SUCCESS;
}
#endif
