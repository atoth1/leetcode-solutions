// https://leetcode.com/problems/rectangle-area-ii/

#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    static constexpr int MOD = 1000000007;
    
    struct IdRange {
        int begin;
        int end;
        
        constexpr bool operator==(const IdRange&) const noexcept = default;
        
        constexpr int size() const noexcept {
            return end - begin;
        }
        
        constexpr int mid() const noexcept {
            return begin + size() / 2;
        }
        
        constexpr bool canSplit() const noexcept {
            return size() > 1;
        }
        
        constexpr std::pair<IdRange, IdRange> split() const noexcept {
            return { { begin, mid() }, { mid(), end } };
        }
        
        constexpr bool intersectsWith(const IdRange other) const noexcept {
            return begin < other.end && other.begin < end;
        }
        
        constexpr IdRange intersectionWith(const IdRange other) const noexcept {
            const int intersectionBegin = begin > other.begin ? begin : other.begin;
            const int intersectionEnd = end < other.end ? end : other.end;
            return { intersectionBegin, intersectionEnd };
        }
    };
    
    struct IdRange2d {
        IdRange xRange;
        IdRange yRange;
        
        constexpr bool operator==(const IdRange2d&) const noexcept = default;
        
        constexpr bool canSplit() const noexcept {
            return xRange.canSplit() || yRange.canSplit();
        }
        
        constexpr std::pair<IdRange2d, IdRange2d> split() const noexcept {
            if (xRange.size() >= yRange.size()) {
                const auto [left, right] = xRange.split();
                return { { left, yRange }, { right, yRange } };
            } else {
                const auto [bottom, top] = yRange.split();
                return { { xRange, bottom }, { xRange, top } };
            }
        }
        
        constexpr bool intersectsWith(const IdRange2d other) const noexcept {
            return xRange.intersectsWith(other.xRange) && yRange.intersectsWith(other.yRange);
        }
        
        constexpr IdRange2d intersectionWith(const IdRange2d other) const noexcept {
            return { xRange.intersectionWith(other.xRange), yRange.intersectionWith(other.yRange) };
        }
    };
    
    class Grid {
    public:
        Grid(const std::vector<std::vector<int>>& rectangles) {
            std::set<int> xCoordsSet{};
            std::set<int> yCoordsSet{};
            for (const auto rect : rectangles) {
                xCoordsSet.insert(rect[0]);
                xCoordsSet.insert(rect[2]);
                yCoordsSet.insert(rect[1]);
                yCoordsSet.insert(rect[3]);
            }
            
            auto makeCoordData = [](
                const std::set<int>& coordsSet,
                std::vector<int>& coords,
                std::unordered_map<int, int>& idLookup
            ) {
                coords = std::vector<int>(coordsSet.begin(), coordsSet.end());
                for (int id = 0; id < coords.size(); ++id) {
                    idLookup[coords[id]] = id;
                }
            };
            makeCoordData(xCoordsSet, xCoords, xCoordToId);
            makeCoordData(yCoordsSet, yCoords, yCoordToId);
        }
        
        IdRange2d toIdRange2d(const std::vector<int>& rectangle) const noexcept {
            IdRange xRange{ xCoordToId.at(rectangle[0]), xCoordToId.at(rectangle[2]) };
            IdRange yRange{ yCoordToId.at(rectangle[1]), yCoordToId.at(rectangle[3]) };
            return { xRange, yRange };
        }
        
        IdRange2d getBoundingIdRange2d() const noexcept {
            IdRange xRange{ 0, static_cast<int>(xCoords.size()) - 1 };
            IdRange yRange{ 0, static_cast<int>(yCoords.size()) - 1 };
            return { xRange, yRange };
        }
        
        int getArea(const IdRange2d range) const noexcept {
            const int xLength = xCoords[range.xRange.end] - xCoords[range.xRange.begin];
            const int yLength = yCoords[range.yRange.end] - yCoords[range.yRange.begin];
            return (static_cast<long long>(xLength) * yLength) % MOD;
        }
        
    private:
        std::vector<int> xCoords{};
        std::vector<int> yCoords{};
        std::unordered_map<int, int> xCoordToId{};
        std::unordered_map<int, int> yCoordToId{};
    };
    
    class Node {
    public:
        Node(const std::shared_ptr<Grid> inGrid, const IdRange2d inRange)
            : grid(inGrid)
            , range(inRange)
        {
            if (range.canSplit()) {
                const auto [part1, part2] = range.split();
                child1 = std::make_unique<Node>(grid, part1);
                child2 = std::make_unique<Node>(grid, part2);
            }
        }
        
        void insert(const IdRange2d inRange) {
            if (!isFullyIncluded) {
                if (inRange == range) {
                    isFullyIncluded = true;
                } else {
                    const auto [part1, part2] = range.split();
                    if (part1.intersectsWith(inRange)) {
                        child1->insert(part1.intersectionWith(inRange));
                    }
                    if (part2.intersectsWith(inRange)) {
                        child2->insert(part2.intersectionWith(inRange));
                    }
                }
            }
        }
        
        int queryIncludedArea() const noexcept {
            if (isFullyIncluded) {
                return grid->getArea(range);
            } else if (child1 && child2) {
                return (child1->queryIncludedArea() + child2->queryIncludedArea()) % MOD;
            } else {
                return 0;
            }
        }
        
    private:
        std::shared_ptr<Grid> grid;
        IdRange2d range;
        std::unique_ptr<Node> child1{};
        std::unique_ptr<Node> child2{};
        bool isFullyIncluded = false;
    };
    
    class SegmentTree {
    public:
        SegmentTree(const std::shared_ptr<Grid> inGrid)
            : grid(inGrid)
            , root(std::make_unique<Node>(grid, grid->getBoundingIdRange2d()))
        { }
        
        void insert(const std::vector<int>& rectangle) {
            root->insert(grid->toIdRange2d(rectangle));
        }
        
        int queryIncludedArea() const noexcept {
            return root->queryIncludedArea();
        }
        
    private:
        std::shared_ptr<Grid> grid;
        std::unique_ptr<Node> root;
    };
}

class Solution {
public:
    static int rectangleArea(const std::vector<std::vector<int>>& rectangles) {
        const auto grid = std::make_shared<Grid>(rectangles);
        SegmentTree st(grid);
        for (const auto& rectangle : rectangles) {
            st.insert(rectangle);
        }
        return st.queryIncludedArea();
    }
};
