/*
03_메모장
*/
#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

constexpr int MAX = 10000000 + 1;

int N, M, Q;
int idxCur, memo_size;
deque<int> memo[1000 + 1];
char str[MAX];

void insert(char in_ch)
{
    int row = idxCur / M;
    int col = idxCur % M;

    //printf("[INFO] Insert, row=%d, col=%d, ch=%c\n", row, col, in_ch);
    memo[row].insert(memo[row].begin() + col, in_ch);
    idxCur++;
    memo_size++;

    while (memo[row].size() > M) {
        memo[row + 1].push_front(memo[row].back());
        memo[row].pop_back();
        row++;
    }
}

void erase()
{
    if (idxCur == 0)
        return;

    idxCur--;
    memo_size--;
    int row = idxCur / M;
    int col = idxCur % M;

    //printf("[INFO] Erase, row=%d, col=%d\n", row, col);
    memo[row].erase(memo[row].begin() + col);

    while (!memo[row + 1].empty()) {
        memo[row].push_back(memo[row + 1].front());
        memo[row + 1].pop_front();
        row++;
    }
}

void init()
{
    idxCur = 0, memo_size = 0;
    char init_ch;
    for (int i = 0; (init_ch = str[i]); i++) {
        int row = i / M;

        memo[row].push_back(str[i]);
        memo_size++;
    }
}

void move(int x, int y)
{
    /*idxCur = min(x * M + y, memo_size);
    if (idxCur == memo_size) puts("*");
    else printf("%c\n", memo[x][y]);*/


    int target = x * M + y;

    if (target >= memo_size) {
        idxCur = memo_size;
        printf("*\n");
    }
    else {
        idxCur = target;
        printf("%c\n", memo[x][y]);
    }
}

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32

    scanf("%d %d %d", &N, &M, &Q);
    scanf("%s", str);

    init();

    for (int i = 0; i < Q; i++) {
        char cmd[30];
        scanf(" %s", &cmd);

        if (cmd[0] == 'i') {
            char in_ch;
            scanf(" %c", &in_ch);

            insert(in_ch);
        }
        else if (cmd[0] == 'e') {
            erase();
        }
        else if (cmd[0] == 'm') {
            int x, y;
            scanf(" %d %d", &x, &y);
            move(x, y);
        }
    }

    return 0;
}

