EXEC = trie
SRCDIR = src
INCDIR = include
#SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(wildcard src/*.o)

CC = g++
CC_FLAGS = -g -w -I. -Iinclude

$(EXEC): main.o thereisno_trie.o
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

main.o: $(SRCDIR)/main.cpp thereisno_trie.o
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o

thereisno_trie.o: $(SRCDIR)/thereisno_trie.cpp
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/thereisno_trie.cpp -o $(SRCDIR)/thereisno_trie.o

#%o: %.cpp
#	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(SRCDIR)/*.o
