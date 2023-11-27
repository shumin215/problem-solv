#include <iostream>
#include <vector>
#define MAX 256

using namespace std;

int N;
int paper[MAX][MAX];
int white_cnt, blue_cnt;

void countPaper(int x, int y, int size)
{
    int b_cnt = 0;

    for (int i=y; i<y+size; i++) {
        for (int j=x; j<x+size; j++) {
            if (paper[i][j] == 1)
                b_cnt++;
        }
    }

    if (b_cnt == (size * size)) {
        blue_cnt++;
    } else if (b_cnt == 0) {
        white_cnt++;
    } else {
        // Left upper
        countPaper(x, y, size/2);
        // Right upper
        countPaper(x + size/2, y, size/2);
        // Left bottom
        countPaper(x, y + size/2, size/2);
        // Right bottom
        countPaper(x + size/2, y + size/2, size/2);
    }
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> paper[i][j];
        }
    }

    countPaper(0, 0, N);

    cout << white_cnt << "\n";
    cout << blue_cnt << "\n";

    return 0;
}
