#include <stack>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        int ans = 0;
        int n = heights.size();
        for (int i=0; i<=n; i++) {
            int h = i==n ? 0 : heights[i];
            while (!stk.empty() && h < heights[stk.top()]) {
                int h = heights[stk.top()];
                stk.pop();
                int w = stk.empty() ? i : i - stk.top() - 1;
                ans = max(ans, w * h);
            }
            stk.push(i);
        }
        return ans;
    }
};

static bool expectArea(const vector<int>& heights, int expected) {
    vector<int> input = heights;
    Solution sol;
    int got = sol.largestRectangleArea(input);
    if (got != expected) {
        cout << "FAIL: expected " << expected << ", got " << got << "\n";
        return false;
    }
    cout << "PASS: area = " << got << "\n";
    return true;
}

int runDay051LargestRectangleInHistogramTests() {
    int passed = 0;
    int total = 0;

    auto check = [&](const vector<int>& heights, int expected) {
        ++total;
        if (expectArea(heights, expected)) {
            ++passed;
        }
    };

    check({2, 1, 5, 6, 2, 3}, 10);
    check({2, 4}, 4);

    cout << "测试结果: " << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}

int main() {
    runDay051LargestRectangleInHistogramTests();
    return 0;
}
