#include <iostream>

using namespace std;

int main()
{
    long a, b;
    scanf("%ld %ld", &a, &b);

    long big = (a == b) ? 0 : ((a > b) ? a : b);
    long small = (a > b) ? b : a;
    int diff = (big == 0) ? 0 : (int)(big - small - 1);

    printf("%d\n", diff);

    for (long i=small+1; i<big; i++) {
        printf("%ld ", i);
    }
    printf("\n");

    return 0;
}

