#include <iostream>
#include <climits>
#define MAX 50
#define TOTAL_SIZE 64

using namespace std;

int N, M;
char map[MAX][MAX];

int main()
{
    cin >> N >> M;
    int result = INT_MAX;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            cin >> map[i][j];

    for (int i=0; i<N && i+8<=N; i++) {
        for (int j=0; j<M && j+8<=M; j++) {
            int b_cnt = 0, w_cnt = 0;
            int local_result;

            for (int ii=i; ii<i+8; ii++) {
                for (int jj=j; jj<j+8; jj++) {
                    bool is_idx_even = ((ii+jj) % 2) == 0;

                    // In case of non-black at even index
                    if (is_idx_even && map[ii][jj] != 'B') {
                        w_cnt++;
                    }
                    // In case of non-white at odd index
                    if (!is_idx_even && map[ii][jj] != 'W') {
                        b_cnt++;
                    }
                }
            }

            if (w_cnt + b_cnt > (TOTAL_SIZE / 2))
                local_result = TOTAL_SIZE - (w_cnt + b_cnt);
            else
                local_result = w_cnt + b_cnt;

            if (local_result < result)
                result = local_result;
        }
    }

    printf("%d\n", result);

    return 0;
}
