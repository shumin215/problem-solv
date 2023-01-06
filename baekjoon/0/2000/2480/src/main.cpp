#include <iostream>

int val[3];

int main()
{
    scanf("%d %d %d", &val[0], &val[1], &val[2]);
    int price = 0;
    bool cmp01 = val[0] == val[1];
    bool cmp12 = val[1] == val[2];
    bool cmp02 = val[0] == val[2];

    if (cmp01 && cmp12) {
        price = 10000 + 1000 * val[0];
    } else if (cmp01 || cmp02 || cmp12) {
        if (cmp01)
            price = 1000 + 100 * val[0];
        else if (cmp02)
            price = 1000 + 100 * val[0];
        else
            price = 1000 + 100 * val[1];
    }
    else {
        int max = val[0];
        if (max < val[1])
            max = val[1];
        if (max < val[2])
            max = val[2];
        price = max * 100;
    }

    printf("%d\n", price);

    return 0;
}
