// https://leetcode.com/problems/number-of-valid-move-combinations-on-chessboard/submissions/

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace {
    
    static constexpr int BOARD_SIZE = 8;
    
    static constexpr int N_PIECES = 4;
    
    struct Position {
        int row{ -1 };
        int col{ -1 };
        
        constexpr bool operator==(const Position other) const {
            return row == other.row && col == other.col;
        }
        
        constexpr bool operator!=(const Position other) const {
            return !(*this == other);
        }
    };
    
    static constexpr Position UNUSED{ -1000, -1000 };
    
    struct Direction {
        static constexpr int UNSET = -1000000000;
        int rowDelta{ UNSET };
        int colDelta{ UNSET };
        
        constexpr bool operator==(const Direction other) const {
            return rowDelta == other.rowDelta && colDelta == other.colDelta;
        }
        
        constexpr bool operator!=(const Direction other) const {
            return !(*this == other);
        }
    };
    
    static constexpr Direction ZERO{ 0, 0 };
    
    constexpr Position operator+(const Position pos, const Direction dir) {
        return { pos.row + dir.rowDelta, pos.col + dir.colDelta };
    }
    
    struct Rook {
        Position pos{};
        
        Rook(const int row, const int col) : pos{ row, col } {}
        
        static constexpr std::string_view getPieceName() {
            return "rook";
        }
        
        static std::vector<Direction> getValidDirections() {
            return { ZERO, { 1, 0 }, { -1, 0 }, { 0 , 1 }, { 0, -1 } };
        }
    };
    
    struct Bishop {
        Position pos{};
        
        Bishop(const int row, const int col) : pos{ row, col } {}
        
        static constexpr std::string_view getPieceName() {
            return "bishop";
        }
        
        static std::vector<Direction> getValidDirections() {
            return { ZERO, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
        }
    };
    
    struct Queen {
        Position pos{};
        
        Queen(const int row, const int col) : pos{ row, col } {}
        
        static constexpr std::string_view getPieceName() {
            return "queen";
        }
        
        static std::vector<Direction> getValidDirections() {
            return { ZERO, { 1, 0 }, { -1, 0 }, { 0 , 1 }, { 0, -1 },
                     { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
        }
    };
    
    struct Dummy {
        Position pos{ UNUSED };
        
        static constexpr std::string_view getPieceName() {
            return "dummy";
        }
        
        static std::vector<Direction> getValidDirections() {
            return { ZERO };
        }
    };
    
    using Piece = std::variant<Rook, Bishop, Queen, Dummy>;
    
    struct BoardState {
        Position p1{};
        Direction d1{};
        Position p2{};
        Direction d2{};
        Position p3{};
        Direction d3{};
        Position p4{};
        Direction d4{};
        
        constexpr bool isValidState() const {
            auto isValidPosition = [](const Position pos) {
                return pos == UNUSED
                    || (pos.row >= 0 && pos.row < BOARD_SIZE && pos.col >= 0 && pos.col < BOARD_SIZE);
            };
            if (!(isValidPosition(p1) && isValidPosition(p2) && isValidPosition(p3) && isValidPosition(p4))) {
                return false;
            }
            
            auto isPairwiseValid = [](const Position pos1, const Position pos2) {
                return (pos1 != UNUSED && pos2 != UNUSED) ? pos1 != pos2 : true;
            };
            return isPairwiseValid(p1, p2) && isPairwiseValid(p1, p3) && isPairwiseValid(p1, p4)
                && isPairwiseValid(p2, p3) && isPairwiseValid(p2, p4) && isPairwiseValid(p3, p4);
        }
    };
    
    void impl(const BoardState bs, int& count) {
        if (bs.isValidState()) {
            ++count;
            
            const bool p1Inactive = bs.d1 == ZERO;
            const bool p2Inactive = bs.d2 == ZERO;
            const bool p3Inactive = bs.d3 == ZERO;
            const bool p4Inactive = bs.d4 == ZERO;
            const std::uint8_t bound = 1 << N_PIECES;
            for (std::uint8_t mask = 1; mask < bound; ++mask) {
                const bool set1 = mask & 1;
                const Direction dir1 = set1 ? bs.d1 : ZERO;
                const Position pos1 = bs.p1 + dir1;
                const bool set2 = mask & (1 << 1);
                const Direction dir2 = set2 ? bs.d2 : ZERO;
                const Position pos2 = bs.p2 + dir2;
                const bool set3 = mask & (1 << 2);
                const Direction dir3 = set3 ? bs.d3 : ZERO;
                const Position pos3 = bs.p3 + dir3;
                const bool set4 = mask & (1 << 3);
                const Direction dir4 = set4 ? bs.d4 : ZERO;
                const Position pos4 = bs.p4 + dir4;
                
                const bool shouldRecurse = (!p1Inactive || !set1) && (!p2Inactive || !set2)
                    && (!p3Inactive || !set3) && (!p4Inactive || !set4);
                if (shouldRecurse) {
                    impl({ pos1, dir1, pos2, dir2, pos3, dir3, pos4, dir4 }, count);
                }
            }
        }
    }
}

class Solution {
public:
    int countCombinations(
        const std::vector<std::string>& pieceTypes,
        const std::vector<std::vector<int>>& positions
    ) {
        auto makePieces = [&]() {
            Piece init(std::in_place_type_t<Dummy>{});
            std::array<Piece, N_PIECES> pieces{ init, init, init, init };
            const int n = pieceTypes.size();
            for (int id = 0; id < n; ++id) {
                if (pieceTypes[id] == Rook::getPieceName()) {
                    pieces[id] = Piece(std::in_place_type_t<Rook>{}, positions[id][0] - 1, positions[id][1] - 1);
                } else if (pieceTypes[id] == Bishop::getPieceName()) {
                    pieces[id] = Piece(std::in_place_type_t<Bishop>{}, positions[id][0] - 1, positions[id][1] - 1);
                } else if (pieceTypes[id] == Queen::getPieceName()) {
                    pieces[id] = Piece(std::in_place_type_t<Queen>{}, positions[id][0] - 1, positions[id][1] - 1);
                }
            }
            return pieces;
        };
        
        auto posVisitor = [](auto&& piece) {
            return piece.pos;
        };
        
        auto dirVisitor = [](auto&& piece) {
            return piece.getValidDirections();
        };
        
        const auto pieces = makePieces();
        int count = 0;
        for (const Direction dir1 : std::visit(dirVisitor, pieces[0])) {
            for (const Direction dir2 : std::visit(dirVisitor, pieces[1])) {
                for (const Direction dir3 : std::visit(dirVisitor, pieces[2])) {
                    for (const Direction dir4 : std::visit(dirVisitor, pieces[3])) {
                        BoardState bs {
                            std::visit(posVisitor, pieces[0]) + dir1, dir1, 
                            std::visit(posVisitor, pieces[1]) + dir2, dir2,
                            std::visit(posVisitor, pieces[2]) + dir3, dir3,
                            std::visit(posVisitor, pieces[3]) + dir4, dir4
                        };
                        impl(bs, count);
                    }
                }
            }
        }
        return count;
    }
};