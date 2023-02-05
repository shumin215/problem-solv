/*
 *  Idea
 *  
 *  1. Using permutation, we get all player order
 *  2. Calculate score with the baseball rule
 *  3. If the inning reaches the N, compare the max score
 */
#include <iostream>
#include <climits>
#include <vector>
#include <cassert>
#define PLAYERS 9
#define OUT_CNT 3
#define MAX 50+1

using namespace std;

int N;
int info[MAX][PLAYERS+1];
int max_score = INT_MIN;;
bool selected[PLAYERS+1];
vector<int> lineup;

int getScore(unsigned char _field)
{
    int ret = 0;
    int field = _field >> 3;

    for (int i=0; i<5; i++) {
        if ((field >> i) & 1)
            ret++;
    }

    return ret;
}

/*
 *  field_info Description
 *
 *   On LSB side, each bit indicates base 
 *   0b0000_0XXX
 *          ||||_ 1st base
 *          |||__ 2nd base
 *          ||___ 3rd base
 *          |____ home base
 */
int play(vector<int> cur_lineup)
{
    int score = 0, out_cnt = 0, inning = 0;

    unsigned char field_info = 0;

    while(true) {
        if (out_cnt == OUT_CNT) {
            inning++;
            out_cnt = 0;
            field_info = 0;
        }

        if (inning == N)
            break;

        int player = cur_lineup.front();
        int hit = info[inning][player];

        if (hit == 0) {
            out_cnt++;
        } else {
            if (hit == 1)
                field_info = (field_info << 1) | 0b1;
            else if (hit == 2)
                field_info = (field_info << 2) | 0b10;
            else if (hit == 3)
                field_info = (field_info << 3) | 0b100;
            else if (hit == 4)
                field_info = (field_info << 4) | 0b1000;
            else
                assert(false);

            score += getScore(field_info);
            field_info = field_info & 0b111;
        }

        cur_lineup.erase(cur_lineup.begin());
        cur_lineup.push_back(player);
    }

    return score;
}

void doDFS(int cnt)
{
    if (cnt == PLAYERS) {
        int score = play(lineup);

        if (score > max_score)
            max_score = score;

        return;
    }

    for (int i=1; i<=PLAYERS; i++) {
        if (selected[i])
            continue;
        // To consider 1st player
        if (i == 1 && lineup.size() != 3)
            continue;

        selected[i] = true;
        lineup.push_back(i);
        doDFS(cnt+1);
        lineup.pop_back();
        selected[i] = false;
    }
}

void solve(void)
{
    doDFS(0);
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=1; j<=PLAYERS; j++) {
            cin >> info[i][j];
        }
    }

    solve();

    cout << max_score << "\n";

    return 0;
}
