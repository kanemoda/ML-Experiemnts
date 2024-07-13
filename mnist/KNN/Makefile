CXX = g++
CXXFLAGS = -std=c++11 -I../include/ -I./include/ -DEUCLID
LDFLAGS = -L../lib -lmylib

SRCDIR = src
INCDIR = include
BINDIR = ../bin
OBJDIR = ../obj

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEPS = $(wildcard $(INCDIR)/*.hpp)

EXECUTABLE = knn_executable

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJ) ../lib/libmylib.a
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(EXECUTABLE)

run: $(BINDIR)/$(EXECUTABLE)
	@cd ../ && ./bin/$(EXECUTABLE)

.PHONY: clean run
