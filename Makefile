CXX=g++-15
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic

TARGET := cybergame
SRC := main.cpp

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
