#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>

// Use integer arithmetic for board size
const int M = 1 + (1 << 7); // 129

const int N = 1 + (1 << 3); // 9

// Default variables for number of players and win length
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
  /*
   * This function is where you should define your win conditions.
   * If player p in [1,...,P] has won, then you should return p; otherwise 0.
   * If you find yourself with a great deal of spare time you might try
   * rendering the board to the terminal here, too.
   */
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

int main(void) {
  int P;
  bool cont = true;
  if (argc < 1) {
    return EXIT_FAILURE;
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
