#include <iostream>
#include <set>

using namespace std;

set<int> s;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N;
    cin >> N;

    for (int i=0; i<N; i++) {
        int num;
        cin >> num;

        s.insert(num);
    }

    cin >> N;
    for (int i=0; i<N; i++) {
        int num;
        cin >> num;

        if (s.find(num) != s.end())
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}
