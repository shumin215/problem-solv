/**
 *  Algorithm
 *  - 각 low는 배열로, 행은 deque으로 관리
 *  - 만약 insert가 되는 경우엔, 만약 W보다 커지는 경우 해당 행의 마지막 글자를 뒤 행으로 전달
 *  - 현재 행의 크기가 W 이하일 때 까지 진행
 *  - countCharacter를 위해 각 행별로 알파벳의 개수를 관리하는 table를 둔다.
 * 
 */
#include <deque>
#include <cstring>

using namespace std;

constexpr int MAX = 300;
int H, W;
deque<char> memo[MAX];
int ch_cnt_table[MAX][26]; // [Row][Char]
int cursor;
int memo_size;

void init(int mH, int mW, char mStr[])
{
    H = mH;
    W = mW;

    memset(ch_cnt_table, 0, sizeof(ch_cnt_table));
    cursor = 0;
    memo_size = 0;

    for (int i = 0; i < H; i++) {
        memo[i].clear();
    }

    for (int i = 0; i < (int)strlen(mStr); i++) {
        char c = mStr[i];
        int r = i / W;
        memo[r].push_back(c);
        int idx = c - 'a';
        ch_cnt_table[r][idx]++;
        memo_size++;
    }

}

// Maximum 30,000
void insert(char mChar)
{
    int r = cursor / W;
    int c = cursor % W;
    memo[r].insert(memo[r].begin() + c, mChar);
    ch_cnt_table[r][mChar - 'a']++;
    memo_size++;
    cursor++;

    while((int)memo[r].size() > W && r < MAX) {
        char tmp = memo[r].back();
        memo[r].pop_back();
        ch_cnt_table[r][tmp - 'a']--;

        memo[r+1].push_front(tmp);
        ch_cnt_table[r+1][tmp - 'a']++;
        r++;
    }
}

// Maximum 30,000
char moveCursor(int mRow, int mCol)
{
    if ((mRow - 1) * W + mCol - 1 >= memo_size) {
        cursor = memo_size;
        return '$';
    }

    cursor = (mRow - 1) * W + mCol - 1;
    return memo[mRow - 1][mCol - 1];
}

// Maximum 40,000
int countCharacter(char mChar)
{
    int cnt = 0;
    int r = cursor / W;
    int c = cursor % W;

    if (c != 0) {
        for (int i = c; i < (int)memo[r].size(); i++) {
            if (memo[r][i] == mChar)
                cnt++;
        }
        r++;
    }

    while (memo[r].size() > 0 && r < MAX) {
        cnt += ch_cnt_table[r][mChar - 'a'];
        r++;
    }

	return cnt;
}
