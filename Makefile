LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: jomap

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.h
	$(CXX) -c $< -o $@

jomap: main.o Country.o
	@echo "** Building the game"
	$(CXX) -o jomap main.o Country.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f main *.o

install:
	@echo '** Installing...'
	cp main /usr/bin/
