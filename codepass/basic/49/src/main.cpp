#include <iostream>

using namespace std;

long long getFact(int val)
{
    if (val == 1) {
        printf("1! = 1\n");
        return 1;
    }


    printf("%d! = %d * %d!\n", val, val, val - 1);

    return val * getFact(val - 1);
}

int main()
{
    int a;
    cin >> a;

    long long result = getFact(a);

    printf("%lld\n", result);

    return 0;
}
