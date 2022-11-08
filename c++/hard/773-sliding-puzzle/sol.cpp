// https://leetcode.com/problems/sliding-puzzle/

#include <unordered_set>
#include <utility>

struct Configuration
{
    enum class Vacancy { TOPLEFT, TOPMID, TOPRIGHT, BOTTOMLEFT, BOTTOMMID, BOTTOMRIGHT };
    int topLeft{};
    int topMid{};
    int topRight{};
    int bottomLeft{};
    int bottomMid{};
    int bottomRight{};
    Vacancy vacancy{};
};

struct ConfigurationHash
{
    std::size_t operator()(const Configuration& c) const noexcept
    {
        std::size_t ret = c.topLeft;
        ret = 6*ret + c.topMid;
        ret = 6*ret + c.topRight;
        ret = 6*ret + c.bottomLeft;
        ret = 6*ret + c.bottomMid;
        ret = 6*ret + c.bottomRight;
        return ret;
    }
};

bool operator==(const Configuration& l, const Configuration& r)
{
    return ConfigurationHash{}(l) == ConfigurationHash{}(r);
}

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        Configuration start{board[0][0], board[0][1], board[0][2],
                            board[1][0], board[1][1], board[1][2]};
        if (start.topLeft == 0) start.vacancy = Configuration::Vacancy::TOPLEFT;
        else if (start.topMid == 0) start.vacancy = Configuration::Vacancy::TOPMID;
        else if (start.topRight == 0) start.vacancy = Configuration::Vacancy::TOPRIGHT;
        else if (start.bottomLeft == 0) start.vacancy = Configuration::Vacancy::BOTTOMLEFT;
        else if (start.bottomMid == 0) start.vacancy = Configuration::Vacancy::BOTTOMMID;
        else start.vacancy = Configuration::Vacancy::BOTTOMRIGHT;
        Configuration target{1, 2, 3, 4, 5, 0, Configuration::Vacancy::BOTTOMRIGHT};
        
        std::unordered_set<Configuration, ConfigurationHash> curr{start};
        std::unordered_set<Configuration, ConfigurationHash> next;
        std::unordered_set<Configuration, ConfigurationHash> visited;
        int moves = 0;
        while (!curr.empty())
        {
            for (const auto& config : curr)
            {
                if (config == target) return moves;
                visited.insert(config);
                
                Configuration candidate{config};
                switch (config.vacancy)
                {
                    case Configuration::Vacancy::TOPLEFT:
                        std::swap(candidate.topLeft, candidate.bottomLeft);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMLEFT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.topLeft, candidate.bottomLeft);
                        std::swap(candidate.topLeft, candidate.topMid);
                        candidate.vacancy = Configuration::Vacancy::TOPMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                    case Configuration::Vacancy::TOPMID:
                        std::swap(candidate.topMid, candidate.bottomMid);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.topMid, candidate.bottomMid);
                        std::swap(candidate.topMid, candidate.topLeft);
                        candidate.vacancy = Configuration::Vacancy::TOPLEFT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.topMid, candidate.topLeft);
                        std::swap(candidate.topMid, candidate.topRight);
                        candidate.vacancy = Configuration::Vacancy::TOPRIGHT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                    case Configuration::Vacancy::TOPRIGHT:
                        std::swap(candidate.topRight, candidate.bottomRight);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMRIGHT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.topRight, candidate.bottomRight);
                        std::swap(candidate.topRight, candidate.topMid);
                        candidate.vacancy = Configuration::Vacancy::TOPMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                    case Configuration::Vacancy::BOTTOMLEFT:
                        std::swap(candidate.bottomLeft, candidate.topLeft);
                        candidate.vacancy = Configuration::Vacancy::TOPLEFT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.bottomLeft, candidate.topLeft);
                        std::swap(candidate.bottomLeft, candidate.bottomMid);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                    case Configuration::Vacancy::BOTTOMMID:
                        std::swap(candidate.bottomMid, candidate.topMid);
                        candidate.vacancy = Configuration::Vacancy::TOPMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.bottomMid, candidate.topMid);
                        std::swap(candidate.bottomMid, candidate.bottomLeft);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMLEFT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.bottomMid, candidate.bottomLeft);
                        std::swap(candidate.bottomMid, candidate.bottomRight);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMRIGHT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                    case Configuration::Vacancy::BOTTOMRIGHT:
                        std::swap(candidate.bottomRight, candidate.topRight);
                        candidate.vacancy = Configuration::Vacancy::TOPRIGHT;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        std::swap(candidate.bottomRight, candidate.topRight);
                        std::swap(candidate.bottomRight, candidate.bottomMid);
                        candidate.vacancy = Configuration::Vacancy::BOTTOMMID;
                        if (visited.count(candidate) == 0) next.insert(candidate);
                        break;
                }
            }
            std::swap(curr, next);
            next.clear();
            ++moves;
        }
        return -1;
    }
};
