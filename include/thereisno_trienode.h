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

#ifndef THEREISNO_TRIENODE_H
#define THEREISNO_TRIENODE_H

#include <unordered_map>
#include <utility>
#include <memory>

namespace tin {

class TrieNode {
public:
    typedef std::shared_ptr<TrieNode> TrieNodePtr;

    explicit TrieNode(char kl);
    explicit TrieNode(char kl, bool is_terminal_node);
    ~TrieNode();
    TrieNode(const TrieNode & other);
    const TrieNode & operator=(const TrieNode & rhs);

    char getKeyLetter() const;
    void setKeyLetter(char key_letter);
    bool isTerminalNode() const;
    void isTerminalNode(bool terminal_node);
    const TrieNodePtr & findChildNode(char key_letter) const;
    TrieNodePtr & findChildNode(char key_letter);
    TrieNodePtr & addChildNode(char key_letter, bool is_terminal_node);
    //void pruneChildNode(char key_letter);
private:
    typedef std::unordered_map<char, TrieNodePtr> ChildNodes;
    typedef ChildNodes::iterator ChildNodesIt;
    typedef ChildNodes::const_iterator ChildNodesCit;
    typedef ChildNodes::value_type ChildNodeData;

    char m_key_letter;
    bool m_terminal_node;
    ChildNodes m_subsequent_nodes;
};

} // namespace tin

#endif // THEREISNO_TRIENODE_H
