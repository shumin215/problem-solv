#include <iostream>
#define MAX 101

using namespace std;

char arr[MAX][MAX];

void funcType1(int n)
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<i+1; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void funcType2(int n)
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void funcType3(int n)
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i-1; j++) {
            printf(" ");
        }
        for (int j=0; j<i*2+1; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    int n, type;
    cin >> n >> type;

    if (n < 1 || n > 100 || type < 1 || type > 3) {
        printf("INPUT ERROR!\n");
        return 0;
    }

    if (type == 1)
        funcType1(n);
    else if (type == 2)
        funcType2(n);
    else if (type == 3)
        funcType3(n);

    return 0;
}
