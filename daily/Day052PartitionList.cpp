#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode smallHead(0);
        ListNode largeHead(0);
        ListNode* smallTail = &smallHead;
        ListNode* largeTail = &largeHead;

        ListNode* cur = head;
        while (cur != nullptr) {
            if (cur->val < x) {
                smallTail->next = cur;
                smallTail = cur;
            } else {
                largeTail->next = cur;
                largeTail = cur;
            }
            cur = cur->next;
        }
        largeTail->next = nullptr;
        smallTail->next = largeHead.next;
        return smallHead.next;
    }
};

static ListNode* buildList(const vector<int>& values) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : values) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

static vector<int> listToVector(ListNode* head) {
    vector<int> result;
    for (ListNode* cur = head; cur != nullptr; cur = cur->next) {
        result.push_back(cur->val);
    }
    return result;
}

static void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

static bool expectPartition(const vector<int>& values, int x, const vector<int>& expected) {
    ListNode* head = buildList(values);
    Solution sol;
    ListNode* gotHead = sol.partition(head, x);
    vector<int> got = listToVector(gotHead);
    freeList(gotHead);

    if (got != expected) {
        cout << "FAIL: x=" << x << ", expected [";
        for (size_t i = 0; i < expected.size(); ++i) {
            if (i) cout << ',';
            cout << expected[i];
        }
        cout << "], got [";
        for (size_t i = 0; i < got.size(); ++i) {
            if (i) cout << ',';
            cout << got[i];
        }
        cout << "]\n";
        return false;
    }
    cout << "PASS: x=" << x << "\n";
    return true;
}

int runDay052PartitionListTests() {
    int passed = 0;
    int total = 0;

    auto check = [&](const vector<int>& values, int x, const vector<int>& expected) {
        ++total;
        if (expectPartition(values, x, expected)) {
            ++passed;
        }
    };

    check({1, 4, 3, 2, 5, 2}, 3, {1, 2, 2, 4, 3, 5});
    check({2, 1}, 2, {1, 2});

    cout << "test result: " << passed << "/" << total << " pass\n";
    return passed == total ? 0 : 1;
}

int main() {
    return runDay052PartitionListTests();
}
