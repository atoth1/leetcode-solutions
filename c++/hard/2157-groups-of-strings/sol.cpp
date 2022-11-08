// https://leetcode.com/problems/groups-of-strings/

#include <algorithm>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        std::sort(words.begin(), words.end(), [](const std::string& l, const std::string& r) {
            return l.size() < r.size();
        });
        
        std::vector<std::shared_ptr<Node>> nodes{};
        std::unordered_map<uint32_t, std::shared_ptr<Node>> maskToNode{};
        for (const auto& word : words) {
            auto getMask = [](const std::string& str) {
                uint32_t mask = 0;
                for (const auto c : str) {
                    mask |= 1 << (c-'a');
                }
                return mask;
            };
            
            auto updateConnections = [&](const std::shared_ptr<Node> node, const uint32_t mask) {
                static constexpr int N = 26;
                // Sorted by increasing string length, so only consider removing
                // a character or changing one character.
                for (int bit = 0; bit < N; ++bit) {
                    if ((mask & (1 << bit)) != 0) {
                        // Connections from removing a set bit.
                        uint32_t removedMask = mask ^ (1 << bit);
                        auto removedIt = maskToNode.find(removedMask);
                        if (removedIt != maskToNode.end()) {
                            merge(node, removedIt->second);
                        }
                        
                        // Connections from changing one set bit
                        for (int addedBit = 0; addedBit < N; ++addedBit) {
                            if ((removedMask & (1 << addedBit)) == 0) {
                                uint32_t changedMask = removedMask | (1 << addedBit);
                                auto changedIt = maskToNode.find(changedMask);
                                if (changedIt != maskToNode.end()) {
                                    merge(node, changedIt->second);
                                }
                            }
                        }
                    }
                }
            };
            
            auto node = std::make_shared<Node>();
            auto mask = getMask(word);
            updateConnections(node, mask);
            nodes.push_back(node);
            maskToNode[mask] = node;
        }
        
        std::unordered_set<std::shared_ptr<Node>> roots{};
        int maxSize = 0;
        for (const auto node : nodes) {
            const auto root = rootNode(node);
            roots.insert(root);
            if (root->size > maxSize) maxSize = root->size;
        }
        return { static_cast<int>(roots.size()), maxSize };
    }
    
private:
    struct Node {
        std::shared_ptr<Node> parent{};
        int size{ 1 };
    };
    
    std::shared_ptr<Node> rootNode(std::shared_ptr<Node> node) {
        auto root = node;
        while (root->parent) root = root->parent;
        while (node != root) {
            auto tmp = node->parent;
            node->parent = root;
            node = tmp;
        }
        return root;
    }
    
    void merge(std::shared_ptr<Node> x, std::shared_ptr<Node> y) {
        x = rootNode(x);
        y = rootNode(y);
        if (x != y) {
            if (x->size < y->size) std::swap(x, y);
            x->size += y->size;
            y->parent = x;
        }
    }
};
