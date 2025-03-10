# Makefile for Circular Buffer Heart Rate Monitor

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2 -std=c++11
LDFLAGS =
GTEST_LIBS = -lgtest -lpthread

# Target names.
TARGET = heart_rate_monitor
TEST_TARGET = test_circular_buffer

# Source files.
C_SOURCES = circular_buffer.c heart_rate_monitor.c
C_OBJECTS = $(C_SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(C_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(C_OBJECTS) $(LDFLAGS)

%.o: %.c circular_buffer.h
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): circular_buffer.c test_circular_buffer.cpp circular_buffer.h
	$(CXX) $(CXXFLAGS) circular_buffer.c test_circular_buffer.cpp -o $(TEST_TARGET) $(GTEST_LIBS)

clean:
	rm -f $(TARGET) $(C_OBJECTS) $(TEST_TARGET)
