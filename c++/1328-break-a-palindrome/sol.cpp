// https://leetcode.com/problems/break-a-palindrome/

class Solution {
public:
    string breakPalindrome(string palindrome) {
        if (palindrome.size() < 2) return "";
        
        int n = palindrome.size()/2;
        bool found = false;
        for (int pos = 0; pos < n; ++pos) {
            if (palindrome[pos] != 'a') {
                found = true;
                palindrome[pos] = 'a';
                break;
            }
        }
        if (!found) palindrome.back() = 'b';
        return palindrome;
    }
};