CC = g++
CFLAGS  =
LDFLAGS =
NAME = xiangqi

all: xiangqi_chinese-chess

xiangqi_chinese-chess: main.o position.o textio.o
	$(CC) -o $@ $^ $(LDFLAGS) -o $(NAME)

main.o: src/main.cpp
	$(CC) -c $(CFLAGS) $<

position.o: src/position.cpp src/val_moves.cpp src/position.h
	$(CC) -c $(CFLAGS) $<
	
textio.o: src/textio.cpp src/io.h src/position.h
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean cleanest

clean:
	rm *.o
	rm $(NAME)

cleanest: clean
