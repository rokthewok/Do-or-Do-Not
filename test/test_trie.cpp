#include <gtest/gtest.h>
#include "../thereisno_trie.h"

TEST(TrieTests, TestTrieConstructor) {
    EXPECT_NO_THROW(tin::Trie());
}

TEST(TrieTests, TestCatalog) {
    tin::Trie trie;
    trie.catalog("hello");
}
