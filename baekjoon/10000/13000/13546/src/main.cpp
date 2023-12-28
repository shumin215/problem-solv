#include <iostream>
#include <cstdio>

using namespace std;

constexpr int SQ = 220;
constexpr int MAX = 100000 + 1;

int max_arr[SQ];
int arr[MAX];
int N, K, M;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);
//    string hello_str, world_str;
//    cin >> hello_str >> world_str;
    cin >> N >> K;

    for (int i=1; i<=N; i++) {
        cin >> arr[i];
    }

    cin >> M;

    for (int i=0; i<M; i++) {
        int l, r;
        cin >> l >> r;

        // Left
        while (l <= r && l % SQ != 0) {
            
        }
        // Right
        
        // Else
    }

    return 0;
}
