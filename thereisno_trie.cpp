#include "thereisno_trie.h"


namespace tin {

const int NODES_PER_LEVEL = 26;

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
            this->subsequent_nodes[i] = other.subsequent_nodes[i];
        }
    }

    const TrieNode & operator=(const TrieNode & rhs) {
        if(this != &rhs) {
            this->key_letter = rhs.key_letter;
            for(int i = 0; i != NODES_PER_LEVEL; ++i) {
                this->subsequent_nodes[i] = rhs.subsequent_nodes[i];
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
    TrieNode * m_root_nodes[NODES_PER_LEVEL];
};

TrieImpl::TrieImpl() {
    for(int i = 0; i != NODES_PER_LEVEL; ++i) {
        m_root_nodes[i] = NULL;
    }
}

TrieImpl::~TrieImpl() {
    for(int i = 0; i != NODES_PER_LEVEL; ++i) {
        if(m_root_nodes[i]) {
            delete m_root_nodes[i];
        }
    }
}

TrieImpl::TrieImpl(const TrieImpl & other) {
    for(int i = 0; i != NODES_PER_LEVEL; ++i) {
        this->m_root_nodes[i] = other.m_root_nodes[i];
    }
}

const TrieImpl & TrieImpl::operator=(const TrieImpl & rhs) {
    if(this != &rhs) {
        for(int i = 0; i != NODES_PER_LEVEL; ++i) {
            this->m_root_nodes[i] = rhs.m_root_nodes[i];
        }
    }

    return *this;
}

void TrieImpl::catalog(const std::string & keyword) {
    if(keyword.size()) {
        this->catalog(keyword, 1, m_root_nodes[keyword[0] - 'a']);
    }
}

void TrieImpl::catalog(const std::string & keyword,
                       size_t kw_position,
                       TrieNode * parent_node) {
    int child_position = keyword[kw_position] - 'a';
    TrieNode * new_node = new TrieNode(keyword[kw_position]);
    parent_node->subsequent_nodes[child_position] = new_node;
    if(keyword.size() - 1 == kw_position) {
        new_node->terminal_node = true;
        return;
    }

    catalog(keyword, kw_position + 1, new_node);
}

bool TrieImpl::lookup(const std::string & keyword) const {
    if(keyword.size()) {
        return this->lookup(keyword, 1, m_root_nodes[keyword[0] - 'a']);
    }

    return false;
}

bool TrieImpl::lookup(const std::string & keyword,
                      size_t kw_position,
                      const TrieNode * parent_node) const {
    int child_position = keyword[kw_position] - 'a';
    if(keyword.size() == kw_position) {
        return true;
    }

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
    : m_trie(new TrieImpl()) {};

Trie::~Trie() {
    if(m_trie) {
        delete m_trie;
    }
}

Trie::Trie(const Trie & other) {
    *(this->m_trie) = *(other.m_trie);
}

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
