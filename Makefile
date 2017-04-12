#set compiler to g++ for c++ code
CC = g++

# build target executable
TARGET = datalog

# specify version
CLFAGS = -std=c++14 -c

Database.o: source/Database.cpp source/Database.h source/Relation.h source/Predicate.h source/Rule.h source/Graph.h
	$(CC) $(CFLAGS) source/Database.cpp

DatalogProgram.o: DatalogProgram.cpp DatalogProgram.h Token.h Scanner.h tokenType.h Rule.h Predicate.h Parameter.h
	$(CC) CFLAGS DatalogProgram.cpp

Graph.o: Graph.cpp Graph.h 
	$(CC) CFLAGS Graph.cpp

Interpreter.o: Interpreter.cpp Interpreter.h Predicate.h Scheme.h Tuple.h DatalogProgram.h Database.h
	$(CC) CFLAGS Interpreter.cpp

main.o: main.cpp Scanner.h DatalogProgram.h Parse.h Interpreter.h
	$(CC) CFLAGS main.cpp

Parse.o: Parse.cpp Parse.h Token.h DatalogProgram.h
	$(CC) CFLAGS Parse.cpp

Predicate.o: Predicate.cpp Predicate.h Parameter.h
	$(CC) CFLAGS Predicate.cpp

Relation.o: Relation.cpp Relation.h Scheme.h Tuple.h
	$(CC) CFLAGS Relation.cpp

Rule.o: Rule.cpp Rule.h Predicate.h
	$(CC) CFLAGS Rule.cpp

Scanner.o: Scanner.cpp Scanner.h tokenType.h Token.h DatalogProgram.h
	$(CC) CFLAGS Scanner.cpp

Token.o: Token.cpp Token.h
	$(CC) CFLAGS Token.cpp

$(TARGET): Database.o DatalogProgram.o Graph.o Interpreter.o main.o Parse.o Predicate.o Relation.o Rule.o Scanner.o Token.o
	$(CC) -std=c++14 Database.o DatalogProgram.o Graph.o Interpreter.o main.o Parse.o Predicate.o Relation.o Rule.o Scanner.o Token.o -o $(TARGET)

clean:
	rm *.o
