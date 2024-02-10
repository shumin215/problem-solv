#include <list>
#include <queue>
#include <cstring>

using namespace std;

constexpr int NUM_LINES = 5;
constexpr int MAX_STATIONS = 40000 + 1;

int N;
list<int> routes[NUM_LINES];
list<int>::iterator stations[NUM_LINES][MAX_STATIONS];
int visited[NUM_LINES][MAX_STATIONS];
int visit_cnt;
bool is_endline[NUM_LINES];

struct Data
{
    int line, station, time;
};

void init(int mN, int mLastStation1[5], int mLastStation2[5])
{
    N = mN;
    visit_cnt = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < NUM_LINES; i++) {
        for (int j = 0; j < N; j++) {
            stations[i][j] = routes[i].end();
        }
    }

    for (int i = 0; i < NUM_LINES; i++) {
        routes[i].clear();
        stations[i][mLastStation1[i]] = routes[i].insert(routes[i].end(), mLastStation1[i]);
        stations[i][mLastStation2[i]] = routes[i].insert(routes[i].end(), mLastStation2[i]);
    }
}
 
// Maximum 40,000
void add(int mLine, int mPrevStation, int mStation)
{
    auto iter = routes[mLine].insert(next(stations[mLine][mPrevStation]), mStation);
    stations[mLine][mStation] = iter;
}

bool existStation(int line, int station)
{
    return stations[line][station] != routes[line].end();
}

// Maximum 100
int minTravelTime(int mStart, int mEnd)
{
    int ret = -1;
    queue<Data> q;
    visit_cnt++;

    for (int i = 0; i < NUM_LINES; i++) {
        if (existStation(i, mStart)) {
            q.push({i, mStart, 0});
        }
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (cur.station == mEnd) {
            ret = cur.time;
            break;
        }

        if (visited[cur.line][cur.station] == visit_cnt)
            continue;
        visited[cur.line][cur.station] = visit_cnt;

        // Front
        auto front = next(stations[cur.line][cur.station]);
        if (front != routes[cur.line].end()) {
            if (visited[cur.line][*front] != visit_cnt) {
                q.push({cur.line, *front, cur.time + 1});
            }
        }

        // Back
        if (stations[cur.line][cur.station] != routes[cur.line].begin()) {
            auto back = prev(stations[cur.line][cur.station]);
            if (visited[cur.line][*back] != visit_cnt) {
                q.push({cur.line, *back, cur.time + 1});
            }
        }

        // Transfer
        for (int i = 0; i < NUM_LINES; i++) {
            if (i != cur.line) {
                if (!existStation(i, cur.station))
                    continue;
                if (visited[i][cur.station] == visit_cnt)
                    continue;
                q.push({i, cur.station, cur.time + 1});
            }
        }
    }

	return ret;
}

// Maximum 400
int minTransfer(int mStart, int mEnd)
{
    int ret = -1;
    queue<Data> q;
    bool visited_line[5];

    for (int i = 0; i < NUM_LINES; i++) {
        visited_line[i] = false;
        if (existStation(i, mStart)) {
            q.push({i, 0, 0});
        }
    }

    for (int i = 0; i < NUM_LINES; i++) {
        is_endline[i] = false;
        if (existStation(i, mEnd)) {
            is_endline[i] = true;
        }
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (is_endline[cur.line]) {
            ret = cur.time;
            break;
        }

        if (visited_line[cur.line])
            continue;
        visited_line[cur.line] = true;

        for (auto sid: routes[cur.line]) {
            // Transfer check
            for (int i = 0; i < NUM_LINES; i++) {
                if (i == cur.line)
                    continue;
                if (visited_line[i])
                    continue;
                if (stations[i][sid] != routes[i].end()) {
                    q.push({i, 0, cur.time + 1});
                }
            }
        }
    }

	return ret;
}