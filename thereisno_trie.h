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
