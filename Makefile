# Makefile for Serializer

CPPFLAGS=-Wall -Werror -Wextra -Wfatal-errors
assignment=serializer

$(assignment): $(assignment).o
	g++ $(CPPFLAGS) -o $@ $^
tar:
	tar -cv $(MAKEFILE_LIST) *.cc >$(assignment).tar

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch
