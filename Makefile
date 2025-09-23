# Compiler
CXX = g++

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin
TARGET = $(BINDIR)/vkui_app

# Default build type is DEBUG
BUILD_TYPE ?= DEBUG

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I$(INCDIR)
ifeq ($(BUILD_TYPE), DEBUG)
	CXXFLAGS += -g
	# In DEBUG mode, we define _DEBUG macro
	CPPFLAGS += -D_DEBUG
else
	CXXFLAGS += -O3
	# In RELEASE mode, we define NDEBUG to disable asserts and validation layers
	CPPFLAGS += -DNDEBUG
endif

# Sources and Objects
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Linker flags from pkg-config
LDFLAGS = $(shell pkg-config --libs glfw3 vulkan)

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build finished [$(BUILD_TYPE)]. Run with: ./$(TARGET)"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILDDIR)/* $(BINDIR)/*

# Target to build in release mode
release:
	$(MAKE) all BUILD_TYPE=RELEASE

.PHONY: all clean release
