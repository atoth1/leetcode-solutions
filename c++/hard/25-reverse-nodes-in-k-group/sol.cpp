// https://leetcode.com/problems/reverse-nodes-in-k-group/

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
namespace
{
    ListNode* reverseImpl(ListNode* first, ListNode* last)
    {
        // Return back of reversed list
        if (first->next == last)
        {
            first->next = last->next;
            last->next = first;
            return first;
        }
        else
        {
            ListNode* tmp = reverseImpl(first->next, last);
            first->next = tmp->next;
            tmp->next = first;
            return first;
        }
    }
    
    ListNode* reverse(ListNode* n, int k)
    {
        ListNode* tmp = n;
        for (int i = 0; i < k-1; ++i)
        {
            tmp = tmp->next;
            if (!tmp) return nullptr;
        }
        
        reverseImpl(n, tmp);
        return tmp;
    }
}

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        // Supposedly at least one node but why trust it
        if (!head) return nullptr;
        if (k == 1) return head;
        
        // Again, should have k<=n, but why trust it
        ListNode* tmp = reverse(head, k);
        ListNode* myHead;
        if (tmp)
            myHead = tmp;
        else
            return head;
        
        ListNode* current = myHead;
        for (int i = 0; i < k-1; ++i)
                current = current->next;
            
        while (current->next)
        {
            tmp = reverse(current->next, k);
            if (tmp)
            {
                current->next = tmp;
                for (int i = 0; i < k; ++i)
                    current = current->next;
            }
            else
            {
                break;
            }
        }
        return myHead;
    }
};
