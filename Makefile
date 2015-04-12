EXEC = trie
SRCDIR = src
INCDIR = include
#SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(wildcard src/*.o)

CC = g++
CC_FLAGS = -std=c++11 -g -w -I. -Iinclude

$(EXEC): main.o thereisno_trie.o thereisno_trienode.o
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

main.o: thereisno_trienode.o $(SRCDIR)/main.cpp thereisno_trie.o
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o

thereisno_trie.o: thereisno_trienode.o $(SRCDIR)/thereisno_trie.cpp
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/thereisno_trie.cpp -o $(SRCDIR)/thereisno_trie.o

thereisno_trienode.o: $(SRCDIR)/thereisno_trienode.cpp
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/thereisno_trienode.cpp -o $(SRCDIR)/thereisno_trienode.o

#%o: %.cpp
#	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(SRCDIR)/*.o
