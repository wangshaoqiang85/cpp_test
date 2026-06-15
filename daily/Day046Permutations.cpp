#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> cur;
        vector<bool> used(nums.size(), false);
        backtrack(nums, used, cur, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& cur,
                   vector<vector<int>>& result) {
        if (cur.size() == nums.size()) {
            result.push_back(cur);
            return;
        }
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            cur.push_back(nums[i]);
            backtrack(nums, used, cur, result);
            cur.pop_back();
            used[i] = false;
        }
    }
};
