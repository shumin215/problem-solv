#include <iostream>
#include <climits>
#include <cassert>
#include <vector>
#define MAX 10
#define PAPER_MAX 5
#define PAPER_MAX_SIZE 5

using namespace std;

bool paper[MAX][MAX];
bool tmp_visited[MAX][MAX];
int min_paper_num = INT_MAX;
int paper_cnt[PAPER_MAX+1];
int num_of_one;
vector<pair<pair<int, int>, int>> list;

bool isRectValid(int x, int y, int size)
{
    bool ret = true;

    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++) {
            if (!paper[y+i][x+j]) {
                return false;
            }
        }

    return ret;
}

void updateVisited(int x, int y, int size, bool attach)
{
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++) {
            paper[y+i][x+j] = !attach;
        }
}

void print(int arr[MAX][MAX])
{
    cout << "############### Print Paper #################\n";
    for (int i=0; i<MAX; i++) {
        for (int j=0; j<MAX; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    return;
}

bool allCovered(void)
{
    for (int i=0; i<MAX; i++)
        for (int j=0; j<MAX; j++) {
            if (paper[i][j])
                return false;
        }
    return true;
}

void doDFS(int total_paper_cnt)
{
    if (total_paper_cnt > min_paper_num)
        return;

    if (allCovered()) {
        if (total_paper_cnt < min_paper_num)
            min_paper_num = total_paper_cnt;
        return;
    }

    for (int row=0; row<MAX; row++) {
        for (int col=0; col<MAX; col++) {
            if (paper[row][col]) {
                for (int s=PAPER_MAX_SIZE; s>0; s--) {
                    if (paper_cnt[s] == PAPER_MAX || col + s > MAX || row + s > MAX)
                        continue;

                    if (isRectValid(col, row, s)) {
                        updateVisited(col, row, s, true);
                        paper_cnt[s]++;
#ifdef DEBUG
                        list.push_back({{col, row}, s});
#endif
                        doDFS(total_paper_cnt+1);
#ifdef DEBUG
                        list.pop_back();
#endif
                        paper_cnt[s]--;
                        updateVisited(col, row, s, false);
                    }
                }

                return;
            }
        }
    }
}

int main()
{
    for (int i=0; i<MAX; i++)
        for (int j=0; j<MAX; j++) {
            int val;
            cin >> val;
            paper[i][j] = val;
            if (val == 1)
                num_of_one++;
        }

    if (num_of_one == 0) {
        cout << "0\n";
        return 0;
    } else if (num_of_one == (MAX * MAX)) {
        cout << "4\n";
        return 0;
    }

    doDFS(0);

    if (min_paper_num == INT_MAX)
        cout << "-1\n";
    else
        cout << min_paper_num << "\n";

    return 0;
}
