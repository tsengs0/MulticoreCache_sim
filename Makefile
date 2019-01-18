LIB_DIR=-L/usr/local/systemc-2.3.2/lib-linux64

INC_DIR=-I/usr/local/systemc-2.3.2/include

LIB=-lsystemc



APP=4_core



all: main.o alu.o bus.o save.o thread.o RAM.o cache.o

	 g++ -o $(APP) $(LIB_DIR) $(LIB) main.o alu.o bus.o save.o thread.o RAM.o cache.o



alu.o: alu.cpp alu.h cache.h

	 g++ $(INC_DIR) -c alu.cpp



main.o: main.cpp thread.h bus.h alu.h save.h bus_if.h RAM.h

	 g++ $(INC_DIR) -c main.cpp

bus.o : bus.cpp bus.h bus_if.h

	 g++ $(INC_DIR) -c bus.cpp

save.o : save.cpp save.h

	 g++ $(INC_DIR) -c save.cpp

thread.o : thread.cpp alu.h save.h bus_if.h thread.h

	 g++ $(INC_DIR) -c thread.cpp

RAM.o : RAM.h

	 g++ $(INC_DIR) -c RAM.cpp

cache.o : cache.h

	g++ $(INC_DIR) 	-c cache.cpp

clean:

	rm -rf $(APP) *.o

