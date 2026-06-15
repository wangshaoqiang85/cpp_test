#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 通配符匹配（LeetCode 44）
// 规则:
//   '?' — 匹配任意单个字符
//   '*' — 匹配任意字符序列（含空序列）
// 成功条件: 模式 p 必须从头到尾完全匹配整个 s，不允许部分匹配
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = static_cast<int>(s.size());
        int n = static_cast<int>(p.size());
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        // dp[o][j]是匹配的s的空字符串
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

class WildcardMatcherExplainer {
public:
    bool isMatchWithSteps(const string& s, const string& p) {
        cout << "========== 通配符匹配 ==========\n";
        cout << "输入字符串 s = \"" << s << "\"\n";
        cout << "模式字符串 p = \"" << p << "\"\n\n";

        cout << "规则说明:\n";
        cout << "  '?' 匹配任意单个字符\n";
        cout << "  '*' 匹配任意字符序列（包括空序列）\n";
        cout << "  必须完全匹配: s 的每个字符都被 p 消耗，p 的每个符号也都用完\n\n";

        int m = static_cast<int>(s.size());
        int n = static_cast<int>(p.size());
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        cout << "【步骤 1】初始化 DP 表\n";
        cout << "  dp[i][j] 表示 s 的前 i 个字符 与 p 的前 j 个字符 是否完全匹配\n";
        cout << "  表大小: (m+1) x (n+1) = " << (m + 1) << " x " << (n + 1) << "\n";
        dp[0][0] = true;
        cout << "  dp[0][0] = true  （空串匹配空模式）\n\n";

        cout << "【步骤 2】处理模式前缀中的 '*'\n";
        cout << "  当 s 为空时，只有连续 '*' 才能匹配\n";
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
                cout << "  dp[0][" << j << "] = dp[0][" << (j - 1) << "] = "
                     << (dp[0][j] ? "true" : "false")
                     << "  （p[" << (j - 1) << "]='*'，* 可匹配空串）\n";
            } else {
                dp[0][j] = false;
                cout << "  dp[0][" << j << "] = false  （p[" << (j - 1) << "]='"
                     << p[j - 1] << "'，s 为空无法匹配）\n";
            }
        }
        cout << "\n";

        cout << "【步骤 3】逐格填表\n";
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                char sc = s[i - 1];
                char pc = p[j - 1];
                cout << "  比较 s[" << (i - 1) << "]='" << sc << "' 与 p[" << (j - 1) << "]='" << pc << "'\n";

                if (pc == '*') {
                    bool matchEmpty = dp[i][j - 1];
                    bool matchOneMore = dp[i - 1][j];
                    dp[i][j] = matchEmpty || matchOneMore;
                    cout << "    '*' 有两种选择:\n";
                    cout << "      1) 匹配空串: dp[" << i << "][" << (j - 1) << "] = "
                         << (matchEmpty ? "true" : "false") << "\n";
                    cout << "      2) 再吞 s 中一个字符: dp[" << (i - 1) << "][" << j << "] = "
                         << (matchOneMore ? "true" : "false") << "\n";
                    cout << "    => dp[" << i << "][" << j << "] = "
                         << (dp[i][j] ? "true" : "false") << "\n";
                } else if (pc == '?' || sc == pc) {
                    dp[i][j] = dp[i - 1][j - 1];
                    if (pc == '?') {
                        cout << "    '?' 匹配任意单字符，继承 dp[" << (i - 1) << "][" << (j - 1) << "] = "
                             << (dp[i][j] ? "true" : "false") << "\n";
                    } else {
                        cout << "    字符相同，继承 dp[" << (i - 1) << "][" << (j - 1) << "] = "
                             << (dp[i][j] ? "true" : "false") << "\n";
                    }
                    cout << "    => dp[" << i << "][" << j << "] = "
                         << (dp[i][j] ? "true" : "false") << "\n";
                } else {
                    dp[i][j] = false;
                    cout << "    字符不匹配且不是 '?' => dp[" << i << "][" << j << "] = false\n";
                }
            }
        }
        cout << "\n";

        cout << "【步骤 4】读取最终结果（完全匹配的充要条件）\n";
        cout << "  dp[" << m << "][" << n << "] = "
             << (dp[m][n] ? "true" : "false") << "\n";
        cout << "  i=m 且 j=n 意味着 s 全部 " << m << " 个字符、p 全部 " << n << " 个符号都已对齐\n";
        cout << "  结论: " << (dp[m][n] ? "完全匹配成功" : "完全匹配失败") << "\n";
        cout << "================================\n\n";
        return dp[m][n];
    }
};

#ifdef DAY044_WILDCARD_MATCHING_TEST

static bool expectMatch(const string& s, const string& p, bool expected) {
    Solution sol;
    bool got = sol.isMatch(s, p);
    if (got != expected) {
        cout << "FAIL: s=\"" << s << "\", p=\"" << p << "\" expected "
             << (expected ? "true" : "false") << ", got "
             << (got ? "true" : "false") << "\n";
        return false;
    }
    cout << "PASS: s=\"" << s << "\", p=\"" << p << "\" => "
         << (got ? "true" : "false") << "\n";
    return true;
}

int runDay044WildcardMatchingTests() {
    int passed = 0;
    int total = 0;

    auto check = [&](const string& s, const string& p, bool expected) {
        ++total;
        if (expectMatch(s, p, expected)) {
            ++passed;
        }
    };

    cout << "===== 基础用例 =====\n";
    check("aa", "a", false);
    check("aa", "*", true);
    check("cb", "?a", false);
    check("adceb", "*a*b", true);
    check("acdcb", "a*c?b", false);
    check("", "*", true);
    check("", "?", false);
    check("a", "", false);
    check("", "", true);
    check("abc", "a*bc", true);
    check("abc", "a*b*c", true);

    cout << "\n===== 完全匹配 vs 部分匹配 =====\n";
    check("a", "aa", false);       // p 太长，s 已耗尽但 p 还有 'a'
    check("abc", "ab", false);     // 前缀相同，但 s 末尾 'c' 未被匹配
    check("abc", "bc", false);     // 不是从中间开始匹配，必须从首字符对齐
    check("abc", "***", true);     // 多个 * 也可完全匹配

    cout << "\n===== 逐步说明演示 =====\n";
    WildcardMatcherExplainer explainer;
    explainer.isMatchWithSteps("adceb", "*a*b");
    explainer.isMatchWithSteps("acdcb", "a*c?b");

    cout << "测试结果: " << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}

#endif
