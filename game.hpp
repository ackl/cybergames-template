#pragma once

// Use integer arithmetic for board size
inline constexpr int M = 1 + (1 << 7); // 129
inline constexpr int N = 1 + (1 << 3); // 9

extern int P;
extern int K;

void initBoard(int board[M][N], int M, int N);
int parseBoard(int board[M][N]);
void gameLoop(int board[M][N], bool cont);
