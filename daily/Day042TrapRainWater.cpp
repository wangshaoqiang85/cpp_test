#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:。，、m
    int trap(vector<int>& height) {
        stack<int> stk;
        int ans = 0;
        for (int i = 0; i< height.size(); ++i) {
            while(!stk.empty() && height[stk.top()] < height[i]) {
                int bottom = stk.top();
                stk.pop();
                if (stk.empty()) break;
                int left = stk.top();
                int w = i - left - 1;
                int h = min(height[left],height[i]) - height[bottom];
                ans += w*h;
            }
            stk.push(i);
        }
        return ans;
    }
};
