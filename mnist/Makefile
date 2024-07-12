CXX = g++
CXXFLAGS = -std=c++11 -I./include/ -I./KNN/include/ -DEUCLID
LDFLAGS =

SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj
LIBDIR = lib

# Source files for the library
LIBSRC = $(wildcard $(SRCDIR)/*.cpp)
LIBOBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(LIBSRC))
LIBRARY = libmylib.a

# Source files for the KNN executable
KNNSRCDIR = KNN/src
KNNSRC = $(wildcard $(KNNSRCDIR)/*.cpp)
KNNOBJ = $(patsubst $(KNNSRCDIR)/%.cpp,$(OBJDIR)/%.o,$(KNNSRC))
KNNEEXECUTABLE = knn_executable

all: $(BINDIR)/$(KNNEEXECUTABLE)

# Build the KNN executable
$(BINDIR)/$(KNNEEXECUTABLE): $(KNNOBJ) $(LIBDIR)/$(LIBRARY)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(KNNOBJ) -o $@ -L$(LIBDIR) -lmylib

# Build the library
$(LIBDIR)/$(LIBRARY): $(LIBOBJ)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

# Compile library object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile KNN object files
$(OBJDIR)/%.o: $(KNNSRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR)

run: $(BINDIR)/$(KNNEEXECUTABLE)
	./$(BINDIR)/$(KNNEEXECUTABLE)
