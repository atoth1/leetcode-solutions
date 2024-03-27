// https://leetcode.com/problems/find-the-string-with-lcp/

#include <optional>
#include <string>
#include <utility>
#include <vector>

class Solution {
public:
    static std::string findTheString(const std::vector<std::vector<int>>& mat) {
        if (!checkFeasibility(mat)) return "";
        
        auto dsu = makeDSU(mat);
        if (!dsu) return "";
        
        const auto candidate = makeCandidate(*dsu);
        return candidate && checkCandidate(*candidate, mat) ? *candidate : "";
    }
    
private:
    
    static bool checkFeasibility(const std::vector<std::vector<int>>& mat) {
        // Check symmetry and valid lengths
        const int n = mat.size();
        for (int row = 0; row < n; ++row) {
            if (mat[row][row] != n - row) return false;
            for (int col = row + 1; col < n; ++col) {
                if (mat[row][col] != mat[col][row] || mat[row][col] > n - col) return false;
            }
        }
        return true;
    }
    
    class DSU {
    public:
        DSU(const int n) : nodes(n) { }
        
        int size() const noexcept { return nodes.size(); }
        
        bool inSameSet(const int id1, const int id2) {
            return getRootId(id1) == getRootId(id2);
        }
        
        void join(const int id1, const int id2) {
            int rootId1 = getRootId(id1);
            int rootId2 = getRootId(id2);
            if (rootId1 != rootId2) {
                if (nodes[rootId1].rank < nodes[rootId2].rank) std::swap(rootId1, rootId2);
                if (nodes[rootId1].rank == nodes[rootId2].rank) ++nodes[rootId1].rank;
                nodes[rootId2].parentId = rootId1;
            }
        }
        
        bool rootCharIsSet(const int id) {
            return nodes[getRootId(id)].c != SetNode::UNSET_CHAR;
        }
        
        void setRootChar(const int id, const char c) {
            nodes[getRootId(id)].c = c;
        }
        
        char getRootChar(const int id) {
            return nodes[getRootId(id)].c;
        }
        
    private:
        
        struct SetNode {
            int parentId = -1;
            int rank = 0;

            static constexpr char UNSET_CHAR = '\0';
            char c = UNSET_CHAR;
        };
        
        std::vector<SetNode> nodes;
        
        int getRootId(int id) {
            int rootId = id;
            while (nodes[rootId].parentId != -1) {
                rootId = nodes[rootId].parentId;
            }
            
            while (nodes[id].parentId != -1) {
                id = std::exchange(nodes[id].parentId, rootId);
            }
            return rootId;
        }
    };
    
    static std::optional<DSU> makeDSU(const std::vector<std::vector<int>>& mat) {
        const int n = mat.size();
        
        DSU dsu(n);
        for (int row = 0; row < n; ++row) {
            for (int col = row + 1; col < n; ++col) {
                if (mat[row][col]) {
                    dsu.join(row, col);
                }
            }
        }
        
        for (int row = 0; row < n; ++row) {
            for (int col = row + 1; col < n; ++col) {
                if (!mat[row][col] && dsu.inSameSet(row, col)) return {};
            }
        }
        
        return dsu;
    }
    
    static std::optional<std::string> makeCandidate(DSU dsu) {
        const int n = dsu.size();
        char nextChar = 'a';
        std::string ret;
        ret.reserve(n);
        for (int id = 0; id < n; ++id) {
            if (!dsu.rootCharIsSet(id)) {
                if (nextChar > 'z') return {};
                dsu.setRootChar(id, nextChar++);
            }
            ret.push_back(dsu.getRootChar(id));
        }
        return ret;
    }
    
    static bool checkCandidate(const std::string& candidate, const std::vector<std::vector<int>>& mat) {
        const int n = candidate.size();
        std::vector<int> curr(n);
        for (int id = 0; id < n; ++id) {
            curr[id] = candidate[id] == candidate[n - 1];
            if (curr[id] != mat[n - 1][id]) return false;
        }
        
        std::vector<int> prev(n);
        for (int row = n - 2; row >= 0; --row) {
            prev[n - 1] = candidate[n - 1] == candidate[row];
            if (prev[n - 1] != mat[row][n - 1]) return false;
            
            for (int col = n - 2; col >= 0; --col) {
                prev[col] = candidate[col] == candidate[row] ? 1 + curr[col + 1] : 0;
                if (prev[col] != mat[row][col]) return false;
            }
            
            std::swap(prev, curr);
        }
        return true;
    }
};
