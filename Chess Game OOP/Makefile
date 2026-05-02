CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRCDIR = src
OBJDIR = output
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TARGET = $(OBJDIR)/chess-game

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR):
mkdir -p $(OBJDIR)

clean:
rm -f $(OBJECTS) $(TARGET)
