CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g

SRCS = main.cpp menu.cpp hashtable.cpp
HEADERS = categoryList.h Product.h menu.h hashtable.h

OBJS = $(SRCS:.cpp=.o)

mainexe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mainexe $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) mainexe
