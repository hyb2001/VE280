all: p5_pretest p5_a p5_b
	valgrind -q --leak-check=full ./p5_pretest
	valgrind -q --leak-check=full ./p5_a <call.in >test_a.out
	valgrind -q --leak-check=full ./p5_b <tex.in >test_b.out
	# diff test_b.out tex.out
p5_pretest:
	g++ -Wall -Wunused -Wextra -Werror -pedantic -O3 -o p5_pretest test.cpp
p5_a:
	g++ -Wall -Wunused -Wextra -Werror -pedantic -O3 -o p5_a call.cpp
p5_b:
	g++ -Wall -Wunused -Wextra -Werror -pedantic -O3 -o p5_b cleaner.cpp
clean:
	rm -f p5* test*.out