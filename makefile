CFLAGS=-Wall -Wextra -std=c11 -O2

main: tree.o self_sorting_list.o double_ended_list.o main.o utl.o
	gcc -o main double_ended_list.o self_sorting_list.o tree.o utl.o main.o $(CFLAGS)
	
double_ended_list.o: double_ended_list.c double_ended_list.h
	gcc -c double_ended_list.c $(CFLAGS)

self_sorting_list.o: self_sorting_list.c self_sorting_list.h
	gcc -c self_sorting_list.c $(CFLAGS)

tree.o: tree.c tree.h
	gcc -c tree.c $(CFLAGS)

utl.o: utl.c utl.h
	gcc -c utl.c $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

clean:
	@echo "Removing unnecessary files..."
	rm double_ended_list.o
	rm self_sorting_list.o
	rm tree.o
	rm utl.o
	rm main.o
	rm main
	@echo "Done."