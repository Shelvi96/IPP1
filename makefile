FLAGI=-Wall -Wextra -std=c11 -O2 -g
double_ended_list.o: double_ended_list.c double_ended_list.h
	gcc -c double_ended_list.c $(FLAGI)
self_sorting_list.o: self_sorting_list.c self_sorting_list.h
	gcc -c self_sorting_list.c $(FLAGI)
tree.o: tree.c tree.h
	gcc -c tree.c $(FLAGI)
main.o: main.c
	gcc -c main.c $(FLAGI)
main: tree.o self_sorting_list.o double_ended_list.o main.o
	gcc -o main double_ended_list.o self_sorting_list.o tree.o main.o $(FLAGI)
clean:
	@echo "Removing unnecessary files..."
	rm double_ended_list.o
	rm self_sorting_list.o
	rm tree.o
	rm main.o
	rm main
	@echo "Done."