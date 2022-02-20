all: p4
	valgrind -q --leak-check=full ./p4 ENUM <sat.in >test_standard.out
	diff test_standard.out sat_enum.out >diff.out
	valgrind -q --leak-check=full ./p4 ENUM <unsat.in >test_standard.out
	diff test_standard.out unsat_enum.out >diff.out
	valgrind -q --leak-check=full ./p4 DEDUCT <sat.in >test_standard.out
	diff test_standard.out sat_deduct.out >diff.out
	valgrind -q --leak-check=full ./p4 DEDUCT <unsat.in >test_standard.out
	diff test_standard.out unsat_deduct.out >diff.out
p4: main.cpp clause.cpp cnf.cpp solver.cpp
	g++ -std=c++11 -Wall -o p4 main.cpp clause.cpp cnf.cpp solver.cpp
clean:
	rm -f test_standard.out p4 diff.out

# Normal output:
# g++ -std=c++11 -Wall -o p4 main.cpp clause.cpp cnf.cpp solver.cpp
# valgrind -q --leak-check=full ./p4 ENUM <sat.in >test_standard.out
# ==2422== error calling PR_SET_PTRACER, vgdb might block
# diff test_standard.out sat_enum.out >diff.out
# valgrind -q --leak-check=full ./p4 ENUM <unsat.in >test_standard.out
# ==2426== error calling PR_SET_PTRACER, vgdb might block
# diff test_standard.out unsat_enum.out >diff.out
# valgrind -q --leak-check=full ./p4 DEDUCT <sat.in >test_standard.out
# ==2430== error calling PR_SET_PTRACER, vgdb might block
# diff test_standard.out sat_deduct.out >diff.out
# valgrind -q --leak-check=full ./p4 DEDUCT <unsat.in >test_standard.out
# ==2434== error calling PR_SET_PTRACER, vgdb might block
# diff test_standard.out unsat_deduct.out >diff.out