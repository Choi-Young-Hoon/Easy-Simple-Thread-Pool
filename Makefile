FILES = $(wildcard *.cpp)
OBJECTS = $(subst .cpp,.o,$(FILES))
TARGET = test
CPPFLAGS = -pthread -std=c++11
all:
	g++ -c $(FILES) $(CPPFLAGS)
	g++ -o $(TARGET) $(OBJECTS) $(CPPFLAGS) 
clean:
	rm -rf $(TARGET) $(OBJECTS)
