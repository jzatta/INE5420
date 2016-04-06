
all: test
	./vplexecution

test: *.cpp
	gcc `pkg-config --cflags gtk+-3.0`-o vplexecution *.cpp `pkg-config --libs gtk+-3.0` -rdynamic -lstdc++ -std=c++11 -lm

%.o: %.cpp *.hpp
	gcc `pkg-config --cflags gtk+-3.0`-o $@ -c `pkg-config --libs gtk+-3.0` -rdynamic -lstdc++ -std=c++11 -lm $<
	
%.txt: %.cpp *.hpp
	gcc `pkg-config --cflags gtk+-3.0`-o $@ -E -c `pkg-config --libs gtk+-3.0` -rdynamic -lstdc++ -std=c++11 -lm $<

clean:
	rm vplexecution
