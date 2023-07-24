// https://leetcode.com/problems/smallest-sufficient-team/

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> smallestSufficientTeam(
        const std::vector<std::string>& req_skills,
        const std::vector<std::vector<std::string>>& people
    ) {
        auto makeTargetMask = [&]() {
            std::uint16_t mask{};
            for (int offset = 0; offset < req_skills.size(); ++offset) {
                mask |= 1 << offset;
            }
            return mask;
        };
        const auto targetMask = makeTargetMask();
        
        auto makeStrToSkillMask = [&]() {
            std::unordered_map<std::string_view, std::uint16_t> map{};
            int offset = 0;
            for (const auto& skill : req_skills) {
                map[skill] = 1 << offset++;
            }
            return map;
        };
        const auto strToSkillMask = makeStrToSkillMask();
        
        auto makeCandidates = [&]() {
            std::vector<Candidate> candidates{};
            for (int pos = 0; pos < people.size(); ++pos) {
                std::uint16_t skillsMask{};
                for (const auto& skill : people[pos]) {
                    skillsMask |= strToSkillMask.at(skill);
                }
                candidates.push_back({ pos, skillsMask });
            }
            return candidates;
        };
        const auto candidates = makeCandidates();
        
        auto makeSkillMaskToCandidates = [&]() {
            std::unordered_map<std::uint16_t, std::vector<Candidate>> map{};
            for (const auto [_, skillMask] : strToSkillMask) {
                auto& satisfyingCandidates = map[skillMask];
                for (const auto candidate : candidates) {
                    if (skillMask & candidate.skillsMask) {
                        satisfyingCandidates.push_back(candidate);
                    }
                }
            }
            return map;
        };
        const auto skillMaskToCandidates = makeSkillMaskToCandidates();
        
        std::unordered_map<std::uint16_t, std::vector<int>> cache{};
        return impl(targetMask, skillMaskToCandidates, cache);
    }
    
private:
    struct Candidate{
        int pos{ -1 };
        std::uint16_t skillsMask{};
    };
    
    static std::vector<int> impl(
        const std::uint16_t remainingMask,
        const std::unordered_map<std::uint16_t, std::vector<Candidate>>& skillMaskToCandidates,
        std::unordered_map<std::uint16_t, std::vector<int>>& cache
    ) {
        if (remainingMask == 0) return {};
        
        if (auto it = cache.find(remainingMask); it != cache.end()) {
            return it->second;
        }
        
        for (const auto& [skillMask, candidates] : skillMaskToCandidates) {
            if (remainingMask & skillMask) {
                std::vector<int> ret{};
                for (const auto candidate : candidates) {
                    auto candidateSol = impl(remainingMask & ~candidate.skillsMask, skillMaskToCandidates, cache);
                    candidateSol.push_back(candidate.pos);
                    if (ret.empty() || candidateSol.size() < ret.size()) {
                        ret = candidateSol;
                    }
                }
                cache[remainingMask] = ret;
                return ret;
            }
        }
        return {};
    }
};