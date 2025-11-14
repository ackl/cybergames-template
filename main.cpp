#include <bits/stdc++.h>
#include <cassert>
#include <iostream>

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

// Test helper to set up board and check winner
void testParseBoard() {
  // Test 1: Horizontal win for player 1
  P = 2;
  K = 3;
  int board1[M][N] = {0};
  board1[0][0] = 1;
  board1[0][1] = 1;
  board1[0][2] = 1;
  assert(parseBoard(board1) == 1);

  // Test 2: Vertical win for player 2
  P = 2;
  K = 4;
  int board2[M][N] = {0};
  board2[1][5] = 2;
  board2[2][5] = 2;
  board2[3][5] = 2;
  board2[4][5] = 2;
  assert(parseBoard(board2) == 2);

  // Test 3: Diagonal down-right win for player 1
  P = 2;
  K = 3;
  int board3[M][N] = {0};
  board3[0][0] = 1;
  board3[1][1] = 1;
  board3[2][2] = 1;
  assert(parseBoard(board3) == 1);

  // Test 4: Diagonal down-left win for player 2
  P = 2;
  K = 3;
  int board4[M][N] = {0};
  board4[0][2] = 2;
  board4[1][1] = 2;
  board4[2][0] = 2;
  assert(parseBoard(board4) == 2);

  // Test 5: No win
  P = 2;
  K = 3;
  int board5[M][N] = {0};
  board5[0][0] = 1;
  board5[0][1] = 2;
  board5[0][2] = 1;
  assert(parseBoard(board5) == 0);

  // Test 6: Out of bounds (should not crash)
  P = 2;
  K = 3;
  int board6[M][N] = {0};
  // No out-of-bounds access in parseBoard, so just check normal
  assert(parseBoard(board6) == 0);

  // Test 7: Large P and K
  P = 4;
  K = 5;
  int board7[M][N] = {0};
  for (int i = 0; i < K; ++i)
    board7[i][0] = 4;
  assert(parseBoard(board7) == 4);

  // Test 8: Negative values (should not win)
  P = 2;
  K = 3;
  int board8[M][N] = {0};
  board8[0][0] = -1;
  board8[0][1] = -1;
  board8[0][2] = -1;
  assert(parseBoard(board8) == 0);

  std::cout << "All parseBoard tests passed!" << std::endl;
}

int main(int argc, char *argv[]) {
  testParseBoard();

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
