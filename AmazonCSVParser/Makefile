CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -g

SRCS = main.cpp menu.cpp hashtable.cpp
HEADERS = categoryList.h Product.h menu.h hashtable.h

OBJS = $(SRCS:.cpp=.o)

all: mainexe run  # 'make' will compile and then run

mainexe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o mainexe $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: mainexe
	./mainexe  # Automatically executes mainexe

clean:
	rm -f $(OBJS) mainexe

