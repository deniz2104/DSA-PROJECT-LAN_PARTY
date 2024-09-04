.PHONY: build run clean

OBJS = main.o list.o stack_and_queue.o trees.o

build: $(OBJS)
	gcc -Wall -Werror -Wextra $(OBJS) -o lanParty -lm

main.o: main.c
	gcc -Wall -Werror -Wextra -c main.c -o main.o

list.o: source/list.c header/list.h
	gcc -Wall -Werror -Wextra -c source/list.c -o list.o

stack_and_queue.o: source/stack_and_queue.c header/stack_and_queue.h
	gcc -Wall -Werror -Wextra -c source/stack_and_queue.c -o stack_and_queue.o

trees.o: source/trees.c header/trees.h
	gcc -Wall -Werror -Wextra -c source/trees.c -o trees.o

run:
	./lanParty

clean:
	rm -f $(OBJS) lanParty
