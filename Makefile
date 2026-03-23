CXXFLAGS = -Wall -Wextra -Weffc++ -std=c++14 -MMD

all : vector-tests

vector-tests: main.o
	$(CXX) -o $@ $^

-include main.d

clean:
	$(RM) -rf vector-tests main.o main.d