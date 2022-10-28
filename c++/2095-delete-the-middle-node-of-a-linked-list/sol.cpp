// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/

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
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (!head->next) return nullptr;
        if (!head->next->next) {
            head->next = nullptr;
            return head;
        }
        
        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        
        if (fast->next) { /* even count */
            slow->next = slow->next->next;
        } else { /* odd count */
            slow->val = slow->next->val;
            slow->next = slow->next->next;
        }
        return head;
    }
};
