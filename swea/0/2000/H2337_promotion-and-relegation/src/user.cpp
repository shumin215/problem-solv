/**
 * H2337 승강제리그 
 * 
 * 삭제, 삽입이 이뤄지면서 기존 순서가 무너지는 문제가 존재함
 */
#include <set>

using namespace std;

struct Player
{
    int id, abil;
    bool operator < (const Player &rhs) const {
        if (abil != rhs.abil)
            return abil > rhs.abil;
        else
            return id < rhs.id;
    }
};
constexpr int MAX = 39990+1;
constexpr int LEAGUE_MAX = 3999 + 1;
int N, L;
int round;
int num_players_league;
set<Player, less<Player>> plist_upper[LEAGUE_MAX];
set<Player, less<Player>> plist_lower[LEAGUE_MAX];

void init(int mN, int mL, int mAbility[])
{
    N = mN;
    L = mL;
    num_players_league = N / L;
    int league = 0;

    for (int i = 0; i < L; i++) {
        plist_upper[i].clear();
        plist_lower[i].clear();
    }

    for (int id = 0; id < N; id++) {
        if ((int)plist_upper[league].size() < (num_players_league / 2)) {
            plist_upper[league].insert({id, mAbility[id]});
        } else {
            auto worst = --plist_upper[league].end();
            if (worst->abil < mAbility[id]) {
                plist_lower[league].insert(*worst);
                plist_upper[league].erase(worst);
                plist_upper[league].insert({id, mAbility[id]});
            } else {
                plist_lower[league].insert({id, mAbility[id]});
            }
        }

        if (id % num_players_league == (num_players_league - 1)) {
            league++;
        }
    }
}

void insertPlayer(int idx, Player p)
{
    if (plist_upper[idx].size() == num_players_league / 2) {
        auto upper_worst = --plist_upper[idx].end();
        if (upper_worst->abil < p.abil ||
            (upper_worst->abil == p.abil && upper_worst->id > p.id)) {
            plist_lower[idx].insert(*upper_worst);
            plist_upper[idx].erase(upper_worst);
            plist_upper[idx].insert(p);
        } else {
            plist_lower[idx].insert(p);
        }
    } else {
        // DEBUG: 만약 plist_upper에서 player가 빠져나간 경우도 고려해야함
        // DEBUG: plist_upper size가 0인 경우도 고려해야함
        auto lower_best = plist_lower[idx].begin();
        if (lower_best->abil < p.abil ||
            (lower_best->abil == p.abil && lower_best->id > p.id)) {
            plist_upper[idx].insert(p);
        } else {
            plist_upper[idx].insert(*plist_lower[idx].begin());
            plist_lower[idx].erase(plist_lower[idx].begin());
            plist_lower[idx].insert(p);
        }
    }
    return;
}

// Maximum 500
// O(500 * 4000 * 10) = O(20,000,000)
int move()
{
    int ret = 0;
    Player prev_worst_p = *prev(plist_lower[0].end(), 1);
    plist_lower[0].erase(prev(plist_lower[0].end(), 1));

    for (int i = 1; i < L; i++) {
        auto best_it = plist_upper[i].begin();
        auto best_p = *best_it;
        auto worst_it = prev(plist_lower[i].end(), 1);
        auto worst_p = *worst_it;

        ret += prev_worst_p.id + best_p.id;

        if (i != (L - 1))
            plist_lower[i].erase(worst_it);
        plist_upper[i].erase(best_it);

        insertPlayer(i - 1, best_p);
        insertPlayer(i, prev_worst_p);
        // plist[i-1].insert(best_p);
        // DEBUG: 이전의 worst player가 들어가야 함
        // plist[i].insert(prev_worst_p);

        prev_worst_p = worst_p;
    }

    return ret;
}

// Maximum 1000
// O(1000 * 4000 * (4000) / 2) = O(20,000,000)
int trade()
{
    int ret = 0;
    // int mid_idx = (num_players_league + 1) / 2 - 1;
    Player prev_mid_p = *plist_lower[0].begin();
    plist_lower[0].erase(plist_lower[0].begin());

    for (int i = 1; i < L; i++) {
        auto best_it = plist_upper[i].begin();
        auto best_p = *best_it;
        auto mid_it = plist_lower[i].begin();
        auto mid_p = *mid_it;

        ret += prev_mid_p.id + best_p.id;

        if (i != (L - 1))
            plist_lower[i].erase(mid_it);
        plist_upper[i].erase(best_it);

        insertPlayer(i - 1, best_p);
        insertPlayer(i, prev_mid_p);
        // plist[i-1].insert(best_p);
        // plist[i].insert(prev_mid_p);

        prev_mid_p = mid_p;
    }

    return ret;
}
