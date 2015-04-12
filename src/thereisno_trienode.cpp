#include "thereisno_trienode.h"

#ifndef THEREISNO_EXCEPTIONS_H
#include "thereisno_exceptions.h"
#endif // THEREISNO_EXCEPTIONS_H


namespace tin {

TrieNode::TrieNode(char kl)
    : TrieNode(kl, false) {}

TrieNode::TrieNode(char kl, bool terminal_node)
    : m_key_letter(kl),
      m_terminal_node(terminal_node) {}

TrieNode::~TrieNode() {}

TrieNode::TrieNode(const TrieNode & other)
    : m_key_letter(other.m_key_letter),
      m_terminal_node(other.m_terminal_node),
      m_subsequent_nodes(other.m_subsequent_nodes) {}

const TrieNode & TrieNode::operator=(const TrieNode & rhs) {
    if(this != &rhs) {
        this->m_key_letter = rhs.m_key_letter;
        this->m_terminal_node = rhs.m_terminal_node;
        this->m_subsequent_nodes = rhs.m_subsequent_nodes;
    }
    return *this;
}

char TrieNode::getKeyLetter() const {
    return this->m_key_letter;
}

void TrieNode::setKeyLetter(char key_letter) {
    this->m_key_letter = key_letter;
}

bool TrieNode::isTerminalNode() const {
    return this->m_terminal_node;
}

void TrieNode::isTerminalNode(bool terminal_node) {
    this->m_terminal_node = terminal_node;
}

const TrieNode::TrieNodePtr & TrieNode::findChildNode(char key_letter) const {
    ChildNodesCit result = this->m_subsequent_nodes.find(key_letter);
    if(this->m_subsequent_nodes.end() == result) {
        throw ChildNodeNotFoundException();
    }

    return result->second;
}

TrieNode::TrieNodePtr & TrieNode::findChildNode(char key_letter) {
    ChildNodesIt result = this->m_subsequent_nodes.find(key_letter);
    if(this->m_subsequent_nodes.end() == result) {
        throw ChildNodeNotFoundException();
    }

    return result->second;
}

TrieNode::TrieNodePtr & TrieNode::addChildNode(char key_letter, bool is_terminal_node) {
    ChildNodesIt result = this->m_subsequent_nodes.find(key_letter);
    if(this->m_subsequent_nodes.end() != result) {
        throw ChildNodeAlreadyExistsException();
    }

    TrieNodePtr child_node(new TrieNode(key_letter, is_terminal_node));

    return this->m_subsequent_nodes.insert(ChildNodeData(key_letter, child_node)).first->second;
}

} // namespace tin
