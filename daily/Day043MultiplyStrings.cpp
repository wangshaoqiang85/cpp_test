#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string multiplyAbs(string num1, string num2) {
        bool neg1 = num1[0] == '-' ? 1 : 0;
        bool neg2 = num2[0] == '-' ? 1 : 0;
        string num11 = neg1 ? num1.substr(1) : num1;
        string num22 = neg2 ? num2.substr(1) : num2;
        string result = multiply(num11, num22);
        if (result != "0" && neg1 != neg2) {
            result = "-" + result;
        } 
        return result;
    }
    string multiply(string num1, string num2) {
        int m = num1.size();
        int n = num2.size();
        if (num1[0] == '0' || num2[0] == '0') {
            return "0";
        }
        vector<int> total(m+n);
        for (int i = m -1; i>=0; i--) {
            for (int j = n -1; j>=0; j--) {
                int num = (num1[i] - '0') *(num2[j] - '0');
                int pos1 = i+j;
                int pos2 = i+j +1;
                int cur = total[pos2] + num;
                total[pos2] = cur % 10;
                total[pos1] += cur / 10;
            }
        }

        string result;
        for (auto& item : total) {
            if(!result.empty() || item != 0) {
                result.push_back(item + '0');
            }
        }
        return result;
    }
};
