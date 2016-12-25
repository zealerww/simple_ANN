CXX = g++
CC = g++
CXXFLAGS += -std=c++11
LDFLAGS += #-L dir
LDLIBS += `pkg-config --libs opencv` #-l somelibs
SOURCEFILE = $(notdir $(wildcard ./*.cpp))
OBJS = $(SOURCEFILE:.cpp=.o)

TARGET = main
all: $(TARGET)

$(TARGET): $(OBJS)

clean:
	-rm $(TARGET) *.o

.PHONY: clean