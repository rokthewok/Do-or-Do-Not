CC = g++
CC_FLAGS = -w -I. -I.. -lgtest_main -lgtest

EXEC = trie_test
SOURCES = $(wildcard *.cpp) \
../thereisno_trie.cpp

OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

%o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
