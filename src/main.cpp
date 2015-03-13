#include <iostream>
#include "thereisno_trie.h"


int main(int argc, char ** argv) {
    tin::Trie trie;

    trie.catalog("Hello");
    if(trie.lookup("Hello")) {
        std::cout << "Found 'Hello'" << std::endl;
    }

    if(!trie.lookup("Hey")) {
        std::cout << "Could not find 'Hey'" << std::endl;
    }

    return 0;
}
