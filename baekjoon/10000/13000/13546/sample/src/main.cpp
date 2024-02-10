#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    string hello_str, world_str;
    cin >> hello_str >> world_str;
    cout << hello_str + " " + world_str << "\n";

    return 0;
}
