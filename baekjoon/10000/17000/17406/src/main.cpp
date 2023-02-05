#include <iostream>
#include <climits>
#include <vector>
#include <cstring>
#define MAX 50
#define K_MAX 6

using namespace std;

int N, M, K;
int arr[MAX][MAX];
int tmp_arr[MAX][MAX];
int R[K_MAX], C[K_MAX], S[K_MAX];
int min_value = INT_MAX;
bool visited[K_MAX];
vector<int> order;

int getMinValue(int _arr[][MAX])
{
    int row_min = INT_MAX;

    for (int i=0; i<N; i++) {
        int row_sum = 0;
        for (int j=0; j<M; j++) {
            row_sum += _arr[i][j];
        }

        if (row_min > row_sum)
            row_min = row_sum;
    }

    return row_min;
}

void printArr(int _arr[][MAX])
{
    cout << "############ Array Print #############\n";
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cout << _arr[i][j] << " ";
        }
        cout << "\n";
    }
}

void rotate(int _arr[][MAX], int idx)
{
    int func_idx = order[idx];
    int r = R[func_idx] - 1, c = C[func_idx] - 1, s = S[func_idx];
    
    for (int i=1; i<=s; i++) {
        int min_x = c-i, min_y = r-i;
        int max_x = c+i, max_y = r+i;
        int len = i * 2;
        int right_up_val = _arr[min_y][max_x];
        // 1. Upper side
        for (int j=0; j<len; j++)
            _arr[min_y][max_x-j] = _arr[min_y][max_x-(j+1)];

        // 2. Left side
        for (int j=0; j<len; j++)
            _arr[min_y+j][min_x] = _arr[min_y+j+1][min_x];

        // 3. Bottom side
        for (int j=0; j<len; j++)
            _arr[max_y][min_x+j] = _arr[max_y][min_x+j+1];

        // 4. Right side
        for (int j=0; j<len; j++)
            _arr[max_y-j][max_x] = _arr[max_y-(j+1)][max_x];
        _arr[min_y+1][max_x] = right_up_val;
    }
}

void doDFS(int cnt)
{
    if (cnt == K) {
        memcpy(tmp_arr, arr, sizeof(arr));

        for (int i=0; i<K; i++) {
            rotate(tmp_arr, i);
        }

        int arr_row_min = getMinValue(tmp_arr);

        if (min_value > arr_row_min)
            min_value = arr_row_min;

        return;
    }

    for (int i=0; i<K; i++) {
        if (visited[i])
            continue;

        visited[i] = true;
        order.push_back(i);
        doDFS(cnt+1);
        order.pop_back();
        visited[i] = false;
    }
}

int main()
{
    cin >> N >> M >> K;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            cin >> arr[i][j];
        }

    for (int i=0; i<K; i++) {
        cin >> R[i] >> C[i] >> S[i];
    }

#ifdef DEBUG
    printArr(arr);
#endif

    doDFS(0);

    cout << min_value << "\n";

    return 0;
}
