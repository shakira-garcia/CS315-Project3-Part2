
#ifndef P3_PART1_BST_HPP
#define P3_PART1_BST_HPP

#pragma once
#include <string>
#include <vector>
#include <utility>
#include <cstddef>

class BST {
public:
    BST() = default;
    ~BST();

    // Build by inserting every token (O(n log n) avg)
    void buildFromTokens(const std::vector<std::string>& tokens);

    // Insert one word (updates count if already present)
    void insert(const std::string& word);

    // Measures
    std::size_t height() const;            // empty => 0
    std::size_t uniqueCount() const;       // # of distinct words
    std::size_t minFrequency() const;      // 0 if empty
    std::size_t maxFrequency() const;      // 0 if empty

    // Extract (word,count) lexicographically by word (inorder traversal)
    std::vector<std::pair<std::string,std::size_t>> toVector() const;

private:
    struct Node {
        std::string word;
        std::size_t count;
        Node* left;
        Node* right;
        Node(std::string w): word(std::move(w)), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root_ = nullptr;

    // helpers
    static void destroy(Node* n);
    static Node* insert(Node* n, const std::string& word);
    static std::size_t height(Node* n);
    static void inorder(Node* n, std::vector<std::pair<std::string,std::size_t>>& out);
    static void minmax(Node* n, std::size_t& mn, std::size_t& mx, std::size_t& uniq);
};


#endif //P3_PART1_BST_HPP
