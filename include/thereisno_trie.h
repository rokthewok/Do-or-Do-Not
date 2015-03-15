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

#ifndef THEREISNO_TRIE_H
#define THEREISNO_TRIE_H

#include <string>
#include <ostream>

namespace tin {

class TrieImpl;

class Trie {
public:
    Trie();
    ~Trie();
    Trie(const Trie & other);
    const Trie & operator=(const Trie & rhs);
    void catalog(const std::string & keyword);
    bool lookup(const std::string & keyword) const;
    void dump(std::ostream & out);
private:
    TrieImpl * m_trie;
};

} // namespace tin

#endif // THEREISNO_TRIE_H
