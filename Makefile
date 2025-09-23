# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -g -Wall

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin

# Executable name
TARGET = $(BINDIR)/vkui_app

# Find all .cpp files recursively in SRCDIR
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')

# Generate object file paths based on source paths
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Library flags from pkg-config
INCLUDES = -I$(INCDIR)
LDFLAGS = $(shell pkg-config --libs glfw3 vulkan)

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build finished. Run with: ./$(TARGET)"

# Rule to compile .cpp files into .o files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILDDIR)/* $(BINDIR)/*

# Phony targets
.PHONY: all clean
