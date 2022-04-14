EXECUTABLE  = Puzzle-Game

# The following line looks for a project's main() in files named
# executable.cpp (substituted from EXECUTABLE above), or main.cpp
PROJECTFILE = $(or $(wildcard $(EXECUTABLE).cpp), main.cpp)

# designate which compiler to use
CXX         = g++

# list of sources used in project
SOURCES     = $(wildcard *.cpp)

# list of objects used in project
OBJECTS     = $(SOURCES:%.cpp=%.o)

# Default Flags + static
CXXFLAGS = -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -static

# make debug - will compile sources with $(CXXFLAGS) and the -g3 flag
#              also defines DEBUG, so "#ifdef DEBUG /*...*/ #endif" works
debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug

$(EXECUTABLE): $(OBJECTS)
ifeq ($(EXECUTABLE), executable)
	@echo Edit EXECUTABLE variable in Makefile.
	@echo Using default a.out.
	$(CXX) $(CXXFLAGS) $(OBJECTS)
else
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)
endif

# rule for creating objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug
	rm -Rf *.dSYM

# disable built-in rules
.SUFFIXES:
