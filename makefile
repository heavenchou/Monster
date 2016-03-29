
Monster: src/*.cpp src/*.h
	mkdir -p output
	g++ -std=c++11 src/*.cpp src/*.h -o output/Monster
