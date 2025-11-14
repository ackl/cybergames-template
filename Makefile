CXX=g++-15
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic
TARGET := cybergame.fun
SRC := main.cpp

TEST_TARGET := cybergame_tests
TEST_SRC := tests/parse_board_test.cpp
OBJ_DIR := build
MAIN_OBJ := $(OBJ_DIR)/main.o
MUNIT_OBJ := $(OBJ_DIR)/munit.o

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MAIN_OBJ): $(SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -DCYBERGAME_TESTING -c $(SRC) -o $@

$(MUNIT_OBJ): vendor/munit/munit.c | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -Ivendor/munit -c $< -o $@

$(TEST_TARGET): $(MAIN_OBJ) $(MUNIT_OBJ) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -I. -Ivendor/munit $(TEST_SRC) $(MAIN_OBJ) $(MUNIT_OBJ) -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)
	rm -rf $(OBJ_DIR)
