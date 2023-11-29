#include <iostream>
#include <map>

using namespace std;

int T;
int N;
map<string, int> m;

int main()
{
    cin >> T;

    for (int i=0; i<T; i++) {
        cin >> N;
        m.clear();

        if (N == 0) {
            printf("0\n");
            continue;
        }

        for (int i=0; i<N; i++) {
            string name, type;
            cin >> name >> type;

            if (m.find(type) == m.end()) {
                m.insert({type, 1});
            } else {
                m[type]++;
            }
        }

        int ans = 1;
        for (auto elem: m) {
            // Both number of kinds and none of them
            ans *= (elem.second + 1);
        }
        // We have to omit naked case
        ans = ans - 1;

        printf("%d\n", ans);
    }

    return 0;
}
