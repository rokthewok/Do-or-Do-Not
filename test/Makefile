CC = g++
CC_FLAGS = -std=c++11 -g -w -I. -I../include -lgtest_main -lgtest

SRCDIR=../src
EXEC = trie_test
SOURCES = $(wildcard *.cpp) \
$(SRCDIR)/thereisno_trie.cpp \
$(SRCDIR)/thereisno_trienode.cpp \

OBJECTS = test_trienode.o \
$(SRCDIR)/thereisno_trie.o \
$(SRCDIR)/thereisno_trienode.o \

$(EXEC): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o $(EXEC)

thereisno_trie.o: thereisno_trienode.o $(SRCDIR)/thereisno_trie.cpp
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/thereisno_trie.cpp -o $(SRCDIR)/thereisno_trie.o

thereisno_trienode.o: $(SRCDIR)/thereisno_trienode.cpp
	$(CC) -c $(CC_FLAGS) $(SRCDIR)/thereisno_trienode.cpp -o $(SRCDIR)/thereisno_trienode.o

test_trie.o: test_trie.cpp
	$(CC) -c $(CC_FLAGS) test_trie.cpp -o test_trie.o

test_trienode.o: test_trienode.cpp
	$(CC) -c $(CC_FLAGS) test_trienode.cpp -o test_trienode.o

clean:
	rm -f $(EXEC) $(OBJECTS)

print-%: ; @echo $*=$($*)
