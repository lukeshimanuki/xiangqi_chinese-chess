CC = g++
CFLAGS  =
LDFLAGS =
NAME = xiangqi

all: xiangqi_chinese-chess

xiangqi_chinese-chess: main.o position.o textio.o person.o computer.o io.o game.o
	$(CC) -o $@ $^ $(LDFLAGS) -o $(NAME)

main.o: src/main.cpp
	$(CC) -c $(CFLAGS) $<

position.o: src/position.cpp src/val_moves.cpp src/position.h
	$(CC) -c $(CFLAGS) $<
	
textio.o: src/textio.cpp src/io.h src/position.h
	$(CC) -c $(CFLAGS) $<
	
io.o: src/io.cpp src/io.h src/position.h
	$(CC) -c $(CFLAGS) $<
	
person.o: src/person.cpp src/player.h src/io.h
	$(CC) -c $(CFLAGS) $<
	
computer.o: src/computer.cpp src/player.h
	$(CC) -c $(CFLAGS) $<

game.o: src/game.cpp src/player.h src/position.h
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean cleanest

clean:
	rm *.o
	rm $(NAME)

cleanest: clean
