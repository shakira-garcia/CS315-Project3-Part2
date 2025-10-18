
#include "BST.hpp"
#include <algorithm>

BST::~BST(){ destroy(root_); }

void BST::destroy(Node* n){
    if(!n) return;
    destroy(n->left);
    destroy(n->right);
    delete n;
}

BST::Node* BST::insert(Node* n, const std::string& w){
    if(!n) return new Node(w);
    if(w < n->word) {
        n->left  = insert(n->left, w);
    } else if(w > n->word) {
        n->right = insert(n->right, w);
    } else {
        n->count += 1;
    }
    return n;
}

void BST::insert(const std::string& word){
    root_ = insert(root_, word);
}

void BST::buildFromTokens(const std::vector<std::string>& tokens){
    for(const auto& t : tokens) insert(t);
}

std::size_t BST::height(Node* n){
    if(!n) return 0; // empty-tree height := 0 per spec
    std::size_t lh = height(n->left);
    std::size_t rh = height(n->right);
    std::size_t bigger;
    if (lh > rh) {
        bigger = lh;
    } else {
        bigger = rh;
    }
    return 1 + bigger;
}

std::size_t BST::height() const { return height(root_); }

void BST::inorder(Node* n, std::vector<std::pair<std::string,std::size_t>>& out){
    if(!n) return;
    inorder(n->left, out);
    out.emplace_back(n->word, n->count);
    inorder(n->right, out);
}

std::vector<std::pair<std::string,std::size_t>> BST::toVector() const{
    std::vector<std::pair<std::string,std::size_t>> out;
    inorder(root_, out);
    return out;
}

void BST::minmax(Node* n, std::size_t& mn, std::size_t& mx, std::size_t& uniq){
    if(!n) return;
    minmax(n->left, mn, mx, uniq);
    mn = std::min(mn, n->count);
    mx = std::max(mx, n->count);
    uniq += 1;
    minmax(n->right, mn, mx, uniq);
}

std::size_t BST::uniqueCount() const{
    std::size_t mn = (std::size_t)-1, mx = 0, uniq = 0;
    minmax(root_, mn, mx, uniq);
    return uniq;
}

std::size_t BST::minFrequency() const{
    if(!root_) return 0;
    std::size_t mn = (std::size_t)-1, mx = 0, uniq = 0;
    minmax(root_, mn, mx, uniq);
    if (uniq != 0) {
        return mn;
    } else {
        return 0;
    }
}

std::size_t BST::maxFrequency() const{
    if(!root_) return 0;
    std::size_t mn = (std::size_t)-1, mx = 0, uniq = 0;
    minmax(root_, mn, mx, uniq);
    if (uniq != 0) {
        return mx;
    } else {
        return 0;
    }
}