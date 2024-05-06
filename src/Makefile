CC = g++
CFLAGS = -Wextra -Werror -Wall
CPPFLAGS = -lstdc++ -std=c++17
SOURCE_MODEL = Model/*.cc
SOURCE_QT =
TESTS = UnitTest/test.cc
TEST_FLAGS = -lgtest -pthread -lgmock
OBJECTS = *.o

.PHONY: all maze.a install uninstall start clean dvi dist leaks style tests

all: clean maze.a

maze.a:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCE_MODEL) -c
	ar $(ARFLAGS) maze.a $(OBJECTS)
	rm $(OBJECTS)

clean:
	rm -rf main *.o *.a UnitTest/test

leaks: maze.a
	$(CC) $(CPPFLAGS) $(FLAGS) -c $(TESTS) -o tests.o
	$(CC) tests.o maze.a $(TEST_FLAGS) -o test
	CK_FORK=no leaks --atExit -- ./test


tests: maze.a
	$(CC) $(CPPFLAGS) $(FLAGS) -c $(TESTS) -o tests.o
	$(CC) tests.o maze.a $(TEST_FLAGS) -o UnitTest/test
	cd UnitTest && ./test

install:
	qmake -o Executables/Makefile Maze.pro
	cd Executables && make

start:
	cd Executables/Maze.app/Contents/MacOS && ./Maze

uninstall:
	cd Executables && make clean
	cd Executables && rm -rf Makefile qmake_qmake_qm_files.qrc Maze.app .qm .qmake.stash


style:
	clang-format -n Model/*.cc Model/*.h View/*.cc View/*.h Controller/*.cc Controller/*.h $(TESTS) -style=google

dist:
	cd .. && tar -czf Maze_v1.0.tgz src

dvi:
	open Manual/Manual.md
