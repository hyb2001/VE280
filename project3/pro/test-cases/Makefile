#variable definition

CC = g++

MAINSRCS = p4.cpp
OTHSRCS = simulation.cpp
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.cpp=.o)
TARGETS = $(MAINSRCS:.cpp=)

CFLAGS = -g -Wall

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)
	./0.in
	./1.in
	./2.in
	./3.in
	./4.in
	./5.in
	./6.in
	./7.in
	./8.in
	./9.in
	./10.in
	./11.in
	./12.in
	./13.in
	./14.in
	./15.in
	./16.in
	./17.in
	./18.in
	./19.in
	./20.in
	./21.in
	./22.in
	./23.in
	./24.in
	./25.in
	./26.in
	./27.in
	./28.in
	./29.in
	./30.in
	./31.in
	./32.in
	./33.in
	./34.in
	cat ../test_cases/*.out >../test_cases/a.output
	diff ../test-cases/a.output ../test_cases/a.output >diff.out
	cd test-cases/

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS)

clean:
	rm -f $(OBJS) $(TARGETS) a.output *.output ../test_cases/a.output

.PHONY: all clean memcheck 
