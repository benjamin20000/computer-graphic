# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wconversion -Werror
LIBS = -lGLU -lGL -lglut

# Object files
OBJ = main.o button.o settings.o world.o control.o

# Executable
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
