#include <iostream>
#define MAX 15

using namespace std;

int N;
int q_cnt;
// {row0, row1, row2, row3, ...}
// board[0]: col0, board[1]: col1, ...
int board[MAX];

bool rowValid(int row)
{
    for (int i=0; i<row; i++) {
        if (board[i] == board[row] || (row-i) == abs(board[row] - board[i]))
            return false;
    }
    return true;
}

void search(int row)
{
    if (row == N) {
        q_cnt++;
        return;
    }

    for (int col=0; col<N; col++) {
        board[row] = col;
        if (rowValid(row)) {
            search(row+1);
        }
    }
}

int main()
{
    cin >> N;

    search(0);

    cout << q_cnt << endl;

    return 0;
}

























































#if 0
#include <iostream>
#define MAX 15+1

using namespace std;

int map[MAX];
int N;
int qnum;

bool isAvail(int row)
{
    for (int i=0; i<row; i++) {
        if (map[i] == map[row] || abs(map[i] - map[row]) == (row - i))
            return false;
    }

    return true;
}

void search(int row)
{
    if (row == N) {
        qnum++;
        return;
    }

    // Column
    for (int i=0; i<N; i++) {
        map[row] = i;

        if (isAvail(row)) {
            search(row+1);
        }
    }
}

int main()
{
    cin >> N;

    search(0);

    cout << qnum << endl;

    return 0;
}
#endif
