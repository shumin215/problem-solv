#include <iostream>

#define MAX 1000000+1

using namespace std;

int N, M;
int g_table[MAX];

int getGrp(int _v)
{
    if (_v == g_table[_v])
        return _v;
    else {
        g_table[_v] = getGrp(g_table[_v]);
        return g_table[_v];
    }
}

bool isDiffGrp(int _a, int _b)
{
    int ga = getGrp(_a);
    int gb = getGrp(_b);

    return (ga != gb) ? true : false;
}

void doUnion(int _a, int _b)
{
    int ga = getGrp(_a);
    int gb = getGrp(_b);

    if (ga != gb) {
        g_table[ga] = gb;
    }
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin >> N >> M;

    for (int i=0; i<=N; i++)
        g_table[i] = i;

    for (int i=0; i<M; i++) {
        int op, a, b;
        cin >> op >> a >> b;

        if (op == 0) {
            doUnion(a, b);
        } else {
            if (isDiffGrp(a, b)) {
                printf("%s\n", "NO");
            } else {
                printf("%s\n", "YES");
            }
        }
    }

    return 0;
}
