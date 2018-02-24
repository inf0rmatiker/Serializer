# Makefile for Serializer

CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option
assignment=serializer

$(assignment): main.o serializer.o unserializer.o
	$(CXX) $(CXXFLAGS) main.o serializer.o unserializer.o -o $@
	
main.o : main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

serializer.o : serializer.cc serializer.h
	$(CXX) $(CXXFLAGS) -c serializer.cc

unserializer.o : unserializer.cc unserializer.h
	$(CXX) $(CXXFLAGS) -c unserializer.cc

tar:
	tar -cv $(MAKEFILE_LIST) *.cc >$(assignment).tar

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch
