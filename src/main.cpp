/* The MIT License (MIT)
 *
 *  Copyright (c) 2015 John Ruffer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <iostream>
#include "thereisno_trie.h"


int main(int argc, char ** argv) {
    tin::Trie trie;

    trie.catalog("Hello");
    if(trie.lookup("Hello")) {
        std::cout << "trie found 'Hello'" << std::endl;
    } else {
        std::cerr << "ERROR: trie did not find 'Hello'" << std::endl;
    }

    if(!trie.lookup("Hey")) {
        std::cout << "trie could not find 'Hey'" << std::endl;
    } else {
        std::cerr << "ERROR: trie found 'Hey'" << std::endl;
    }

    tin::Trie copy(trie);

    if(copy.lookup("Hello")) {
        std::cout << "copy found 'Hello'" << std::endl;
    } else {
        std::cerr << "ERROR: copy did not find 'Hello'" << std::endl;
    }

    if(!copy.lookup("Hey")) {
        std::cout << "Copy could not find 'Hey'" << std::endl;
    } else {
        std::cerr << "ERROR: copy did not find 'Hello'" << std::endl;
    }

    copy.catalog("Bat");
    if(copy.lookup("Bat")) {
        std::cout << "Copy found 'Bat'" << std::endl;
    } else {
        std::cerr << "ERROR: copy did not find 'Bat'" << std::endl;
    }

    if(!trie.lookup("Bat")) {
        std::cout << "trie could not find 'Bat'" << std::endl;
    } else {
        std::cerr << "ERROR: trie found 'Bat'" << std::endl;
    }

    return 0;
}
