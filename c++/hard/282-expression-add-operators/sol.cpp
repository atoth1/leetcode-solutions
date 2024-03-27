// https://leetcode.com/problems/expression-add-operators/

#include <numeric>
#include <string>
#include <utility>
#include <vector>

namespace {
    void generatePartitions(
        const std::string& num,
        const int startPos,
        std::vector<std::vector<std::string>>& partitions
    ) {
        if (startPos < num.size()) {
            std::vector<std::vector<std::string>> next{};
            for (const auto& partition : partitions) {
                // Extending last term (no leading 0's)
                if (partition.back()[0] != '0') {
                    auto part1 = partition;
                    part1.back().push_back(num[startPos]);
                    next.push_back(part1);
                }
                
                // Starting new term
                auto part2 = partition;
                part2.push_back({ num[startPos] });
                next.push_back(part2);
            }
            std::swap(partitions, next);
            generatePartitions(num, startPos + 1, partitions);
        }
    }
    
    void impl(
        const std::vector<std::string>& partition,
        const int partitionPos,
        const int target,
        std::string& expr,
        std::vector<long long>& summationTerms,
        std::vector<std::string>& successes
    ) {
        if (partitionPos == partition.size()) {
            if (std::accumulate(summationTerms.begin(), summationTerms.end(), 0ll) == target) {
                successes.push_back(expr);
            }
        } else {
            const long long num = std::stoll(partition[partitionPos]);
            const int exprSize = expr.size();
            
            // Inserting +
            expr.push_back('+');
            expr.append(partition[partitionPos]);
            summationTerms.push_back(num);
            impl(partition, partitionPos + 1, target, expr, summationTerms, successes);
            summationTerms.pop_back();
            
            // Inserting -
            expr[exprSize] = '-';
            summationTerms.push_back(-num);
            impl(partition, partitionPos + 1, target, expr, summationTerms, successes);
            summationTerms.pop_back();
            
            // Inserting *
            expr[exprSize] = '*';
            const long long tmp = summationTerms.back();
            summationTerms.back() *= num;
            impl(partition, partitionPos + 1, target, expr, summationTerms, successes);
            while (expr.size() > exprSize) {
                expr.pop_back();
            }
            summationTerms.back() = tmp;
        }
    }
}

class Solution {
public:
    static std::vector<std::string> addOperators(const std::string& num, const int target) {
        std::vector<std::vector<std::string>> partitions{ { { num[0] } } };
        generatePartitions(num, 1, partitions);
        
        std::string expr{};
        std::vector<long long> terms{};
        std::vector<std::string> ret{};
        for (const auto& partition : partitions) {
            expr = partition[0];
            terms.push_back(std::stoll(partition[0]));
            impl(partition, 1, target, expr, terms, ret);
            terms.pop_back();
        }
        return ret;
    }
};
