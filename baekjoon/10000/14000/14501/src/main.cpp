#include <iostream>
#include <vector>
#define MAX 1000

using namespace std;

int N;
pair<int, int> schedule[MAX];
int max_result;
vector<int> list;
bool visited[MAX];

int calResult(void)
{
    int ret = 0;

    for (int i=0; i<list.size(); i++) {
        int idx = list[i];

        ret += schedule[idx].second;
    }

    return ret;
}

void doDFS(int idx)
{
    if (idx > N) {
        int result = calResult();
        if (result > max_result)
            max_result = result;

        return;
    }

    for (int i=idx; i<=N; i++) {
        if (visited[i])
            continue;
        int time = schedule[i].first;
        if (i + time > N + 1) {
            doDFS(i+time);
            continue;
        }

        visited[i] = true;
        list.push_back(i);
        doDFS(i+time);
        list.pop_back();
        visited[i] = false;
    }
}

int main()
{
    cin >> N;

    for (int i=1; i<=N; i++) {
        cin >> schedule[i].first >> schedule[i].second;
    }

    doDFS(1);

    cout << max_result << "\n";

    return 0;
}
