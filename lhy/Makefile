all: test
	valgrind -q --leak-check=full ./test
	make clean
test: dynamic_array.cpp
	g++ -o test dynamic_array.cpp
clean: 
	rm test