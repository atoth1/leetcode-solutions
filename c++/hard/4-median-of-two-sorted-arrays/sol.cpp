// https://leetcode.com/problems/median-of-two-sorted-arrays/

#include <algorithm>

class Solution {
public:
    using Iterator = std::vector<int>::const_iterator;
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return findMedianSortedArraysImpl(nums1.begin(), nums1.end(), nums2.begin(), nums2.end()); 
    }
    
private:
    double findMedianSortedArraysImpl(Iterator lbegin,
                                      Iterator lend,
                                      Iterator rbegin,
                                      Iterator rend)
    {
        int M = std::distance(lbegin, lend);
        int N = std::distance(rbegin, rend);

        // Terminal cases
        if (N == 0)
        {
            int M1 = M/2;
            return M % 2 ? static_cast<double>(*(lbegin + M1))
                : (*(lbegin + M1 - 1) + *(lbegin + M1))/2.0;
        }
        else if (M == 0)
        {
            int N1 = N/2;
            return N % 2 ? static_cast<double>(*(rbegin + N1))
                : (*(rbegin + N1 - 1) + *(rbegin + N1))/2.0;
        }
        else if (M == 1 && N == 1)
        {
            return (*lbegin + *rbegin)/2.0;
        }
        else if (M == 1 && N == 2)
        {
            return *lbegin < *rbegin ? *rbegin : *lbegin > *(rbegin+1) ? *(rbegin+1) : *lbegin;
        }
        else if (M == 2 && N == 1)
        {
            return *rbegin < *lbegin ? *lbegin : *rbegin > *(lbegin+1) ? *(lbegin+1) : *rbegin;
        }
        else if (*(lend-1) < *rbegin)
        {
            return M == N ? (*(lend-1) + *rbegin)/2.0 :
                M < N ? findMedianSortedArraysImpl(lend, lend, rbegin, rend-M) : 
                        findMedianSortedArraysImpl(lbegin+N, lend, rbegin, rbegin);
        }
        else if (*(rend-1) < *lbegin)
        {
            return M == N ? (*(rend-1) + *lbegin)/2.0 :
                M < N ? findMedianSortedArraysImpl(lend, lend, rbegin+M, rend) : 
                        findMedianSortedArraysImpl(lbegin, lend-N, rbegin, rbegin);
        }
        
        const int num_remove = (M+N)/4;
        if (N < num_remove)
        {
            return findMedianSortedArraysImpl(lbegin+num_remove, lend-num_remove, rbegin, rend);
        }
        else if (M < num_remove)
        {
            return findMedianSortedArraysImpl(lbegin, lend, rbegin+num_remove, rend-num_remove);
        }
        else
        {
            if (*(lbegin + num_remove - 1) < *(rbegin + num_remove - 1))
            {
                lbegin += num_remove;
                M -= num_remove;
                if (M < num_remove)
                    return findMedianSortedArraysImpl(lbegin, lend, rbegin, rend-num_remove);
            }
            else
            {
                rbegin += num_remove;
                N -= num_remove;
                if (N < num_remove)
                    return findMedianSortedArraysImpl(lbegin, lend-num_remove, rbegin, rend);
            }
            
            if (*(lend - num_remove) > *(rend - num_remove))
            {
                lend -= num_remove;
            }
            else
            {
                rend -= num_remove;
            }
            return findMedianSortedArraysImpl(lbegin, lend, rbegin, rend);

        }
    }
};
