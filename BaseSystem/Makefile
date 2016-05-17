

OBJS:=$(subst .cpp,.o,$(shell ls *.cpp))
OBJS:=$(foreach object,$(OBJS),obj/$(object))

INC:= $(shell pwd)

all: vplexecution
	./vplexecution

vplexecution: $(OBJS)
	gcc `pkg-config --cflags gtk+-3.0`-o $@ $^ `pkg-config --libs gtk+-3.0` -rdynamic -lstdc++ -std=c++11 -lm

obj/%.o: %.cpp *.hpp | obj
	gcc `pkg-config --cflags gtk+-3.0` -funroll-loops -I$(INC) -o $@ -c -rdynamic -lstdc++ -std=c++11 -lm $<

obj: 
	mkdir obj

clean:
	rm -rf obj/
	rm -f vplexecution
