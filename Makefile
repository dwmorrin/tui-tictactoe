objs = tictactoe.o
tictactoe: $(objs)
	gcc -Wall -o $@ $(objs)
tictactoe.o: tictactoe.c tictactoe.h
	gcc -Wall -c $<
clean:
	rm tictactoe $(objs)
