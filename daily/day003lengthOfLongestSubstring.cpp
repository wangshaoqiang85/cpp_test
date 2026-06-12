#include <string>
#include <unordered_set>

using namespace std;

class LengthOfLongestSubstring {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int ans = 0;
        unordered_set<char> charSet;
        for (int right = 0; right < s.size(); right++) {
            while(charSet.find(s[right]) != charSet.end()) {
                charSet.erase(s[left]);
                left++;
            }
            charSet.insert(s[right]);
            ans = std::max(ans, right- left+1);
        }
        return ans;
    }
};