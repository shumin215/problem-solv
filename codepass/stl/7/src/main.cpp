#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int N;
int cmd, pos, value;
deque<int> l;

bool cmp(int l, int r) 
{
    int absl = abs(value - l);
    int absr = abs(value - r);

    if (absl != absr)
        return absl < absr;
    return l < r;
}

int main()
{
//    freopen("input.txt", "r", stdin);
    cin >> N;

    for (int i=0; i<N; i++) {
        cin >> cmd;

        if (cmd == 1) {
            cin >> pos >> value;
            if (pos == 0) {
                l.push_front(value);
            } else {
                l.push_back(value);
            }
        } else if (cmd == 2) {
            cin >> pos >> value;
            int cnt = 0;
            if (pos == 0) {
                for (auto it=l.begin(); it!=l.end();) {
                    if (*it >= value) {
                        it = l.erase(it);
                        cnt++;
                        if (cnt >= 3)
                            break;
                    }
                    else
                        it++;
                }
            } else {
                for (auto it=l.end(); it!=l.begin();) {
                    it--;
                    if (*it >= value) {
                        it = l.erase(it);
                        cnt++;
                        if (cnt >= 3)
                            break;
                    }
                }
            }

        } else if (cmd == 3) {
            cin >> value;
            sort(l.begin(), l.end(), cmp);
        } else if (cmd == 4) {
            cin >> pos;
            if (pos == 0) {
                for (auto x : l) {
                    cout << x << " ";
                }
            } else {
                for (auto iter=l.rbegin(); iter!=l.rend(); iter++) {
                    cout << *iter << " ";
                }
            }

            cout << "\n";
        }
    }

    return 0;
}
