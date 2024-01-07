LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: main

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.h
	$(CXX) -c $< -o $@

main: main.o
	@echo "** Building the game"
	$(CXX) -o main main.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f main *.o

install:
	@echo '** Installing...'
	cp main /usr/bin/
