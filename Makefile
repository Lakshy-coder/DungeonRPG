# Makefile for Dungeon RPG

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = DungeonRPG

SOURCES = main.cpp Player.cpp Enemy.cpp Dungeon.cpp BattleSystem.cpp \
          Inventory.cpp Item.cpp GameManager.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run