//
// Created by wangshaoqiang on 2026/6/2.
//

#include <unordered_map>
#include <string>
#include <stack>

using namespace std;

struct ListNode {
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return new ListNode(0);
    }

    bool isValid(string s) {
        int n = s.size();
        if (n % 2 == 1) {
            return false;
        }
        unordered_map<char, char> pair = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };

        stack<char> stk;
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (ch == '(' || ch == '[' || ch == '{') {
                stk.push(ch);
                continue;
            }
            if (stk.empty() || stk.top() != pair[ch]) {
                return false;
            }
            stk.pop();
        }
        return s.empty();
    }
};

int main() {
    auto s = new Solution();
    string str = "()";
    bool ans = s->isValid(str);
}
