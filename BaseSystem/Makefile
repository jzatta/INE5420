
all: test
	./vplexecution

test: *.cpp *.hpp
	gcc `pkg-config --cflags gtk+-3.0`-o vplexecution *.cpp `pkg-config --libs gtk+-3.0` -rdynamic -lstdc++ -std=c++11 -lm

clean:
	rm vplexecution
