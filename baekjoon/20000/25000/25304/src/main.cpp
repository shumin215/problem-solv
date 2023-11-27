#include <iostream>

using namespace std;

int main()
{
    int total = 0;
    int X, N;
    cin >> X;
    cin >> N;

    for (int i=0; i<N; i++) {
        int a, b;
        cin >> a >> b;
        total += a * b;
    }

    if (total == X)
        cout << "Yes\n";
    else
        cout << "No\n";

    return 0;
}
