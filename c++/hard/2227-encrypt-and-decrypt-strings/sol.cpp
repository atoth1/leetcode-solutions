// https://leetcode.com/problems/encrypt-and-decrypt-strings/

#include <array>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace {
    class Node;
    
    using NodePtr = std::unique_ptr<Node>;
    
    class Node {
    public:
        Node() = default;
        
        void insert(const std::string_view str, int pos) {
            if (pos == str.size()) {
                isTerminal = true;
            } else {
                auto& child = children[str[pos] - 'a'];
                if (!child) {
                    child = std::make_unique<Node>();
                }
                child->insert(str, pos + 1);
            }
        }
        
        int count(
            const std::string_view str, 
            const int pos,
            const std::unordered_map<std::string_view, std::vector<char>>& lookup
        ) {
            if (pos == str.size()) {
                return isTerminal ? 1 : 0;
            } else {
                int count = 0;
                if (const auto it = lookup.find(str.substr(pos, 2)); it != lookup.end()) {
                    for (const char c : it->second) {
                        const auto& child = children[c - 'a'];
                        if (child) count += child->count(str, pos + 2, lookup);
                    }
                }
                return count;
            }
        }
        
    private:
        std::array<NodePtr, 26> children{};
        bool isTerminal{};
    };
    
    class Trie {
    public:    
        Trie() = default;
        
        void insert(const std::string_view str) {
            root->insert(str, 0);
        }
        
        int count(
            const std::string_view str, 
            const std::unordered_map<std::string_view, std::vector<char>>& lookup
        ) const {
            return root->count(str, 0, lookup);
        }
        
    private:
        NodePtr root = std::make_unique<Node>();
    };
}

class Encrypter {
public:
    Encrypter(
        const std::vector<char>& keys,
        const std::vector<std::string>& values,
        const std::vector<std::string>& dictionary
    ) : strs(values) {
        const int n = keys.size();
        for (int pos = 0; pos < n; ++pos) {
            lookup1[keys[pos]] = strs[pos];
            lookup2[strs[pos]].push_back(keys[pos]);
        }
        for (const std::string_view str : dictionary) dictLookup.insert(str);
    }
    
    std::string encrypt(const std::string_view word) {
        std::stringstream builder{};
        for (const char c : word) {
            if (const auto it = lookup1.find(c); it != lookup1.end()) {
                builder << it->second;
            } else {
                return "";
            }
        }
        return builder.str();
    }
    
    int decrypt(const std::string_view word) {
        if (word.size() & 1) return 0;
        else return dictLookup.count(word, lookup2);
    }
    
private:
    std::vector<std::string> strs{};
    std::unordered_map<char, std::string_view> lookup1{};
    std::unordered_map<std::string_view, std::vector<char>> lookup2{};
    Trie dictLookup{};
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */
