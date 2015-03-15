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

#include <cctype>
#include "thereisno_trie.h"


namespace tin {

const int NODES_PER_LEVEL = 26;

inline char get_current_letter(const std::string & word, int position) {
    return ::tolower(word[position]);
}

inline int get_offset_letter_index(char letter) {
    return static_cast<int>(letter - 'a');
}

class TrieNode {
public:
    TrieNode(char kl)
        : key_letter(kl),
          terminal_node(false) {
        for(int i = 0; i != NODES_PER_LEVEL; ++i) {
            subsequent_nodes[i] = NULL;
        }
    }
    ~TrieNode() {
        for(int i = 0; i != NODES_PER_LEVEL; ++i) {
            if(subsequent_nodes[i]) {
                delete subsequent_nodes[i];
            }
        }
    }

    TrieNode(const TrieNode & other) {
        this->key_letter = other.key_letter;
        for(int i = 0; i != NODES_PER_LEVEL; ++i) {
            if(subsequent_nodes[i] && other.subsequent_nodes[i]) {
                *(this->subsequent_nodes[i]) = *(other.subsequent_nodes[i]);
            } else if(other.subsequent_nodes[i]) {
                this->subsequent_nodes[i] = new TrieNode(*(other.subsequent_nodes[i]));
            } else if(this->subsequent_nodes[i]) {
                delete this->subsequent_nodes[i];
                this->subsequent_nodes[i] = NULL;
            } else {
                this->subsequent_nodes[i] = NULL;
            }
        }
    }

    const TrieNode & operator=(const TrieNode & rhs) {
        if(this != &rhs) {
            this->key_letter = rhs.key_letter;
            for(int i = 0; i != NODES_PER_LEVEL; ++i) {
                if(subsequent_nodes[i] && rhs.subsequent_nodes[i]) {
                    *(this->subsequent_nodes[i]) = *(rhs.subsequent_nodes[i]);
                } else if(rhs.subsequent_nodes[i]) {
                    this->subsequent_nodes[i] = new TrieNode(*(rhs.subsequent_nodes[i]));
                } else if(this->subsequent_nodes[i]) {
                    delete this->subsequent_nodes[i];
                    this->subsequent_nodes[i] = NULL;
                } else {
                    this->subsequent_nodes[i] = NULL;
                }
            }
        }
        return *this;
    }

    char key_letter;
    bool terminal_node;
    TrieNode * subsequent_nodes[NODES_PER_LEVEL];
};

class TrieImpl {
public:
    TrieImpl();
    ~TrieImpl();
    TrieImpl(const TrieImpl & other);
    const TrieImpl & operator=(const TrieImpl & rhs);
    void catalog(const std::string & keyword);
    bool lookup(const std::string & keyword) const;
    void dump(std::ostream & out);
private:
    void catalog(const std::string & keyword,
                 size_t kw_position,
                 TrieNode * current_node);
    bool lookup(const std::string & keyword,
                size_t position,
                const TrieNode * parent_node) const;
    TrieNode * m_root;
};

TrieImpl::TrieImpl() {
    m_root = new TrieNode(' ');  // the root of the trie
                                 // should be an "empty" char
}

TrieImpl::~TrieImpl() {
    if(m_root) {
        delete m_root;
    }
}

TrieImpl::TrieImpl(const TrieImpl & other) {
    this->m_root = new TrieNode(*(other.m_root));
}

const TrieImpl & TrieImpl::operator=(const TrieImpl & rhs) {
    if(this != &rhs) {
        *(this->m_root) = *(rhs.m_root);
    }

    return *this;
}

void TrieImpl::catalog(const std::string & keyword) {
    if(keyword.size()) {
        char start_letter = get_current_letter(keyword, 0);
        int start_position = get_offset_letter_index(start_letter);
        if(!m_root->subsequent_nodes[start_position]) {
            m_root->subsequent_nodes[start_position] = new TrieNode(start_letter);
        }
        this->catalog(keyword, 1, m_root->subsequent_nodes[start_position]);
    }
}

void TrieImpl::catalog(const std::string & keyword,
                       size_t kw_position,
                       TrieNode * parent_node) {
    if(keyword.size() == kw_position) {
        return;
    }

    char current_letter = get_current_letter(keyword, kw_position);
    int child_position =  get_offset_letter_index(current_letter);
    TrieNode * new_node = new TrieNode(current_letter);
    parent_node->subsequent_nodes[child_position] = new_node;

    if(keyword.size() - 1 == kw_position) {
        new_node->terminal_node = true;
    }

    catalog(keyword, kw_position + 1, new_node);
}

bool TrieImpl::lookup(const std::string & keyword) const {
    if(keyword.size()) {
        char start_letter = get_current_letter(keyword, 0);
        int start_position = get_offset_letter_index(start_letter);
        if(m_root->subsequent_nodes[start_position]) {
            return this->lookup(keyword, 1, m_root->subsequent_nodes[start_position]);
        }
    }

    return false;
}

bool TrieImpl::lookup(const std::string & keyword,
                      size_t kw_position,
                      const TrieNode * parent_node) const {
    if(keyword.size() == kw_position) {
        return true;
    }

    int child_position = get_offset_letter_index(get_current_letter(keyword, kw_position));
    if(!parent_node->subsequent_nodes[child_position]) {
        return false;
    }

    return lookup(keyword,
                  kw_position + 1,
                  parent_node->subsequent_nodes[child_position]);
}

void TrieImpl::dump(std::ostream & out) {
}




Trie::Trie()
    : m_trie(new TrieImpl()) {}

Trie::~Trie() {
    if(m_trie) {
        delete m_trie;
    }
}

Trie::Trie(const Trie & other)
    : m_trie(new TrieImpl(*(other.m_trie))) {}

const Trie & Trie::operator=(const Trie & rhs) {
    if(this != &rhs) {
        *(this->m_trie) = *(rhs.m_trie);
    }

    return *this;
}

void Trie::catalog(const std::string & keyword) {
    m_trie->catalog(keyword);
}

bool Trie::lookup(const std::string & keyword) const {
    return m_trie->lookup(keyword);
}

void Trie::dump(std::ostream & out) {
    m_trie->dump(out);
}

} // namespace tin
