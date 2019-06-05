objs = main.o tictactoe.o
tictactoe: $(objs)
	gcc -Wall -o $@ $(objs)
main.o: main.c tictactoe.c
	gcc -Wall -c $<
tictactoe.o: tictactoe.c tictactoe.h
	gcc -Wall -c $<
clean:
	rm tictactoe $(objs)
