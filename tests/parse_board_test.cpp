#include "game.hpp"
#include "vendor/munit/munit.h"

static MunitResult test_horizontal_win(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[0][0] = 1;
  board[0][1] = 1;
  board[0][2] = 1;
  munit_assert_int(parseBoard(board), ==, 1);
  return MUNIT_OK;
}

static MunitResult test_vertical_win(const MunitParameter[], void *) {
  P = 2;
  K = 4;
  int board[M][N] = {};
  board[1][5] = 2;
  board[2][5] = 2;
  board[3][5] = 2;
  board[4][5] = 2;
  munit_assert_int(parseBoard(board), ==, 2);
  return MUNIT_OK;
}

static MunitResult test_diagonal_down_right(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[0][0] = 1;
  board[1][1] = 1;
  board[2][2] = 1;
  munit_assert_int(parseBoard(board), ==, 1);
  return MUNIT_OK;
}

static MunitResult test_diagonal_down_left(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[0][2] = 2;
  board[1][1] = 2;
  board[2][0] = 2;
  munit_assert_int(parseBoard(board), ==, 2);
  return MUNIT_OK;
}

static MunitResult test_no_win(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[0][0] = 1;
  board[0][1] = 2;
  board[0][2] = 1;
  munit_assert_int(parseBoard(board), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_empty_board(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  munit_assert_int(parseBoard(board), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_large_p_and_k(const MunitParameter[], void *) {
  P = 4;
  K = 5;
  int board[M][N] = {};
  for (int i = 0; i < K; ++i) {
    board[i][0] = 4;
  }
  munit_assert_int(parseBoard(board), ==, 4);
  return MUNIT_OK;
}

static MunitResult test_negative_values(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[0][0] = -1;
  board[0][1] = -1;
  board[0][2] = -1;
  munit_assert_int(parseBoard(board), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_player_beyond_p(const MunitParameter[], void *) {
  P = 2;
  K = 3;
  int board[M][N] = {};
  board[5][0] = 3;
  board[5][1] = 3;
  board[5][2] = 3;
  munit_assert_int(parseBoard(board), ==, 0);
  return MUNIT_OK;
}

static MunitResult test_k_longer_than_dimension(const MunitParameter[],
                                                void *) {
  P = 2;
  K = N + 1;
  int board[M][N] = {};
  for (int n = 0; n < N; ++n) {
    board[0][n] = 1;
  }
  munit_assert_int(parseBoard(board), ==, 0);
  return MUNIT_OK;
}

static MunitTest parse_board_tests[] = {
    {(char *)"/horizontal", test_horizontal_win, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/vertical", test_vertical_win, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/diagonal/down-right", test_diagonal_down_right, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/diagonal/down-left", test_diagonal_down_left, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/no-win", test_no_win, nullptr, nullptr, MUNIT_TEST_OPTION_NONE,
     nullptr},
    {(char *)"/empty-board", test_empty_board, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/large-pk", test_large_p_and_k, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/negative-values", test_negative_values, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/player-beyond-p", test_player_beyond_p, nullptr, nullptr,
     MUNIT_TEST_OPTION_NONE, nullptr},
    {(char *)"/k-longer-than-dimension", test_k_longer_than_dimension, nullptr,
     nullptr, MUNIT_TEST_OPTION_NONE, nullptr},
    {nullptr, nullptr, nullptr, nullptr, MUNIT_TEST_OPTION_NONE, nullptr}};

static const MunitSuite suite = {(char *)"/parse-board", parse_board_tests,
                                 nullptr, 1, MUNIT_SUITE_OPTION_NONE};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, nullptr, argc, argv);
}
