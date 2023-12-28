#include <queue>
#include <algorithm>
 
using namespace std;
 
struct Road
{
    int id, time;
 
    bool operator < (const Road &rhs) const {
        if (time != rhs.time)
            return time < rhs.time;
        else
            return id > rhs.id;
    }
};
 
constexpr int MAX = 10000 + 1;
int N;
int *P;
int road[MAX], num_road[MAX];
priority_queue<Road, vector<Road>, less<Road>> pq;
 
void init(int mN, int mPopulation[])
{
    N = mN;
    P = mPopulation;
 
    pq = {};
    for (int i = 0; i < N - 1; i++) {
        road[i] = P[i] + P[i + 1];
        num_road[i] = 1;
        pq.push({ i, road[i] });
    }
 
    return;
}
 
// 5000회 이하
int expand(int M)
{
    int ret = 0;
    while (M--) {
        auto top_road = pq.top();
        pq.pop();
 
        num_road[top_road.id]++;
        int time = road[top_road.id] / num_road[top_road.id];
        pq.push({ top_road.id, time });
        ret = time;
    }
 
    return ret;
}
 
// 2500회 이하
int calculate(int mFrom, int mTo)
{
    if (mFrom > mTo)
        swap(mFrom, mTo);
    int sum = 0;
    for (int i = mFrom; i < mTo; i++) {
        sum += road[i] / num_road[i];
    }
    return sum;
}
 
bool isValid(int low, int high, int size, int target)
{
    bool ret = false;
    int sum = 0, num_grp = 1;
    for (int i = low; i <= high; i++) {
        sum += P[i];
 
        if (sum > size) {
            sum = P[i];
            num_grp++;
        }
    }
 
    ret = (num_grp <= target) ? true : false;
 
    return ret;
}
 
// 300회 이하
int divide(int mFrom, int mTo, int K)
{
    int low = *max_element(P + mFrom, P + mTo + 1);
    int high = 0;
    for (int i = mFrom; i <= mTo; i++) {
        high += road[i];
    }
 
    int ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
 
        // Left side
        if (isValid(mFrom, mTo, mid, K)) {
            high = mid - 1;
            ans = mid;
        }
        // Right side
        else {
            low = mid + 1;
        }
    }
    return ans;
}