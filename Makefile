test: source/*.h source/*.cpp
	g++ -std=c++14 source/*.h source/*.cpp

clean:
	rm source/*.h.gch 
