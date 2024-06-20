# Compiler: clang++
CXX=g++
# Compiler flags
CXXFLAGS=-std=c++17 -Wall -g
# Linker flags
LDFLAGS =-lsfml-graphics -lsfml-window -lsfml-system
# Valgrind flags
VALGRIND_FLAGS=--leak-check=full --show-leak-kinds=all --error-exitcode=99 --track-origins=yes --verbose --log-file=valgrind-out.txt
# Catan library source files
LIB_SRC = Board.cpp Cashbox.cpp Catan.cpp City.cpp Hexagon.cpp Player.cpp Point.cpp Settlement.cpp \
		Structure.cpp Trail.cpp Vertex.cpp Types.cpp KnightCard.cpp ProgressCard.cpp \
		VictoryPointCard.cpp

TEST_SRC = TestCounter.cpp Test.cpp

# Catan library object files
LIB_OBJ = $(subst .cpp,.o,$(LIB_SRC))
# Catan library header files
LIB_HDR = $(subst .cpp,.h,$(LIB_SRC))
# Catan library archive
LIB = libCatan.a
# Catan library archive path
#LIB_PATH = ../lib

# Doctest flags
DOCTEST_FLAGS = -std=c++11 -I doctest

all: Main Demo Test

Main: Main.o $(LIB)
	$(CXX) $(CXXFLAGS) -o Main Main.o $(LIB) $(LDFLAGS)

Demo: Demo.o $(LIB)
	$(CXX) $(CXXFLAGS) -o Demo Demo.o $(LIB) $(LDFLAGS)

Test: TestCounter.o Test.o $(LIB)
	$(CXX) $(CXXFLAGS) -o Test TestCounter.o Test.o $(LIB) $(LDFLAGS)

%.o: %.cpp $(LIB_HDR)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

$(LIB): $(LIB_OBJ)
	ar rcs $(LIB) $(LIB_OBJ)

Valgrind_demo: Demo
	valgrind $(VALGRIND_FLAGS) ./Demo

Valgrind_main: Main
	valgrind $(VALGRIND_FLAGS) ./Main

.PHONY: clean all

clean:
	rm -f *.o *.a Main Demo Test valgrind-out.txt



