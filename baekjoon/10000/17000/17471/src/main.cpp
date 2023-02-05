/*
 *  Idea
 *  1. Get combination about area for each party
 *  2. Check condition consisting of two parties
 *      - Each party has to have one area at least
 *      - Each parth has to have adjacent area
 *  3. Calculate difference of pupulation between two parties and update minimum difference
 */
#include <iostream>
#include <climits>
#include <vector>
#include <cstring>
#include <queue>
#define MAX 11

using namespace std;

int N;
int population[MAX];
bool connected[MAX][MAX];
bool selected[MAX];
int min_pdiff = INT_MAX;

void updateParty(vector<int> &a_party, vector<int> &b_party)
{
    for (int i=1; i<=N; i++) {
        if (selected[i])
            a_party.push_back(i);
        else
            b_party.push_back(i);
    }
}

int doBFS(int idx, bool is_a)
{
    int visit_cnt = 0;
    bool visited[MAX];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(idx);
    visited[idx] = true;
    visit_cnt++;

    while(!q.empty()) {
        int cur_idx = q.front();
        q.pop();

        for (int i=1; i<=N; i++) {
            if (is_a) {
                if (!visited[i] && connected[cur_idx][i] && selected[i]) {
                    visited[i] = true;
                    visit_cnt++;
                    q.push(i);
                }
            } else {
                if (!visited[i] && connected[cur_idx][i] && !selected[i]) {
                    visited[i] = true;
                    visit_cnt++;
                    q.push(i);
                }
            }
        }
    }

    return visit_cnt;
}

bool isValid(vector<int> &a_party, vector<int> &b_party)
{
    if (a_party.size() == 0 || b_party.size() == 0)
        return false;

    int a_area = doBFS(a_party.front(), true);
    int b_area = doBFS(b_party.front(), false);

    if (a_area != (int)a_party.size() || b_area != (int)b_party.size())
        return false;

    return true;
}

int getPDiff(vector<int> &a_party, vector<int> &b_party)
{
    int ret;
    int a_sum = 0, b_sum = 0;

    for (int i=0; i<(int)a_party.size(); i++)
        a_sum += population[a_party[i]];
    for (int i=0; i<(int)b_party.size(); i++)
        b_sum += population[b_party[i]];

    ret = abs(a_sum - b_sum);

    return ret;
}

void doDFS(int idx, int cnt)
{
    // Consider all combination when each party has more than single area
    if (cnt >= 1) {
        vector<int> a_party;
        vector<int> b_party;

        updateParty(a_party, b_party);

        if (isValid(a_party, b_party)) {
            int diff = getPDiff(a_party, b_party);

            if (diff < min_pdiff)
                min_pdiff = diff;
        }
    }

    if (cnt == N) {
        return;
    }

    for (int i=idx; i<=N; i++) {
        if (selected[i])
            continue;

        selected[i] = true;
        doDFS(i, cnt+1);
        selected[i] = false;
    }
}

void solve(void)
{
    doDFS(1, 0);

    if (min_pdiff == INT_MAX)
        cout << "-1" << "\n";
    else
        cout << min_pdiff << "\n";
}

int main()
{
    cin >> N;

    for (int i=1; i<=N; i++)
        cin >> population[i];

    for (int i=1; i<=N; i++) {
        int num;
        cin >> num;

        for (int j=0; j<num; j++) {
            int dst;
            cin >> dst;
            connected[i][dst] = true;
        }
    }

    solve();

    return 0;
}
