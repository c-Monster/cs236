test: source/*.h source/*.cpp
	g++ -std=c++14 source/*.h source/*.cpp
	mv a.out datalog

clean:
	rm source/*.h.gch 
	rm datalog
