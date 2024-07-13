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

# Build the library
$(LIBDIR)/$(LIBRARY): $(LIBOBJ)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

# Compile library object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(LIBDIR)

.PHONY: clean
