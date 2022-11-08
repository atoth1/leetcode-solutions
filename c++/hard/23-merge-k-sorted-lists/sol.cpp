// https://leetcode.com/problems/merge-k-sorted-lists/

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1)
            return list2;
        else if (!list2)
            return list1;
        
        ListNode* head;
        if (list1->val < list2->val)
        {
            head = list1;
            list1 = list1->next;
        }
        else
        {
            head = list2;
            list2 = list2->next;
        }
        
        ListNode* current = head;
        while (list1 || list2)
        {
            if (!list1)
            {
                current->next = list2;
                break;
            }
            else if (!list2)
            {
                current->next = list1;
                break;
            }
            else if (list1->val < list2->val)
            {
                current->next = list1;
                current = current->next;
                list1 = list1->next;
            }
            else
            {
                current->next = list2;
                current = current->next;
                list2 = list2->next;
            }
        }
        return head;
    }
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        
        std::vector<ListNode*> ret(lists);
        while (ret.size() > 1)
        {
            std::vector<ListNode*> temp;
            auto it = ret.begin();
            for (; it != ret.end()-1 && it != ret.end(); it += 2)
            {
                temp.push_back(mergeTwoLists(*it, *(it+1)));
            }
            if (it == ret.end()-1)
                temp.push_back(*it);
            ret = temp;
        }
        return ret[0];
    }
};
