RES="template_list"
CC="clang++"


main.o:
	$(CC) -g -c -Wall ../main.cpp


compil:
	$(CC) -g -c -Wall ../*.cpp


link:
	$(CC) *.o -o $(RES)


build:
	make compil
	make link


run:
	./$(RES)


debug:
	kdbg ./$(RES)

clear:
	rm -rf *.o
	rm -rf $(RES)
