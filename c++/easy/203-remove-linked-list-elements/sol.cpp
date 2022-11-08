// https://leetcode.com/problems/remove-linked-list-elements/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <memory>

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        static constexpr int INVALID = 0;
        auto sentinel = std::make_unique<ListNode>(INVALID, head);
        auto prev = sentinel.get();
        auto curr = head;
        while (curr) {
            if (curr->val == val) {
                prev->next = curr->next;
                curr->next = nullptr;
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return sentinel->next;
    }
};
