CXX = g++
CXXFLAGS = -std=c++11 -I./include/
LDFLAGS =

SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEPS = $(wildcard $(INCDIR)/*.hpp)

EXECUTABLE = main

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(BINDIR)/$(EXECUTABLE)
	./$(BINDIR)/$(EXECUTABLE)
