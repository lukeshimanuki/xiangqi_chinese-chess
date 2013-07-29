CC = g++
CFLAGS  = -O3
LDFLAGS =
NAME = xiangqi

all: xiangqi_chinese-chess

xiangqi_chinese-chess: main.o position.o textio.o person.o computer.o io.o game.o
	$(CC) -o $@ $^ $(LDFLAGS) -o $(NAME)

main.o: src/main.cpp
	$(CC) -c $(CFLAGS) $<

position.o: src/position.cpp
	$(CC) -c $(CFLAGS) $<
	
textio.o: src/textio.cpp
	$(CC) -c $(CFLAGS) $<
	
io.o: src/io.cpp
	$(CC) -c $(CFLAGS) $<
	
person.o: src/person.cpp
	$(CC) -c $(CFLAGS) $<
	
computer.o: src/computer.cpp
	$(CC) -c $(CFLAGS) $<

game.o: src/game.cpp
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean cleanest

clean:
	rm *.o
	rm $(NAME)

cleanest: clean
