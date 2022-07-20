functional:
	echo "compiling functional.c and its dependencies"
	gcc functional.c iterators.c linkedlist.c -o functional

clean: 
	rm functional