FLAGS = -Wall -Wextra -Weffc++ -std=c++14

vector-tests: main.cpp
	$(CXX) -o $@ $(FLAGS) $^