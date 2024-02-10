#include <set>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Worker
{
    int id, start, end;
    bool operator < (const Worker& rhs) const {
        if (start != rhs.start)
            return start < rhs.start;
        else if (end != rhs.end) {
            return end < rhs.end;
        } else
            return id < rhs.id;
    }
};

// To get earlier-start worker and earlier-end worker
set<Worker> workers;
// To check whether there is previous worker in O(1)
unordered_map<int, set<Worker>::iterator> hmap;
priority_queue<int, vector<int>, greater<int>> pq;

void init() {
    workers.clear();
    hmap.clear();
}
 
// Maximum 1700
int remove(int mId) 
{
    auto it = hmap.find(mId);
    if (it != hmap.end()) {
        auto s_it = hmap[mId];
        workers.erase(s_it);
        hmap.erase(mId);
    }
    return workers.size();
}

// Maximum 8,000
int add(int mId, int mStart, int mEnd) 
{
    remove(mId);
    auto it = workers.insert({mId, mStart, mEnd}).first;
    hmap[mId] = it; 
    return workers.size();
}
 
// Maximum 300
int announce(int mDuration, int M) 
{
    pq = {};
    for (auto &elem : workers) {
        int cur_t = elem.start;
        int end = elem.end;
        int duration = end - cur_t + 1;
        // Check duration
        if (duration < mDuration)
            continue;
        // Check the others' work time
        while (!pq.empty()) {
            auto top = pq.top();
            if (top - cur_t + 1 < mDuration)
                pq.pop();
            else
                break;
        }

        pq.push(end);

        if ((int)pq.size() == M)
            return cur_t;
    }
    return -1;
}
