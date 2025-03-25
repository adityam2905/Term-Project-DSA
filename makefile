# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -g 
# Target executable
TARGET = main
# Source files
SRCS = main.cpp \
       courseinfo.cpp \
       filehandler.cpp \
       node.cpp \
       node_operations.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Header files
HEADERS = courseinfo.h \
          filehandler.h \
          node.h \
          node_operations.h
# Default target
all: $(TARGET)
# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
# Rule to compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Rule to run the executable with input file
run: $(TARGET)
	./$(TARGET) input.txt
# Alternative run rule that allows any input file
# Usage: make run INPUT=your_input_file.txt
run-with-file: $(TARGET)
	./$(TARGET) $(INPUT)
# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)
.PHONY: all run run-with-file clean
