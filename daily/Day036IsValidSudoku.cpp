#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> row(9, vector<bool>(9, false));
        vector<vector<bool>> col(9, vector<bool>(9, false));
        vector<vector<bool>> box(9, vector<bool>(9, false));

        for (int i = o; i < 9;i++) {
            for (int j =0;j<9;j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int idx = board[i][j] - '1';
                int boxIdx = (i/3) * 3 + j / 3;
                if (row[i][idx] || col[j][idx] || box[boxIdx][idx]) {
                    return false;
                }
                row[i][idx] = true;
                col[j][idx]  = true;
                box[boxIdx][idx] = true;
            }
        }
        return true;

    }
}