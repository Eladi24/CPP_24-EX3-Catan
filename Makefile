# Compiler: clang++
CC = clang++
# Compiler flags
CFLAGS = -Wall -g -std=c++11

# Valgrind flags
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --error-exitcode=99
# Catan library source files
LIB_SRC = Board.cpp City.cpp Hexagon.cpp Player.cpp Point.cpp Settlement.cpp \
		Structure.cpp Trail.cpp Vertex.cpp

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

all: Main 

Main: Main.o $(LIB)
	$(CC) $(CFLAGS) -o Main Main.o $(LIB)

%.o: %.cpp $(LIB_HDR)
	$(CC) $(CFLAGS) --compile $< -o $@

$(LIB): $(LIB_OBJ)
	ar rcs $(LIB) $(LIB_OBJ)

.PHONY: clean all

clean:
	rm -f *.o Main $(LIB)



